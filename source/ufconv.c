#include"../include/ufconv.h"

__local_func void uffconv( context_t* ctx, const param_ufconv_t* p, void* c, void* a, void* b, float alpha, uint32_t relu, hipStream_t s )
{
    lk_ufconv( &ctx->kern_ufco[(p->id&0xffff)*6+(((p->id>>16)<<1)|relu)], p, c, a, b, alpha, s );
}
__local_func void ufbconv( context_t* ctx, const param_ufconv_t* p, void* c, void* a, void* b, float alpha, hipStream_t s )
{
    lk_ufconv( &ctx->kern_ufco[24+(p->id&0xffff)*3+(p->id>>16)], p, c, a, b, alpha, s );
}