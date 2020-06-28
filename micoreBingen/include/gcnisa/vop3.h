#ifndef __vop3_h__
#define __vop3_h__

#define encoding_vop3 0xd0000000u

#define vop3_mad_i24         (450u<<16)
#define vop3_mad_u24         (451u<<16)
#define vop3_fma_f32         (459u<<16)
#define vop3_fma_f64         (460u<<16)
#define vop3_mad_u64_u32     (488u<<16)
#define vop3_perm_b32        (493u<<16)
#define vop3_mad_u32_u16     (497u<<16)
#define vop3_shl_add_u32     (509u<<16)
#define vop3_add_shl_u32     (510u<<16)
#define vop3_add3_u32        (511u<<16)
#define vop3_shl_or_b32      (512u<<16)
#define vop3_and_or_b32      (513u<<16)
#define vop3_or3_b32         (514u<<16)
#define vop3_add_f64         (640u<<16)
#define vop3_mul_f64         (641u<<16)
#define vop3_min_f64         (642u<<16)
#define vop3_max_f64         (643u<<16)
#define vop_mul_lo_u32       (645u<<16)
#define vop_mul_hi_u32       (646u<<16)
#define vop3_laneget_b32     (649u<<16)
#define vop3_laneset_b32     (650u<<16)
#define vop3_mbcnt_lo_u32    (652u<<16)
#define vop3_mbcnt_hi_u32    (653u<<16)
#define vop3_shl_b64         (655u<<16)
#define vop3_shr_b64         (656u<<16)
#define vop3_cvt_f16x2_f32x2 (662u<<16)
#define vop3_add_i32         (668u<<16)
#define vop3_sub_i32         (669u<<16)
#define vop3_pack_b32_f16x2  (672u<<16)

#endif