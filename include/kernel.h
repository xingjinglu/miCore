#ifndef __kernel_h__
#define __kernel_h__

#include<hip/hip_runtime_api.h>
#include<stdint.h>
#include"macro.h"

#define HIP_LAUNCH(kern,gdx,gdy,gdz,s,config) (kern)->launch( (kern)->id, gdx, gdy, gdz, (const uint32_t*)&(kern)->block[0], s, config )

typedef struct{
    hipError_t (*launch)( hipFunction_t, uint32_t, uint32_t, uint32_t, const uint32_t*, hipStream_t, void** );
    size_t        argsize;
    hipFunction_t id;
    uint32_t      block[3];
} kernel_t;

__local_func void init_kernel( kernel_t* );

#endif