#ifndef __pgmrsrc_h__
#define __pgmrsrc_h__

#include<stdint.h>

enum:uint32_t{
    amdgpu_fp_mode_rn=0,
    amdgpu_fp_mode_rd=1,
    amdgpu_fp_mode_ru=2,
    amdgpu_fp_mode_rz=3
};

enum:uint32_t{
    amdgpu_fp_denorm_fsd=0,
    amdgpu_fp_denorm_fd =1,
    amdgpu_fp_denorm_fs =2,
    amdgpu_fp_denorm_fn =3
};

enum:uint32_t{
    amdgpu_vgpr_itermid_1d=0,
    amdgpu_vgpr_itermid_2d=1,
    amdgpu_vgpr_itermid_3d=2
};

#endif