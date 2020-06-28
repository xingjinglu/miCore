#include"../include/bim.h"

__local_func uint32_t bim_clz( uint32_t n )
{
    n^=n-1;
    n=(n&0x55555555)+((n>>1)&0x55555555);
    n=(n&0x33333333)+((n>>2)&0x33333333);
    n=(n+(n>>4))&0x0f0f0f0f;
    n+=n>>8; n+=n>>16;
    return ((n&0x3f)-1);
}
__local_func uint32_t bim_fls( uint32_t n )
{
    n=n|(n>>0x01);
    n=n|(n>>0x02);
    n=n|(n>>0x04);
    n=n|(n>>0x08);
    n=n|(n>>0x10);
    return __builtin_popcount(n);
}