#ifndef __hsaco_h__
#define __hsaco_h__

#include<stdlib.h>
#include<memory.h>
#include"../elf.h"
#include"kernelOb.h"
#include"metadata.h"

#define gfx900 EF_AMDGPU_MACH_GFX900
#define gfx902 EF_AMDGPU_MACH_GFX902
#define gfx904 EF_AMDGPU_MACH_GFX904
#define gfx906 EF_AMDGPU_MACH_GFX906
#define gfx908 EF_AMDGPU_MACH_GFX908
#define gfx909 EF_AMDGPU_MACH_GFX909

#ifndef __gfxip__
#define __gfxip__ gfx908
#endif

#endif