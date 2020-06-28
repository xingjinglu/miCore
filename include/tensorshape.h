#ifndef __tensorshape_h__
#define __tensorshape_h__

#include<stdint.h>

typedef struct{
    uint32_t nx;
    uint32_t ny;
    uint32_t nz;
    uint32_t nc;
    uint32_t bs;
} tensorshape_t;

typedef struct{
    uint32_t nx;
    uint32_t ny;
    uint32_t nz;
    uint32_t pnc;
    uint32_t qnc;
} tensorshape_filter_t;

#endif