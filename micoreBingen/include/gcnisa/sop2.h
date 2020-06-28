#ifndef __sop2_h__
#define __sop2_h__

#define encoding_sop2 0x80000000u

#define sop2_add_u32      ( 0u<<23)
#define sop2_sub_u32      ( 1u<<23)
#define sop2_add_i32      ( 2u<<23)
#define sop2_sub_i32      ( 3u<<23)
#define sop2_addc_u32     ( 4u<<23)
#define sop2_subc_u32     ( 5u<<23)
#define sop2_csel_b32     (10u<<23)
#define sop2_csel_b64     (11u<<23)
#define sop2_and_b32      (12u<<23)
#define sop2_and_b64      (13u<<23)
#define sop2_or_b32       (14u<<23)
#define sop2_or_b64       (15u<<23)
#define sop2_xor_b32      (16u<<23)
#define sop2_xor_b64      (17u<<23)
#define sop2_andn2_b32    (18u<<23)
#define sop2_andn2_b64    (19u<<23)
#define sop2_nand_b32     (22u<<23)
#define sop2_nand_b64     (23u<<23)
#define sop2_shl_b32      (28u<<23)
#define sop2_shl_b64      (29u<<23)
#define sop2_shr_b32      (30u<<23)
#define sop2_shr_b64      (31u<<23)
#define sop2_mul_i32      (36u<<23)
#define sop2_mul_hi_u32   (44u<<23)
#define sop2_mul_hi_i32   (45u<<23)
#define sop2_shl1_add_u32 (46u<<23)
#define sop2_shl2_add_u32 (47u<<23)
#define sop2_shl3_add_u32 (48u<<23)
#define sop2_shl4_add_u32 (49u<<23)

#endif