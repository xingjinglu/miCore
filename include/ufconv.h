#ifndef __ufconv_h__
#define __ufconv_h__

#include"context.h"
#include"op_ufconv.h"

__local_func void uffconv( context_t*, const param_ufconv_t*, void*, void*, void*, float, uint32_t, hipStream_t );
__local_func void ufbconv( context_t*, const param_ufconv_t*, void*, void*, void*, float, hipStream_t );

#endif
