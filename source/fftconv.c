#include"../include/fftconv.h"
#include"../include/op_fft.h"
#include"../include/op_cgemm.h"

#define START_R2C_S    12
#define START_C2R_S    (START_R2C_S+8)
#define START_R2C_X    (START_C2R_S+22)
#define START_R2C_Xg   (START_R2C_X+6)
#define START_C2R_X    (START_R2C_Xg+8)
#define START_R2C      (START_C2R_X+4)
#define START_R2C_PAD  (START_R2C+96)
#define START_C2R      (START_R2C_PAD+48)

static void fft2d_r2c_a( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    if((p->pad_l|p->pad_t)!=0){
        lk_fft2d_r2c_perm_pad( &kern[START_R2C_PAD+(p->id<<4)+p->pad_t], p, dst, src, 0, s );
    } else {
        lk_fft2d_r2c_perm_a( &kern[START_R2C+(p->id<<4)+(p->any-1)], p, dst, src, 0, s );
    }
}
static void fft2d_r2c_b( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t dir, hipStream_t s )
{
    if((p->bnx==p->bny)&&((p->bnx==3)||(p->bnx==5))){
        lk_fft2d_r2c_perm_s( &kern[START_R2C_S+((p->id<<2)|(dir<<1)|(p->bnx==3?0:1))], p, dst, src, dir, s );
    } else {
        lk_fft2d_r2c_perm_b( &kern[START_R2C+dir*48+(p->id<<4)+(p->bny-1)], p, dst, src, dir, s );
    }
}
static void fft2d_r2c_grad_a( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    if((p->pad_l|p->pad_t)!=0){
        lk_fft2d_r2c_perm_pad( &kern[START_R2C_PAD+(p->id<<4)+p->pad_t], p, dst, src, 1, s );
    } else {
        lk_fft2d_r2c_perm_a( &kern[START_R2C+(p->id<<4)+(p->any-1)], p, dst, src, 1, s );
    }
}
static void fft2d_r2c_grad_b( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    lk_fft2d_r2c_perm_b( &kern[START_R2C+(p->id<<4)+(p->bny-1)], p, dst, src, 1, s );
}
static void fft2d_r2c_grid( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{   
    uint32_t id=START_R2C_X+p->id*3;
    if((p->pad_r|p->pad_t)!=0){
        lk_fft2d_r2c_grid_perm_pad( &kern[id+2], p, dst, src, s );
    } else {
        uint32_t nx=p->tile_x*p->grid_x+p->bnx-1;
        uint32_t ny=p->tile_y*p->grid_y+p->bny-1;
        uint32_t ex=((nx!=p->anx)||(ny!=p->any))?1:0;
        lk_fft2d_r2c_grid_perm( &kern[id+ex], p, dst, src, s );
    }
}
static void fft2d_r2c_xgrad_a( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{   
    uint32_t id=START_R2C_Xg+(p->id<<2);
    if((p->pad_r|p->pad_t)!=0){
        lk_fft2d_r2c_grid_perm_pad( &kern[id+2], p, dst, src, s );
    } else {
        uint32_t nx=p->tile_x*p->grid_x+p->bnx-1;
        uint32_t ny=p->tile_y*p->grid_y+p->bny-1;
        uint32_t ex=((nx!=p->anx)||(ny!=p->any))?1:0;
        lk_fft2d_r2c_grid_perm( &kern[id+ex], p, dst, src, s );
    }
}
static void fft2d_r2c_xgrad_b( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{   
    lk_fft2d_r2c_grid_perm_nov( &kern[START_R2C_Xg+((p->id<<2)|3)], p, dst, src, s );
}
static void fft2d_c2r( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t relu, hipStream_t s )
{   
    lk_fft2d_c2r_perm( &kern[START_C2R+(p->id<<5)+(relu<<(p->id+4))+p->cny-1], p, dst, src, s );
}
static void fft2d_c2r_grid( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t relu, hipStream_t s )
{   
    lk_fft2d_c2r_grid_perm( &kern[START_C2R_X+((p->id<<1)|relu)], p, dst, src, s );
}
static void fft2d_c2r_grad( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    if((p->cnx==p->cny)&&((p->cnx==3)||(p->cnx==5)||(p->cnx==7))){
        lk_fft2d_c2r_grad_perm_s( &kern[START_C2R_S+11*p->id+8+(p->cnx>>1)-1], p, dst, src, s );
    } else
    if((p->cnx==1)&&((p->cny&0x1)&&(p->cny>1)&&(p->cny<=9))){
        lk_fft2d_c2r_grad_perm_s( &kern[START_C2R_S+11*p->id+4+(p->cny>>1)-1], p, dst, src, s );
    } else
    if((p->cny==1)&&((p->cnx&0x1)&&(p->cnx>1)&&(p->cnx<=9))){
        lk_fft2d_c2r_grad_perm_s( &kern[START_C2R_S+11*p->id+0+(p->cnx>>1)-1], p, dst, src, s );
    } else {
        lk_fft2d_c2r_grad_perm( &kern[START_C2R+(p->id<<5)+p->cny-1], p, dst, src, s );
    }
}

__local_func void fftconv2d( context_t* ctx, const param_fftconv_t* p, void* aux, void* dst, void* src, void* filter, float alpha, uint32_t relu, uint32_t dir, hipStream_t s )
{
    kernel_t* kern=ctx->kern_fft;
    uint8_t* a=(uint8_t*)aux;
    uint8_t* b=a+(((uint64_t)(p->nbanks*p->abks))<<3);
    uint8_t* c=b+(((uint64_t)(p->nbanks*p->bbks))<<3);
    float coef=alpha*(p->id==0?0.00390625f:0.0009765625f);
    if((p->grid_x|p->grid_y)>1){
        fft2d_r2c_grid( kern, p, a, src, s );
        fft2d_r2c_b( kern, p, b, filter, dir, s );
        lk_cgemm( kern, p, c, a, b, coef, s );
        fft2d_c2r_grid( kern, p, dst, c, relu, s );
    } else {
        fft2d_r2c_a( kern, p, a, src, s );
        fft2d_r2c_b( kern, p, b, filter, dir, s );
        lk_cgemm( kern, p, c, a, b, coef, s );
        fft2d_c2r( kern, p, dst, c, relu, s );
    }
}
__local_func void fftconv2d_grad( context_t* ctx, const param_fftconv_t* p, void* aux, void* dst, void* x, void* y, float alpha, hipStream_t s )
{
    kernel_t* kern=ctx->kern_fft;
    uint8_t* a=(uint8_t*)aux;
    uint8_t* b=a+(((uint64_t)(p->nbanks*p->abks))<<3);
    uint8_t* c=b+(((uint64_t)(p->nbanks*p->bbks))<<3);
    float coef=alpha*(p->id==0?0.00390625f:0.0009765625f);
    if((p->grid_x|p->grid_y)>1){
        fft2d_r2c_xgrad_a( kern, p, a, x, s );
        fft2d_r2c_xgrad_b( kern, p, b, y, s );
    } else {
        fft2d_r2c_grad_a( kern, p, a, x, s );
        fft2d_r2c_grad_b( kern, p, b, y, s );
    }
    lk_cgemm( kern, p, c, a, b, coef, s );
    fft2d_c2r_grad( kern, p, dst, c, s );
}