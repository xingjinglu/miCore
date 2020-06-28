#ifndef __fftconv_h__
#define __fftconv_h__

#include"context.h"
#include"param.h"

__local_func void fftconv2d( context_t*, const param_fftconv_t*, void*, void*, void*, void*, float, uint32_t, uint32_t, hipStream_t );
__local_func void fftconv2d_grad( context_t*, const param_fftconv_t*, void*, void*, void*, void*, float, hipStream_t );

#endif