#include"../include/op_cellconv.h"

__local_func void lk_co3x3_dt( kernel_t* kern, const param_cellconv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[128];
    uint32_t ext=((p->grid_x*6+2)!=p->anx)||((p->grid_y*6+2)!=p->any)?1:0;
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &((kern=&kern[p->pad!=0?2:ext])->argsize), HIP_LAUNCH_PARAM_END };
    uint32_t ldy=p->anx*p->any;
    uint32_t sgs=ldy*p->k;
    uint32_t ldx=sgs*p->ng;
    *((void*   *)&argbuf[0x00])=dst      ;
    *((uint32_t*)&argbuf[0x08])=p->abks  ;
    *((uint32_t*)&argbuf[0x0c])=p->lda   ;
    *((uint32_t*)&argbuf[0x10])=p->grid_x;
    *((uint32_t*)&argbuf[0x14])=p->grid_y;
    *((magic_t *)&argbuf[0x18])=p->xmag  ;
    *((magic_t *)&argbuf[0x20])=p->ymag  ;
    *((uint32_t*)&argbuf[0x28])=ldy      ;
    *((uint32_t*)&argbuf[0x2c])=sgs      ;
    *((void*   *)&argbuf[0x30])=src      ;
    *((uint32_t*)&argbuf[0x38])=ldx      ;
    *((uint32_t*)&argbuf[0x3c])=p->anx   ;
    *((uint32_t*)&argbuf[0x40])=p->any   ;
    *((uint32_t*)&argbuf[0x44])=p->bs    ;
    if(p->pad!=0){ *((uint32_t*)&argbuf[0x48])=p->pad; }
    HIP_LAUNCH( kern, (p->m+63)>>6, p->k, p->ng, s, config );
}
__local_func void lk_co3x3_ft( kernel_t* kern, const param_cellconv_t* p, void* dst, void* src, uint32_t dir, hipStream_t s )
{
    char argbuf[64];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t lds=9*(dir==0?(p->ng*p->k):1);
    uint32_t gdx=((p->n)+63)>>6;
    uint32_t gdy=p->k;
    *((void*   *)&argbuf[0x00])=dst    ;
    *((uint32_t*)&argbuf[0x08])=p->bbks;
    *((uint32_t*)&argbuf[0x0c])=p->ldb ;
    *((void*   *)&argbuf[0x10])=src    ;
    *((uint32_t*)&argbuf[0x18])=p->k   ;
    *((uint32_t*)&argbuf[0x1c])=p->n   ;
    *((uint32_t*)&argbuf[0x20])=lds    ;
    HIP_LAUNCH( &kern[dir], dir==0?gdy:gdx, dir==0?gdx:gdy, p->ng, s, config );
}
void lk_co3x3_mm( kernel_t* kern, const param_cellconv_t* p, void* a, void* b, void* c, float alpha, hipStream_t s )
{
    char argbuf[64];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t u=(p->m+63)>>6;
    uint32_t v=(p->n+31)>>5;
    uint32_t y=(1u^(v&1u))+((((v&3u)==0)&&((p->k&15u)==0))?1:0);
    uint32_t x=(1u^(u&1u))+((((u&3u)==0)&&(y!=2))?1:0);
    uint32_t tilex=6+x;
    uint32_t tiley=5+y;
    *((void*   *)&argbuf[0x00])=a      ;
    *((void*   *)&argbuf[0x08])=b      ;
    *((uint32_t*)&argbuf[0x10])=p->abks;
    *((uint32_t*)&argbuf[0x14])=p->bbks;
    *((uint32_t*)&argbuf[0x18])=p->lda ;
    *((uint32_t*)&argbuf[0x1c])=p->ldb ;
    *((uint32_t*)&argbuf[0x20])=p->m   ;
    *((uint32_t*)&argbuf[0x24])=p->n   ;
    *((uint32_t*)&argbuf[0x28])=p->k   ;
    *((float   *)&argbuf[0x2c])=alpha  ;
    *((void*   *)&argbuf[0x30])=c      ;
    *((uint32_t*)&argbuf[0x38])=p->lda ;
    *((uint32_t*)&argbuf[0x3c])=p->cbks;
    HIP_LAUNCH( &kern[y!=2?(y*3+x):6], (p->m+(1<<tilex)-1)>>tilex, (p->n+(1<<tiley)-1)>>tiley, p->ng<<6, s, config );
}
__local_func void lk_co3x3_ot( kernel_t* kern, const param_cellconv_t* p, void* dst, void* src, uint32_t relu, hipStream_t s )
{
    char argbuf[128];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t ldy=p->cnx*p->cny;
    uint32_t dgs=ldy*p->n;
    uint32_t ldx=dgs*p->ng;
    uint32_t ext=((p->grid_x*6)!=p->cnx)||((p->grid_y*6)!=p->cny)?1:0;
    *((void*   *)&argbuf[0x00])=src      ;
    *((uint32_t*)&argbuf[0x08])=p->cbks  ;
    *((uint32_t*)&argbuf[0x0c])=p->lda   ;
    *((uint32_t*)&argbuf[0x10])=p->grid_x;
    *((uint32_t*)&argbuf[0x14])=p->grid_y;
    *((magic_t *)&argbuf[0x18])=p->xmag  ;
    *((magic_t *)&argbuf[0x20])=p->ymag  ;
    *((uint32_t*)&argbuf[0x28])=ldy      ;
    *((uint32_t*)&argbuf[0x2c])=dgs      ;
    *((void*   *)&argbuf[0x30])=dst      ;
    *((uint32_t*)&argbuf[0x38])=ldx      ;
    *((uint32_t*)&argbuf[0x3c])=p->cnx   ;
    *((uint32_t*)&argbuf[0x40])=p->cny   ;
    *((uint32_t*)&argbuf[0x44])=p->bs    ;
    HIP_LAUNCH( &kern[(ext<<1)|relu], (p->m+63)>>6, p->n, p->ng, s, config );
}