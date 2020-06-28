#include"../include/op_padding.h"

__local_func void lk_padding2d( kernel_t* kern, const param_conv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t inc=p->ng*p->inc;
    *((void*   *)&argbuf[0x00])=dst   ;
    *((void*   *)&argbuf[0x08])=src   ;
    *((uint32_t*)&argbuf[0x10])=p->anx;
    *((uint32_t*)&argbuf[0x14])=p->any;
    *((uint32_t*)&argbuf[0x18])=p->pad;
    *((uint32_t*)&argbuf[0x1c])=inc   ;
    *((uint32_t*)&argbuf[0x20])=p->lda;
    HIP_LAUNCH( kern, (p->pnx*p->pny*inc+255)>>8, p->bs, 1, s, config );
}