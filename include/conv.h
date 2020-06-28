#ifndef __conv_h__
#define __conv_h__

#include"context.h"
#include"op_conv.h"

__local_func void fconv( context_t*, const param_conv_t*, void*, void*, void*, void*, float, uint32_t, hipStream_t );
__local_func void bconv( context_t*, const param_conv_t*, void*, void*, void*, void*, float, hipStream_t );


#endif