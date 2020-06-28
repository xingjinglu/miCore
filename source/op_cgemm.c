#include"../include/op_cgemm.h"

static uint32_t choose_cgemm_id( uint32_t m, uint32_t n )
{
    uint32_t mi=(m+31u)>>5;
    uint32_t ni=(n+15u)>>4;
    return (((0x12>>((ni&3)<<1))&0x3)+((mi&1)==0?0:3));
}
__local_func void lk_cgemm( kernel_t* kern, const param_fftconv_t* p, void* c, void* a, void* b, float coef, hipStream_t s )
{
    char argbuf[64];
    uint32_t kid=choose_cgemm_id( p->m, p->n );
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t shx=(0x666555>>(kid<<2))&0xf;
    uint32_t shy=(0x654654>>(kid<<2))&0xf;
    uint32_t shz=kid==0?1:0;
    uint32_t gdx=(p->m+(1<<shx)-1)>>shx;
    uint32_t gdy=(p->n+(1<<shy)-1)>>shy;
    *((void*   *)&argbuf[0x00])=c      ;
    *((uint32_t*)&argbuf[0x08])=p->lda ;
    *((uint32_t*)&argbuf[0x0c])=p->cbks;
    *((void*   *)&argbuf[0x10])=a      ;
    *((void*   *)&argbuf[0x18])=b      ;
    *((uint32_t*)&argbuf[0x20])=p->lda ;
    *((uint32_t*)&argbuf[0x24])=p->ldb ;
    *((uint32_t*)&argbuf[0x28])=p->m   ;
    *((uint32_t*)&argbuf[0x2c])=p->n   ;
    *((uint32_t*)&argbuf[0x30])=p->k   ;
    *((uint32_t*)&argbuf[0x34])=p->abks;
    *((uint32_t*)&argbuf[0x38])=p->bbks;
    *((float   *)&argbuf[0x3c])=coef   ;
    HIP_LAUNCH( &kern[(kid<<1)|((p->k&7)!=0?1:0)], gdx, gdy, p->nbanks>>shz, s, config );
}