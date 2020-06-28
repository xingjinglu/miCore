#include"../include/op_fft.h"

__local_func void lk_fft2d_r2c_perm_a( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t g, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t m=(g<<31)|p->m;
    uint32_t gdx=(p->m+15)>>4;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->lda ;
    *((uint32_t*)&argbuf[0x0c])=p->abks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=m      ;
    *((uint32_t*)&argbuf[0x1c])=p->anx ;
    *((uint32_t*)&argbuf[0x20])=p->aldx;
    *((uint32_t*)&argbuf[0x24])=p->aldy;
    HIP_LAUNCH( kern, g?gdx:p->k, g?p->k:gdx, 1, s, config );
}
__local_func void lk_fft2d_r2c_perm_b( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t flag, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t n=(flag<<31)|p->n;
    uint32_t gdx=(p->n+15)>>4;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->ldb ;
    *((uint32_t*)&argbuf[0x0c])=p->bbks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=n      ;
    *((uint32_t*)&argbuf[0x1c])=p->bnx ;
    *((uint32_t*)&argbuf[0x20])=p->bldx;
    *((uint32_t*)&argbuf[0x24])=p->bldy;
    HIP_LAUNCH( kern, flag==0?p->k:gdx, flag==0?gdx:p->k, 1, s, config );
}
__local_func void lk_fft2d_r2c_perm_pad( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t g, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t pad=(g<<31)|p->pad_l;
    uint32_t gdx=(p->m+15)>>4;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->lda ;
    *((uint32_t*)&argbuf[0x0c])=p->abks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->m   ;
    *((uint32_t*)&argbuf[0x1c])=pad    ;
    *((uint32_t*)&argbuf[0x20])=p->aldx;
    *((uint32_t*)&argbuf[0x24])=p->aldy;
    *((uint32_t*)&argbuf[0x28])=p->anx ;
    *((uint32_t*)&argbuf[0x2c])=p->any ;
    HIP_LAUNCH( kern, g?gdx:p->k, g?p->k:gdx, 1, s, config );
}
__local_func void lk_fft2d_r2c_perm_s( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, uint32_t dir, hipStream_t s )
{
    char argbuf[32];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t ldr=p->bnx*p->bny*(dir==0?p->k:p->n);
    uint32_t gdx=(p->n+15)>>4;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->ldb ;
    *((uint32_t*)&argbuf[0x0c])=p->bbks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->n   ;
    *((uint32_t*)&argbuf[0x1c])=ldr    ;
    HIP_LAUNCH( kern, dir==0?p->k:gdx, dir==0?gdx:p->k, 1, s, config );
}
__local_func void lk_fft2d_r2c_grid_perm( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[128];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t grid=(p->grid_y<<16)|p->grid_x;
    uint32_t tile=(p->tile_y<<16)|p->tile_x;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->lda ;
    *((uint32_t*)&argbuf[0x0c])=p->abks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->m   ;
    *((uint32_t*)&argbuf[0x1c])=p->anx ;
    *((uint32_t*)&argbuf[0x20])=p->aldx;
    *((uint32_t*)&argbuf[0x24])=p->aldy;
    *((uint32_t*)&argbuf[0x28])=grid   ;
    *((uint32_t*)&argbuf[0x2c])=tile   ;
    *((magic_t *)&argbuf[0x30])=p->xmag;
    *((magic_t *)&argbuf[0x38])=p->ymag;
    *((uint32_t*)&argbuf[0x40])=p->any ;
    HIP_LAUNCH( kern, (p->m+15)>>4, p->k, 1, s, config );
}
__local_func void lk_fft2d_r2c_grid_perm_pad( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[128];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t grid=(p->grid_y<<16)|p->grid_x;
    uint32_t tile=(p->tile_y<<16)|p->tile_x;
    uint32_t pad=(p->pad_t<<16)|p->pad_l;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->lda ;
    *((uint32_t*)&argbuf[0x0c])=p->abks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->m   ;
    *((uint32_t*)&argbuf[0x1c])=p->anx ;
    *((uint32_t*)&argbuf[0x20])=p->aldx;
    *((uint32_t*)&argbuf[0x24])=p->aldy;
    *((uint32_t*)&argbuf[0x28])=grid   ;
    *((uint32_t*)&argbuf[0x2c])=tile   ;
    *((magic_t *)&argbuf[0x30])=p->xmag;
    *((magic_t *)&argbuf[0x38])=p->ymag;
    *((uint32_t*)&argbuf[0x40])=p->any ;
    *((uint32_t*)&argbuf[0x44])=pad    ;
    HIP_LAUNCH( kern, (p->m+15)>>4, p->k, 1, s, config );
}
__local_func void lk_fft2d_r2c_grid_perm_nov( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[128];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t grid=(p->grid_y<<16)|p->grid_x;
    uint32_t tile=(p->tile_y<<16)|p->tile_x;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->ldb ;
    *((uint32_t*)&argbuf[0x0c])=p->bbks;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->n   ;
    *((uint32_t*)&argbuf[0x1c])=p->bnx ;
    *((uint32_t*)&argbuf[0x20])=p->bldx;
    *((uint32_t*)&argbuf[0x24])=p->bldy;
    *((uint32_t*)&argbuf[0x28])=grid   ;
    *((uint32_t*)&argbuf[0x2c])=tile   ;
    *((magic_t *)&argbuf[0x30])=p->xmag;
    *((magic_t *)&argbuf[0x38])=p->ymag;
    *((uint32_t*)&argbuf[0x40])=p->bny ;
    HIP_LAUNCH( kern, (p->n+15)>>4, p->k, 1, s, config );
}
__local_func void lk_fft2d_c2r_perm( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t shx=4-p->id;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->cldx;
    *((uint32_t*)&argbuf[0x0c])=p->cldy;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->lda ;
    *((uint32_t*)&argbuf[0x1c])=p->cbks;
    *((uint32_t*)&argbuf[0x20])=p->m   ;
    *((uint32_t*)&argbuf[0x24])=p->cnx ;
    HIP_LAUNCH( kern, (p->m+(1<<shx)-1)>>shx, p->n, 1, s, config );
}
__local_func void lk_fft2d_c2r_grid_perm( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[128];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t grid=(p->grid_y<<16)|p->grid_x;
    uint32_t tile=(p->tile_y<<16)|p->tile_x;
    uint32_t shx=4-p->id;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->cldx;
    *((uint32_t*)&argbuf[0x0c])=p->cldy;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->lda ;
    *((uint32_t*)&argbuf[0x1c])=p->cbks;
    *((magic_t *)&argbuf[0x20])=p->xmag;
    *((magic_t *)&argbuf[0x28])=p->ymag;
    *((uint32_t*)&argbuf[0x30])=grid   ;
    *((uint32_t*)&argbuf[0x34])=tile   ;
    *((uint32_t*)&argbuf[0x38])=p->cnx ;
    *((uint32_t*)&argbuf[0x3c])=p->cny ;
    *((uint32_t*)&argbuf[0x40])=p->m   ;
    HIP_LAUNCH( kern, (p->m+((1<<shx)-1))>>shx, p->n, 1, s, config );
}
__local_func void lk_fft2d_c2r_grad_perm( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t shx=4-p->id;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->cldx;
    *((uint32_t*)&argbuf[0x0c])=p->cldy;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->lda ;
    *((uint32_t*)&argbuf[0x1c])=p->cbks;
    *((uint32_t*)&argbuf[0x20])=p->m   ;
    *((uint32_t*)&argbuf[0x24])=p->cnx ;
    HIP_LAUNCH( kern, (p->m+((1<<shx)-1))>>shx, p->n, 1, s, config );
}
__local_func void lk_fft2d_c2r_grad_perm_s( kernel_t* kern, const param_fftconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[32];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t ldr=p->cnx*p->cny*p->m;
    uint32_t shx=4-p->id;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=ldr    ;
    *((uint32_t*)&argbuf[0x0c])=p->m   ;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->lda ;
    *((uint32_t*)&argbuf[0x1c])=p->cbks;
    HIP_LAUNCH( kern, (p->m+((1<<shx)-1))>>shx, p->n, 1, s, config );
}