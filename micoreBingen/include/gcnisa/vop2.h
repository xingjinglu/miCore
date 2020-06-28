#ifndef __vop2_h__
#define __vop2_h__

#define encoding_vop2 0u

#define vop2_cmov_b32     0u
#define vop2_add_f32      1u
#define vop2_sub_f32      2u
#define vop2_mul_f32      5u
#define vop2_mul_u24      8u
#define vop2_mul_hi_u24   9u
#define vop2_min_f32     10u
#define vop2_max_f32     11u
#define vop2_shr_b32     16u
#define vop2_shl_b32     18u
#define vop2_and_b32     19u
#define vop2_or_b32      20u
#define vop2_xor_b32     21u
#define vop2_mac_f32     22u
#define vop2_mka_f32     23u
#define vop2_mak_f32     24u
#define vop2_add_co_u32  25u
#define vop2_sub_co_u32  26u
#define vop2_rsub_co_u32 27u
#define vop2_addc_co_u32 28u
#define vop2_subc_co_u32 29u
#define vop2_add_u32     52u
#define vop2_sub_u32     53u
#define vop2_rsub_u32    54u
#define vop2_dp2_f32_f16 55u
#define vop2_dp2_i32_i16 56u
#define vop2_dp4_i32_i8  57u
#define vop2_dp8_i32_i4  58u
#define vop2_fmac_f32    59u
#define vop2_fmac_f16x2  60u
#define vop2_xnor_b32    61u

#endif