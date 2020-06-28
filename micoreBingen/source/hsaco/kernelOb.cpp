#include"../../include/hsaco/kernelOb.h"
#include"../../include/cast.h"

void kernelOb::relocate_branches()
{
    for( uint32_t i=0; i<nbranches; ++i ){
        int16_t ibra=static_cast<int16_t>(ibranch[i]);
        uint32_t c=instr[ibra];
        int16_t ilab=static_cast<int16_t>(ilable[c&0xffffu]);
        instr[ibra]=(c&0xffff0000u)|int16_as_uint16(ilab-ibra-1);
    }
}