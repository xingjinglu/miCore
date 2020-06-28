#ifndef __cellconv_h__
#define __cellconv_h__

#include"context.h"
#include"param.h"

__local_func void cellconv2d( context_t*, const param_cellconv_t*, void*, void*, void*, void*, float, uint32_t, uint32_t, hipStream_t );

#endif