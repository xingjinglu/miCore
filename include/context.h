#ifndef __context_h__
#define __context_h__

#include<stdlib.h>
#include"kernel.h"
#include"istatus.h"

typedef struct{
    hipDevice_t device;
    hipModule_t module;
    kernel_t*   kern;
    kernel_t*   kern_idx;
    kernel_t*   kern_ufco;
    kernel_t*   kern_fco;
    kernel_t*   kern_bco;
    kernel_t*   kern_cell;
    kernel_t*   kern_fft;
    int         arch;
    int         ncu;
} context_t;

__local_func int  context_init( context_t* );
__local_func void context_release( context_t* );

#endif