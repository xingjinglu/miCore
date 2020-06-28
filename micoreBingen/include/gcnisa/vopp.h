#ifndef __vopp_h__
#define __vopp_h__

#include"mma.h"

#define encoding_vopp  0xd3800000u

#define LO(vgpr) (0x4000|vgpr)
#define HI(vgpr) (0x4800|vgpr)

#define vopp_fma_f16x2   (14u<<16)
#define vopp_add_f16x2   (15u<<16)
#define vopp_mul_f16x2   (16u<<16)
#define vopp_min_f16x2   (17u<<16)
#define vopp_max_f16x2   (18u<<16)
#define vopp_fma_f32_f16 (32u<<16)
#define vopp_fma_lo_f16  (33u<<16)
#define vopp_fma_hi_f16  (34u<<16)
#define vopp_dp2_f32_f16 (35u<<16)
#define vopp_dp2_i32_i16 (38u<<16)
#define vopp_dp2_u32_u16 (39u<<16)
#define vopp_dp4_i32_i8  (40u<<16)
#define vopp_dp4_u32_u8  (41u<<16)
#define vopp_dp8_i32_i4  (42u<<16)
#define vopp_dp8_u32_u4  (43u<<16)
#define vopp_movout_b32  (88u<<16)
#define vopp_movin_b32   (89u<<16)

#endif