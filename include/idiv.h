#ifndef __idiv_h__
#define __idiv_h__

#include"bim.h"

typedef struct{
    uint32_t m;
    uint32_t s;
} magic_t;

magic_t idiv_magic( uint32_t, uint32_t );

#endif