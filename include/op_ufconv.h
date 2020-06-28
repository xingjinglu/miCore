#ifndef __op_ufconv_h__
#define __op_ufconv_h__

#include"kernel.h"
#include"param.h"

__local_func void lk_uffconv( kernel_t*, const param_ufconv_t*, void*, void*, void*, float, hipStream_t );

#endif