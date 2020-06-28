#ifndef __lds_h__
#define __lds_h__

#define encoding_ds 0xd8000000u

#define dsop_st_b32     ( 13u<<17)
#define dsop_st_b32x2   ( 14u<<17)
#define dsop_stx_b32x2  ( 15u<<17)
#define dsop_st_b64     ( 77u<<17)
#define dsop_st_b64x2   ( 78u<<17)
#define dsop_stx_b64x2  ( 79u<<17)
#define dsop_lanest_b32 ( 29u<<17)
#define dsop_laneld_b32 (182u<<17)
#define dsop_ld_b32     ( 54u<<17)
#define dsop_ld_b32x2   ( 55u<<17)
#define dsop_ldx_b32x2  ( 56u<<17)
#define dsop_ld_b64     (118u<<17)
#define dsop_ld_b64x2   (119u<<17)
#define dsop_ldx_b64x2  (120u<<17)
#define dsop_st_b96     (222u<<17)
#define dsop_st_b128    (223u<<17)
#define dsop_ld_b96     (254u<<17)
#define dsop_ld_b128    (255u<<17)
#define dsop_nop        ( 20u<<17)
#define dsop_perm_b32   ( 62u<<17)
#define dsop_bperm_b32  ( 63u<<17)
#define dsop_consume    (189u<<17)
#define dsop_append     (190u<<17)
#define dsop_ordcnt     (191u<<17)

#endif