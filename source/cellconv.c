#include"../include/cellconv.h"
#include"../include/op_cellconv.h"

#define START_MM 0
#define START_DT (START_MM+7)
#define START_FT (START_DT+3)
#define START_OT (START_FT+2)

__local_func void cellconv2d( context_t* ctx, const param_cellconv_t* p, void* aux, void* dst, void* src, void* filter, float alpha, uint32_t relu, uint32_t dir, hipStream_t s )
{
    char* a=(char*)aux;
    char* b=a+((p->abks*p->ng)<<8);
    char* c=b+((p->bbks*p->ng)<<8);
    lk_co3x3_dt( &ctx->kern_cell[START_DT], p, a, src, s );
    lk_co3x3_ft( &ctx->kern_cell[START_FT], p, b, filter, dir, s );
    lk_co3x3_mm( &ctx->kern_cell[START_MM], p, a, b, c, alpha, s );
    lk_co3x3_ot( &ctx->kern_cell[START_OT], p, dst, c, relu, s );
}