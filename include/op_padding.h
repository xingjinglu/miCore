#ifndef __op_padding_h__
#define __op_padding_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_padding2d( kernel_t*, const param_conv_t*, void*, void*, hipStream_t );

#endif