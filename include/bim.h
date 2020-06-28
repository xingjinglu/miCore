#ifndef __bim_h__
#define __bim_h__

#include<stdint.h>
#include<x86intrin.h>
#include"macro.h"

__local_func uint32_t bim_clz( uint32_t );
__local_func uint32_t bim_fls( uint32_t );

#endif