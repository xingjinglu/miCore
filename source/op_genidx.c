#include"../include/op_genidx.h"

__local_func void lk_genidx_conv2d( kernel_t* kern, const param_conv_t* p, void* idx, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t npx=p->pnx*p->pny;
    uint32_t inc=p->ng*p->inc;
    uint32_t onc=p->ng*p->n;
    uint32_t ldx=npx*(p->pad==0?inc:1);
    uint32_t srelo=PSIZE(p->k,7)+32;
    uint32_t ntid=p->ntidx>srelo?p->ntidx:srelo;
    *((void*   *)&argbuf[0x00])=idx;
    *((uint32_t*)&argbuf[0x08])=p->ntidx;
    *((uint32_t*)&argbuf[0x0c])=p->pnx  ;
    *((uint32_t*)&argbuf[0x10])=p->sd   ;
    *((uint32_t*)&argbuf[0x14])=ldx     ;
    *((uint32_t*)&argbuf[0x18])=onc     ;
    *((uint32_t*)&argbuf[0x1c])=p->m    ;
    *((uint32_t*)&argbuf[0x20])=p->cnx  ;
    *((uint32_t*)&argbuf[0x24])=p->cny  ;
    *((uint32_t*)&argbuf[0x28])=p->bnx  ;
    *((uint32_t*)&argbuf[0x2c])=p->bny  ;
    *((uint32_t*)&argbuf[0x30])=p->lda  ;
    *((uint32_t*)&argbuf[0x34])=p->k    ;
    HIP_LAUNCH( kern, (ntid+63)>>6, 1, 1, s, config );
}