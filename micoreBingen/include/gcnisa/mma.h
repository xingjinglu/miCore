#ifndef __mma_h__
#define __mma_h__

#define encoding_mma 0xd3c00000u

#define ACC(vgpr)    (0x8000000|vgpr)
#define ABID(vgpr,n) ((n)<<11)|vgpr)
#define ABRO(vgpr,n) ((n)<<9)|vgpr)
#define BL(vgpr,n)   (((n)<<29)|vgpr)

#define opc_mma02b16p_32x32x01_f32_f32 ( 64u<<16)
#define opc_mma01b16p_32x32x02_f32_f32 ( 68u<<16)
#define opc_mma02b16p_32x32x04_f32_f16 ( 72u<<16)
#define opc_mma01b16p_32x32x08_f32_f16 ( 76u<<16)
#define opc_mma02b16p_32x32x02_f32_b16 (104u<<16)
#define opc_mma01b16p_32x32x04_f32_b16 (108u<<16)
#define opc_mma04b08p_16x16x01_f32_f32 ( 65u<<16)
#define opc_mma01b08p_16x16x04_f32_f32 ( 69u<<16)
#define opc_mma04b08p_16x16x04_f32_f16 ( 73u<<16)
#define opc_mma01b08p_16x16x16_f32_f16 ( 77u<<16)
#define opc_mma04b08p_16x16x02_f32_b16 (105u<<16)
#define opc_mma01b08p_16x16x08_f32_b16 (109u<<16)
#define opc_mma16b02p_04x04x01_f32_f32 ( 66u<<16)
#define opc_mma16b02p_04x04x02_f32_b16 (107u<<16)
#define opc_mma16b02p_04x04x04_f32_f16 ( 74u<<16)
#define opc_movout_b32                 ( 88u<<16)
#define opc_movin_b32                  ( 89u<<16)
#define opc_movin_fed_b32              ( 92u<<16)

#endif

