#ifndef __op_cgemm_h__
#define __op_cgemm_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_cgemm( kernel_t*, const param_fftconv_t*, void*, void*, void*, float, hipStream_t );

#endif