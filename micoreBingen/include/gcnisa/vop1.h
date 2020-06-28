#ifndef __vop1_h__
#define __vop1_h__

#define encoding_vop1 0x7e000000u

#define vop1_mov_b32         1u
#define vop1_readlane0_b32   2u
#define vop1_cvt_f16_f32    11u
#define vop1_cvt_f32_i32     5u
#define vop1_cvt_f32_u32     6u
#define vop1_cvt_u32_f32     7u
#define vop1_cvt_i32_f32     8u
#define vop1_fedmov_b32      9u
#define vop1_fract_f32      27u
#define vop1_trunc_f32      28u
#define vop1_ceil_f32       29u
#define vop1_floor_f32      31u
#define vop1_rcp_f32        34u
#define vop1_rsq_f32        36u
#define vop1_sqrt_f32       39u
#define vop1_exch_b32       81u

#endif