#ifndef __op_genidx_h__
#define __op_genidx_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_genidx_conv2d( kernel_t*, const param_conv_t*, void*, hipStream_t );

#endif