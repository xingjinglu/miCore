#ifndef __op_conv_h__
#define __op_conv_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_perm_flip( kernel_t*, const param_conv_t*, void*, void*, hipStream_t );
__local_func void lk_fconv( kernel_t*, const param_conv_t*, void*, void*, void*, void*, float, hipStream_t );
__local_func void lk_bconv( kernel_t*, const param_conv_t*, void*, void*, void*, void*, float, hipStream_t );

#endif