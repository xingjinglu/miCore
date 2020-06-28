#ifndef __op_conv_h__
#define __op_conv_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_co3x3_dt( kernel_t*, const param_cellconv_t*, void*, void*, hipStream_t );
__local_func void lk_co3x3_ft( kernel_t*, const param_cellconv_t*, void*, void*, uint32_t, hipStream_t );
__local_func void lk_co3x3_mm( kernel_t*, const param_cellconv_t*, void*, void*, void*, float, hipStream_t );
__local_func void lk_co3x3_ot( kernel_t*, const param_cellconv_t*, void*, void*, uint32_t, hipStream_t );

#endif