#include"../include/micore.h"
#include"../include/ufconv.h"
#include"../include/conv.h"
#include"../include/cellconv.h"
#include"../include/fftconv.h"

#define CTX(h)     ((context_t*)(h))
#define TSHAPE(h)  ((tensorshape_t*)(h))
#define TSHAPEF(h) ((tensorshape_filter_t*)(h))
#define PUFCO(h)   ((param_ufconv_t  *)(h))
#define PCO(h)     ((param_conv_t    *)(h))
#define PCELLCO(h) ((param_cellconv_t*)(h))
#define PFFTCO(h)  ((param_fftconv_t *)(h))
#define ID(h)      (*((int*)(&((char*)h)[252])))

#ifdef __cplusplus
extern "C"
{
#endif

MICOREAPIENTRY micore_status_t micore_create_handle( micore_handle_t* p_handle )
{
    if((*p_handle=(micore_handle_t)malloc(sizeof(context_t)))==0)
        return micore_error_memory_alloc_failed;
    return ((micore_status_t)context_init(CTX(*p_handle)));
}
MICOREAPIENTRY micore_tensorshape_t micore_create_tensorshape()
{
    return ((micore_tensorshape_t)malloc(sizeof(tensorshape_t)));
}
MICOREAPIENTRY micore_parambox_t micore_create_parambox()
{
    return ((micore_parambox_t)malloc(256));
}
MICOREAPIENTRY void micore_set_tensorshape4d( micore_tensorshape_t shape, uint32_t nx, uint32_t ny, uint32_t nc, uint32_t bs )
{
    TSHAPE(shape)->nx=nx;
    TSHAPE(shape)->ny=ny;
    TSHAPE(shape)->nz=1u;
    TSHAPE(shape)->nc=nc;
    TSHAPE(shape)->bs=bs;
}
MICOREAPIENTRY void micore_set_tensorshape4d_filter( micore_tensorshape_t shape, uint32_t nx, uint32_t ny, uint32_t pnc, uint32_t qnc )
{
    TSHAPEF(shape)->nx =nx;
    TSHAPEF(shape)->ny =ny;
    TSHAPEF(shape)->nz =1u;
    TSHAPEF(shape)->pnc=pnc;
    TSHAPEF(shape)->qnc=qnc;
}
MICOREAPIENTRY micore_padding_t micore_make_padding2d( uint32_t pl, uint32_t pr, uint32_t pt, uint32_t pb )
{
    return ((pb<<24)|(pt<<16)|(pr<<8)|pl);
}
MICOREAPIENTRY micore_stride_t micore_make_stride2d( uint32_t su, uint32_t sv )
{
    return ((sv<<6)|su);
}
MICOREAPIENTRY micore_dilation_t micore_make_dilation2d( uint32_t du, uint32_t dv )
{
    return ((dv<<6)|du);
}
MICOREAPIENTRY micore_status_t micore_build_parambox_fconv( micore_parambox_t h, micore_conv_algo_t algo, uint32_t mask, micore_tensorshape_t sa, micore_tensorshape_t sb, micore_tensorshape_t sc, micore_padding_t pad, micore_stride_t str, micore_dilation_t dla, uint32_t ng )
{
    int status;
    ID(h)=(int)algo;
    if(algo==micore_conv_algo_flexgemm){
        if(((TSHAPEF(sb)->nx|TSHAPEF(sb)->ny|TSHAPEF(sb)->nz)==1)&&((pad|str|dla)==0)){
            status=build_param_ufconv( PUFCO(h), TSHAPE(sa), TSHAPEF(sb), ng, 0 );
        } else {
            status=build_param_fconv( PCO(h), TSHAPE(sa), TSHAPEF(sb), TSHAPE(sc), pad, str, dla, ng );
            ID(h)=1;
        }
    } else
    if(algo==micore_conv_algo_cell){
        if((TSHAPEF(sb)->nx!=3)||(TSHAPEF(sb)->ny!=3)) return micore_error_invalid_value;
        status=build_param_cellconv( PCELLCO(h), TSHAPE(sa), TSHAPE(sc), pad, ng, 0 );
    } else
    if(algo==micore_conv_algo_cellfft){
        status=build_param_fftconv( PFFTCO(h), TSHAPE(sa), TSHAPEF(sb), TSHAPE(sc), pad, 0 );
    }
    return ((micore_status_t)status);
}
MICOREAPIENTRY micore_status_t micore_build_parambox_bconv( micore_parambox_t h, micore_conv_algo_t algo, uint32_t mask, micore_tensorshape_t sa, micore_tensorshape_t sb, micore_tensorshape_t sc, micore_padding_t pad, micore_stride_t str, micore_dilation_t dla, uint32_t ng )
{
    int status;
    ID(h)=(int)algo;
    if(algo==micore_conv_algo_flexgemm){
        if(((TSHAPEF(sb)->nx|TSHAPEF(sb)->ny|TSHAPEF(sb)->nz)==1)&&((pad|str|dla)==0)){
            status=build_param_ufconv( PUFCO(h), TSHAPE(sc), TSHAPEF(sb), ng, 1 );
        } else {
            status=build_param_bconv( PCO(h), TSHAPE(sc), TSHAPEF(sb), TSHAPE(sa), pad, str, dla, ng );
            ID(h)=1;
        }
    } else
    if(algo==micore_conv_algo_cell){
        if((TSHAPEF(sb)->nx!=3)||(TSHAPEF(sb)->ny!=3)) return micore_error_invalid_value;
        status=build_param_cellconv( PCELLCO(h), TSHAPE(sa), TSHAPE(sc), pad, ng, 1 );
    } else
    if(algo==micore_conv_algo_cellfft){
        status=build_param_fftconv( PFFTCO(h), TSHAPE(sa), TSHAPEF(sb), TSHAPE(sc), pad, 1 );
    }
    return ((micore_status_t)status);
}
MICOREAPIENTRY micore_status_t micore_build_parambox_gconv( micore_parambox_t h, micore_conv_algo_t algo, uint32_t mask, micore_tensorshape_t sa, micore_tensorshape_t sb, micore_tensorshape_t sc, micore_padding_t pad, micore_stride_t str, micore_dilation_t dla, uint32_t ng )
{
    int status;
    ID(h)=(int)algo;
    if(algo==micore_conv_algo_cellfft){
        status=build_param_fftconv_grad( PFFTCO(h), TSHAPE(sa), TSHAPE(sc), TSHAPEF(sb), pad );
    }
    return ((micore_status_t)status);
}
MICOREAPIENTRY size_t micore_get_auxsize( micore_parambox_t h )
{
    size_t size=0;
    int algo=ID(h);
    if(algo==1){
        param_conv_t* p=PCO(h);
        size=((uint64_t)p->spad)+((uint64_t)p->sidx)+((uint64_t)p->sperm);
    } else
    if(algo==2){
        param_cellconv_t* p=PCELLCO(h);
        uint64_t abks=p->abks;
        uint64_t bbks=p->bbks;
        uint64_t cbks=p->cbks;
        size=((abks+bbks+cbks)*(p->ng<<8));
    } else
    if(algo==6){
        param_fftconv_t* p=PFFTCO(h);
        uint64_t abks=p->abks;
        uint64_t bbks=p->bbks;
        uint64_t cbks=p->cbks;
        size=((abks+bbks+cbks)*(p->nbanks<<3));
    }
    return size;
}
MICOREAPIENTRY void micore_fconv( micore_handle_t hCtx, micore_parambox_t hPar, void* aux, void* c, const void* a, const void* b, const void* bias, float alpha, uint32_t mask, hipStream_t s )
{
    int algo=ID(hPar);
    uint32_t relu=(mask>>3)&0x1;
    switch(algo){
    case 0 : uffconv( CTX(hCtx), PUFCO(hPar), c, (void*)a, (void*)b, alpha, relu, s ); break;
    case 1 : fconv( CTX(hCtx), PCO(hPar), aux, c, (void*)a, (void*)b, alpha, relu, s ); break;
    case 2 : cellconv2d( CTX(hCtx), PCELLCO(hPar), aux, c, (void*)a, (void*)b, alpha, relu, 0, s ); break;
    case 6 : fftconv2d( CTX(hCtx), PFFTCO(hPar), aux, c, (void*)a, (void*)b, alpha, relu, 0, s ); break;
    default : break;
    }
}
MICOREAPIENTRY void micore_bconv( micore_handle_t hCtx, micore_parambox_t hPar, void* aux, void* c, const void* a, const void* b, float alpha, hipStream_t s )
{
    int algo=ID(hPar);
    switch(algo){
    case 0 : ufbconv( CTX(hCtx), PUFCO(hPar), c, (void*)a, (void*)b, alpha, s ); break;
    case 1 : bconv( CTX(hCtx), PCO(hPar), aux, c, (void*)a, (void*)b, alpha, s ); break;
    case 2 : cellconv2d( CTX(hCtx), PCELLCO(hPar), aux, c, (void*)a, (void*)b, alpha, 0, 1, s ); break;
    case 6 : fftconv2d( CTX(hCtx), PFFTCO(hPar), aux, c, (void*)a, (void*)b, alpha, 0, 1, s ); break;
    default : break;
    }
}
MICOREAPIENTRY void micore_gconv( micore_handle_t hCtx, micore_parambox_t hPar, void* aux, void* c, const void* a, const void* b, float alpha, hipStream_t s )
{
    micore_conv_algo_t algo=(micore_conv_algo_t)ID(hPar);
    if(algo==micore_conv_algo_cellfft){
        fftconv2d_grad( CTX(hCtx), PFFTCO(hPar), aux, c, (void*)a, (void*)b, alpha, s );
    }
}
MICOREAPIENTRY void micore_release_tensorshape( micore_tensorshape_t h )
{
    if(h!=NULL){ free((void*)h); }
}
MICOREAPIENTRY void micore_release_parambox( micore_parambox_t h )
{
    if(h!=NULL){ free((void*)h); }
}
MICOREAPIENTRY void micore_release_handle( micore_handle_t h )
{
    if(h!=NULL){
        context_release(CTX(h));
        free((void*)h);
    }
}
#ifdef __cplusplus
}
#endif
