#include"../include/idiv.h"

__local_func magic_t idiv_magic( uint32_t nmax, uint32_t d )
{
    magic_t magic;
    if(d==1){ magic.m=1; magic.s=0; return magic; }
    uint64_t nc=((nmax+1)/d)*d-1;
    uint32_t nbits=bim_fls(nmax);
    uint32_t r=(nbits<<1)+1;
    magic.m=-1; magic.s=-1;
    for( uint32_t s=0; s<r; s++ ){
        uint64_t exp=((uint64_t)1u)<<s;
        uint64_t mod=d-1-(exp-1)%d;
        if(exp>(nc*mod)){
            magic.m=(uint32_t)((exp+mod)/d);
            magic.s=s;
            break;
        }
    }
    return magic;
}