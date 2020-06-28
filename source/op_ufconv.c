#include"../include/op_ufconv.h"

__local_func void lk_ufconv( kernel_t* kern, const param_ufconv_t* p, void* c, void* a, void* b, float alpha, hipStream_t s )
{
    char argbuf[64];
    void* config[]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t id=p->id&0xffff;
    uint32_t shx=(id>0)&&(id<3)?8:7;
    uint32_t shy=4+id;
    *((void*   *)&argbuf[0x00])=a      ;
    *((void*   *)&argbuf[0x08])=b      ;
    *((uint32_t*)&argbuf[0x10])=p->ng  ;
    *((uint32_t*)&argbuf[0x14])=p->m   ;
    *((uint32_t*)&argbuf[0x18])=p->n   ;
    *((uint32_t*)&argbuf[0x1c])=p->k   ;
    *((magic_t *)&argbuf[0x20])=p->amag;
    *((magic_t *)&argbuf[0x28])=p->cmag;
    *((void*   *)&argbuf[0x30])=c      ;
    *((float   *)&argbuf[0x38])=alpha  ;
    *((uint32_t*)&argbuf[0x3c])=p->dimx;
    HIP_LAUNCH( kern, (p->n+(1<<shy)-1)>>shy, p->ntidx>>shx, p->ng, s, config );
}