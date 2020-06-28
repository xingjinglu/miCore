#include"../include/op_conv.h"

__local_func void lk_perm_flip( kernel_t* kern, const param_conv_t* p, void* dst, void* src, hipStream_t s )
{
    char argbuf[64];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    uint32_t bnn=p->bnx*p->bny;
    uint32_t lda=p->ng*p->n*bnn;
    uint32_t ldb=PSIZE(p->n,3);
    uint32_t align=p->id!=3?7:15;
    uint32_t pk=PSIZE(p->k,align);
    *((void*   *)&argbuf[0x00])=dst ;
    *((void*   *)&argbuf[0x08])=src ;
    *((uint32_t*)&argbuf[0x10])=lda ;
    *((uint32_t*)&argbuf[0x14])=ldb ;
    *((uint32_t*)&argbuf[0x18])=p->k;
    *((uint32_t*)&argbuf[0x1c])=p->n;
    *((uint32_t*)&argbuf[0x20])=bnn ;
    *((uint32_t*)&argbuf[0x24])=pk  ;
    HIP_LAUNCH( kern, (ldb+63)>>6, p->inc, p->ng, s, config );
}
__local_func void lk_fconv( kernel_t* kern, const param_conv_t* p, void* aux, void* c, void* a, void* b, float alpha, hipStream_t s )
{
    char argbuf[128];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    void* amap=aux;
    void* relo=(void*)(((char*)amap)+(p->ntidx<<3));
    uint32_t shx=4+((0x34434>>(p->id<<2))&0xf);
    uint32_t shy=4+((0x32101>>(p->id<<2))&0xf);
    uint32_t flag=p->pad!=0?0x80000000:0;
    uint32_t gdx=p->ntidx>>shx;
    uint32_t gdy=(p->n+(1<<shy)-1)>>shy;
    *((void*   *)&argbuf[0x00])=amap      ;
    *((void*   *)&argbuf[0x08])=relo      ;
    *((uint32_t*)&argbuf[0x10])=p->k*p->ng;
    *((uint32_t*)&argbuf[0x14])=flag|p->n ;
    *((uint32_t*)&argbuf[0x18])=p->k      ;
    *((uint32_t*)&argbuf[0x1c])=p->ags    ;
    *((void*   *)&argbuf[0x20])=a         ;
    *((void*   *)&argbuf[0x28])=b         ;
    *((void*   *)&argbuf[0x30])=c         ;
    *((float   *)&argbuf[0x38])=alpha     ;
    *((uint32_t*)&argbuf[0x3c])=p->m      ;
    *((uint32_t*)&argbuf[0x40])=p->ldc    ;
    HIP_LAUNCH( kern, p->pad!=0?gdx:gdy, p->pad!=0?gdy:gdx, p->ng, s, config );
}
__local_func void lk_bconv( kernel_t* kern, const param_conv_t* p, void* aux, void* c, void* a, void* b, float alpha, hipStream_t s )
{
    char argbuf[128];
    void* config[5]={ HIP_LAUNCH_PARAM_BUFFER_POINTER, &argbuf[0], HIP_LAUNCH_PARAM_BUFFER_SIZE, &kern->argsize, HIP_LAUNCH_PARAM_END };
    void* amap=aux;
    void* relo=(void*)(((char*)amap)+(p->ntidx<<3));
    uint32_t ldb=PSIZE(p->n,3);
    uint32_t align=p->id!=3?7:15;
    uint32_t pk=PSIZE(p->k,align);
    uint32_t n=(p->pad!=0?0x80000000:0)|p->n;
    uint32_t shx=(p->id>0)&&(p->id<3)?8:7;
    uint32_t shy=4+p->id;
    uint32_t gdx=p->ntidx>>shx;
    uint32_t gdy=(ldb+(1<<shy)-1)>>shy;
    *((void*   *)&argbuf[0x00])=amap  ;
    *((void*   *)&argbuf[0x08])=relo  ;
    *((uint32_t*)&argbuf[0x10])=ldb   ;
    *((uint32_t*)&argbuf[0x14])=n     ;
    *((uint32_t*)&argbuf[0x18])=pk    ;
    *((uint32_t*)&argbuf[0x1c])=p->ags;
    *((void*   *)&argbuf[0x20])=a     ;
    *((void*   *)&argbuf[0x28])=b     ;
    *((void*   *)&argbuf[0x30])=c     ;
    *((float   *)&argbuf[0x38])=alpha ;
    *((uint32_t*)&argbuf[0x3c])=p->m  ;
    *((uint32_t*)&argbuf[0x40])=p->ldc;
    HIP_LAUNCH( kern, p->pad!=0?gdx:gdy, p->pad!=0?gdy:gdx, p->ng, s, config );
}