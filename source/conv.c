#include"../include/conv.h"
#include"../include/op_padding.h"
#include"../include/op_genidx.h"

__local_func void fconv( context_t* ctx, const param_conv_t* p, void* aux, void* c, void* a, void* b, float alpha, uint32_t relu, hipStream_t s )
{
    void* ibuf=(void*)(((char*)aux)+p->spad);
    if(p->pad!=0){ lk_padding2d( &ctx->kern[0], p, aux, a, s ); }
    lk_genidx_conv2d( &ctx->kern_idx[0], p, ibuf, s );
    lk_fconv( &ctx->kern_fco[(p->id<<1)|relu], p, ibuf, c, p->pad!=0?aux:a, b, alpha, s );
}
__local_func void bconv( context_t* ctx, const param_conv_t* p, void* aux, void* c, void* a, void* b, float alpha, hipStream_t s )
{
    void* ibuf=(void*)(((char*)aux)+p->spad);
    void* x=(void*)(((char*)ibuf)+p->sidx);
    if(p->pad!=0){ lk_padding2d( &ctx->kern[0], p, aux, a, s ); }
    lk_perm_flip( &ctx->kern_perm[0], p, x, b, s );
    lk_genidx_conv2d( &ctx->kern_idx[0], p, ibuf, s );
    lk_bconv( &ctx->kern_bco[p->id], p, ibuf, c, p->pad!=0?aux:a, x, alpha, s );
}