#ifndef __param_h__
#define __param_h__

#include<stdlib.h>
#include"istatus.h"
#include"tensorshape.h"
#include"idiv.h"
#include"macro.h"

typedef struct{
    size_t   sperm;
    uint32_t id   ;
    uint32_t ng   ;
    uint32_t m    ;
    uint32_t n    ;
    uint32_t k    ;
    uint32_t dimx ;
    uint32_t ntidx;
} param_ufconv_t;

typedef struct{
    size_t   spad ;
    size_t   sidx ;
    size_t   sperm;
    uint32_t id   ;
    uint32_t ng   ;
    uint32_t bs   ;
    uint32_t pad  ;
    uint32_t sd   ;
    uint32_t pnx  ;
    uint32_t pny  ;
    uint32_t anx  ;
    uint32_t any  ;
    uint32_t bnx  ;
    uint32_t bny  ;
    uint32_t cnx  ;
    uint32_t cny  ;
    uint32_t lda  ;
    uint32_t ldc  ;
    uint32_t inc  ;
    uint32_t m    ;
    uint32_t n    ;
    uint32_t k    ;
    uint32_t ags  ;
    uint32_t ntidx;
} param_conv_t;

typedef struct{
    magic_t  xmag  ;
    magic_t  ymag  ;
    uint32_t grid_x;
    uint32_t grid_y;
    uint32_t pad   ;
    uint32_t anx   ;
    uint32_t any   ;
    uint32_t cnx   ;
    uint32_t cny   ;
    uint32_t bs    ;
    uint32_t ng    ;
    uint32_t m     ;
    uint32_t n     ;
    uint32_t k     ;
    uint32_t abks  ;
    uint32_t bbks  ;
    uint32_t cbks  ;
    uint32_t lda   ;
    uint32_t ldb   ;
    uint32_t dir   ;
} param_cellconv_t;

typedef struct{
    magic_t  xmag  ;
    magic_t  ymag  ;
    uint32_t grid_x;
    uint32_t grid_y;
    uint32_t tile_x;
    uint32_t tile_y;
    uint32_t m     ;
    uint32_t n     ;
    uint32_t k     ;
    uint32_t lda   ;
    uint32_t ldb   ;
    uint32_t abks  ;
    uint32_t bbks  ;
    uint32_t cbks  ;
    uint32_t aldx  ;
    uint32_t aldy  ;
    uint32_t bldx  ;
    uint32_t bldy  ;
    uint32_t cldx  ;
    uint32_t cldy  ;
    uint32_t anx   ;
    uint32_t any   ;
    uint32_t bnx   ;
    uint32_t bny   ;
    uint32_t cnx   ;
    uint32_t cny   ;
    uint32_t pad_l ;
    uint32_t pad_r ;
    uint32_t pad_t ;
    uint32_t pad_b ;
    uint32_t nbanks;
    uint32_t id    ;
} param_fftconv_t;

__local_func int build_param_uffconv( param_ufconv_t*, const tensorshape_t*, const tensorshape_filter_t*, uint32_t );
__local_func int build_param_ufbconv( param_ufconv_t*, const tensorshape_t*, const tensorshape_filter_t*, uint32_t );
__local_func int build_param_fconv( param_conv_t*, const tensorshape_t*, const tensorshape_filter_t*, const tensorshape_t*, uint32_t, uint32_t, uint32_t, uint32_t );
__local_func int build_param_bconv( param_conv_t*, const tensorshape_t*, const tensorshape_filter_t*, const tensorshape_t*, uint32_t, uint32_t, uint32_t, uint32_t );
__local_func int build_param_cellconv( param_cellconv_t*, const tensorshape_t*, const tensorshape_t*, uint32_t, uint32_t, uint32_t );
__local_func int build_param_fftconv( param_fftconv_t*, const tensorshape_t*, const tensorshape_filter_t*, const tensorshape_t*, uint32_t, uint32_t );
__local_func int build_param_fftconv_grad( param_fftconv_t*, const tensorshape_t*, const tensorshape_t*, const tensorshape_filter_t*, uint32_t );

#endif