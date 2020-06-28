#ifndef __sfft16x16_h__
#define __sfft16x16_h__

#include"fft.h"

#define FFT16x16_SET_RF(){                           \
    s_movk_b32(C0x,float_as_uint( 0.9238795325113f));\
    s_movk_b32(C0y,float_as_uint(-0.9238795325113f));\
    s_movk_b32(C1x,float_as_uint( 0.7071067811865f));\
    s_movk_b32(C1y,float_as_uint(-0.7071067811865f));\
    s_movk_b32(C2x,float_as_uint( 0.3826834323651f));\
    s_movk_b32(C2y,float_as_uint(-0.3826834323651f));\
}

#define FFT16x16_SET_SCOEF(){                        \
    s_movk_b32(sk0,float_as_uint( 0.3086582838174f));\
    s_movk_b32(sk1,float_as_uint( 0.1464466094067f));\
    s_movk_b32(sk2,float_as_uint( 0.0380602337443f));\
    s_movk_b32(k0x,float_as_uint( 0.4619397662556f));\
    s_movk_b32(k0y,float_as_uint(-0.4619397662556f));\
    s_movk_b32(k1x,float_as_uint( 0.6913417161825f));\
    s_movk_b32(k1y,float_as_uint(-0.6913417161825f));\
    s_movk_b32(k2x,float_as_uint( 0.3535533905932f));\
    s_movk_b32(k2y,float_as_uint(-0.3535533905932f));\
    s_movk_b32(k3x,float_as_uint( 0.8535533905932f));\
    s_movk_b32(k3y,float_as_uint(-0.8535533905932f));\
    s_movk_b32(k4x,float_as_uint( 0.1913417161825f));\
    s_movk_b32(k4y,float_as_uint(-0.1913417161825f));\
    s_movk_b32(k5x,float_as_uint( 0.9619397662556f));\
    s_movk_b32(k5y,float_as_uint(-0.9619397662556f));\
}

#define FFT16x16_R2C_CALC_LDS_PTRS(__p0,__p1,__p2,__q0,__q1,__x,__y,__u,__v,stemp){\
    v_mulk_u24(__p0,0x240,__y);    \
    v_mulk_u24(__p1,0x048,__v);    \
    s_movk_i32(stemp,145);         \
    v_add_u32(__p2,__p0,__p1);     \
    v_shl_add_u32(__p0,__x,2,__p0);\
    v_shl_add_u32(__p1,__u,2,__p2);\
    v_shl_add_u32(__p2,__u,5,__p2);\
    v_mad_u24(__q0,stemp,__y,__x); \
    v_mad_u24(__q1,stemp,__x,__y); \
    v_shl_b32(__q0,__q0,2);        \
    v_shl_b32(__q1,__q1,2);        \
}

#define FFT16x16_C2R_CALC_LDS_PTRS(__p0,__p1,__p2,__x,__y,__u,stemp){\
    s_movk_i32(stemp+0,0x240);        \
    s_movk_i32(stemp+1,0x048);        \
    v_shr_b32(__p0,__x,1);            \
    v_mul_u24(__p1,stemp+0,__y);      \
    v_mad_u24(__p2,stemp+1,__p0,__p1);\
    v_shl_add_u32(__p0,__x,2,__p1);   \
    v_shl_add_u32(__p1,__u,2,__p2);   \
    v_shl_add_u32(__p2,__u,5,__p2);   \
}

#define FFT16x16_C2R_RRENAME(c){\
    v_exch_b32(c[0].y,c[1].x);  \
    v_exch_b32(c[2].y,c[3].x);  \
    v_exch_b32(c[4].y,c[5].x);  \
    v_exch_b32(c[6].y,c[7].x);  \
    c[0].y=v2 ; c[1].x=v1 ;     \
    c[2].y=v6 ; c[3].x=v5 ;     \
    c[4].y=v10; c[5].x=v9 ;     \
    c[6].y=v14; c[7].x=v13;     \
}

#define FFT8(c){                        \
    uint2* d=&c[8];                     \
    /*=============stage0=============*/\
    v_sub_f32(d[0].x,c[0].x,c[4].x);    \
    v_sub_f32(d[0].y,c[0].y,c[4].y);    \
    v_sub_f32(d[1].x,c[1].x,c[5].x);    \
    v_sub_f32(d[1].y,c[1].y,c[5].y);    \
    v_sub_f32(d[2].x,c[2].x,c[6].x);    \
    v_sub_f32(d[2].y,c[2].y,c[6].y);    \
    v_sub_f32(d[3].x,c[3].x,c[7].x);    \
    v_sub_f32(d[3].y,c[3].y,c[7].y);    \
    v_add_f32(c[0].x,c[0].x,c[4].x);    \
    v_add_f32(c[0].y,c[0].y,c[4].y);    \
    v_add_f32(c[1].x,c[1].x,c[5].x);    \
    v_add_f32(c[1].y,c[1].y,c[5].y);    \
    v_add_f32(c[2].x,c[2].x,c[6].x);    \
    v_add_f32(c[2].y,c[2].y,c[6].y);    \
    v_add_f32(c[3].x,c[3].x,c[7].x);    \
    v_add_f32(c[3].y,c[3].y,c[7].y);    \
    /*=============stage1=============*/\
    v_add_f32(c[4].x,d[0].x,d[2].y);    \
    v_sub_f32(c[4].y,d[0].y,d[2].x);    \
    v_sub_f32(c[6].x,d[0].x,d[2].y);    \
    v_add_f32(c[6].y,d[0].y,d[2].x);    \
    v_add_f32(c[5].x,d[1].x,d[3].y);    \
    v_sub_f32(c[5].y,d[1].y,d[3].x);    \
    v_sub_f32(c[7].x,d[1].x,d[3].y);    \
    v_add_f32(c[7].y,d[1].y,d[3].x);    \
    v_sub_f32(d[0].x,c[0].x,c[2].x);    \
    v_sub_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[1].x,c[3].x);    \
    v_sub_f32(d[1].y,c[1].y,c[3].y);    \
    v_add_f32(c[0].x,c[0].x,c[2].x);    \
    v_add_f32(c[0].y,c[0].y,c[2].y);    \
    v_add_f32(c[1].x,c[1].x,c[3].x);    \
    v_add_f32(c[1].y,c[1].y,c[3].y);    \
    /*=============stage2=============*/\
    v_add_f32(c[2].x,d[0].x,d[1].y);    \
    v_sub_f32(c[2].y,d[0].y,d[1].x);    \
    v_sub_f32(c[3].x,d[0].x,d[1].y);    \
    v_add_f32(c[3].y,d[0].y,d[1].x);    \
    v_add_f32(d[2].x,c[5].y,c[5].x);    \
    v_sub_f32(d[2].y,c[5].y,c[5].x);    \
    v_sub_f32(d[3].x,c[7].x,c[7].y);    \
    v_add_f32(d[3].y,c[7].x,c[7].y);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);\
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);\
    v_fma_f32(c[5].x,C1y,d[2].x,c[4].x);\
    v_fma_f32(c[5].y,C1y,d[2].y,c[4].y);\
    v_fma_f32(c[7].x,C1x,d[3].x,c[6].x);\
    v_fma_f32(c[7].y,C1x,d[3].y,c[6].y);\
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
    V_MAC_F32(c[4].y,C1x,d[2].y);       \
    V_MAC_F32(c[6].x,C1y,d[3].x);       \
    V_MAC_F32(c[6].y,C1y,d[3].y);       \
}

#define IFFT8(c){                       \
    uint2* d=&c[8];                     \
    /*=============stage0=============*/\
    v_sub_f32(d[0].x,c[0].x,c[4].x);    \
    v_sub_f32(d[0].y,c[0].y,c[4].y);    \
    v_sub_f32(d[1].x,c[1].x,c[5].x);    \
    v_sub_f32(d[1].y,c[1].y,c[5].y);    \
    v_sub_f32(d[2].x,c[2].x,c[6].x);    \
    v_sub_f32(d[2].y,c[2].y,c[6].y);    \
    v_sub_f32(d[3].x,c[3].x,c[7].x);    \
    v_sub_f32(d[3].y,c[3].y,c[7].y);    \
    v_add_f32(c[0].x,c[0].x,c[4].x);    \
    v_add_f32(c[0].y,c[0].y,c[4].y);    \
    v_add_f32(c[1].x,c[1].x,c[5].x);    \
    v_add_f32(c[1].y,c[1].y,c[5].y);    \
    v_add_f32(c[2].x,c[2].x,c[6].x);    \
    v_add_f32(c[2].y,c[2].y,c[6].y);    \
    v_add_f32(c[3].x,c[3].x,c[7].x);    \
    v_add_f32(c[3].y,c[3].y,c[7].y);    \
    /*=============stage1=============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);    \
    v_add_f32(c[4].y,d[0].y,d[2].x);    \
    v_add_f32(c[6].x,d[0].x,d[2].y);    \
    v_sub_f32(c[6].y,d[0].y,d[2].x);    \
    v_sub_f32(c[5].x,d[1].x,d[3].y);    \
    v_add_f32(c[5].y,d[1].y,d[3].x);    \
    v_add_f32(c[7].x,d[1].x,d[3].y);    \
    v_sub_f32(c[7].y,d[1].y,d[3].x);    \
    v_sub_f32(d[0].x,c[0].x,c[2].x);    \
    v_sub_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[1].x,c[3].x);    \
    v_sub_f32(d[1].y,c[1].y,c[3].y);    \
    v_add_f32(c[0].x,c[0].x,c[2].x);    \
    v_add_f32(c[0].y,c[0].y,c[2].y);    \
    v_add_f32(c[1].x,c[1].x,c[3].x);    \
    v_add_f32(c[1].y,c[1].y,c[3].y);    \
    /*=============stage2=============*/\
    v_sub_f32(c[2].x,d[0].x,d[1].y);    \
    v_add_f32(c[2].y,d[0].y,d[1].x);    \
    v_add_f32(c[3].x,d[0].x,d[1].y);    \
    v_sub_f32(c[3].y,d[0].y,d[1].x);    \
    v_sub_f32(d[2].x,c[5].x,c[5].y);    \
    v_add_f32(d[2].y,c[5].x,c[5].y);    \
    v_add_f32(d[3].x,c[7].y,c[7].x);    \
    v_sub_f32(d[3].y,c[7].y,c[7].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);\
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);\
    v_fma_f32(c[5].x,C1y,d[2].x,c[4].x);\
    v_fma_f32(c[5].y,C1y,d[2].y,c[4].y);\
    v_fma_f32(c[7].x,C1x,d[3].x,c[6].x);\
    v_fma_f32(c[7].y,C1x,d[3].y,c[6].y);\
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
    V_MAC_F32(c[4].y,C1x,d[2].y);       \
    V_MAC_F32(c[6].x,C1y,d[3].x);       \
    V_MAC_F32(c[6].y,C1y,d[3].y);       \
}

#define IHFFT8(c){                      \
    uint2* d=&c[8];                     \
    /*=============stage0=============*/\
    s_sync(lgkmcnt(2));                 \
    v_sub_f32(d[0].x,c[0].x,c[4].x);    \
    v_sub_f32(d[0].y,c[0].y,c[4].y);    \
    v_sub_f32(d[1].x,c[1].x,c[5].x);    \
    v_sub_f32(d[1].y,c[1].y,c[5].y);    \
    v_add_f32(c[0].x,c[0].x,c[4].x);    \
    v_add_f32(c[0].y,c[0].y,c[4].y);    \
    v_add_f32(c[1].x,c[1].x,c[5].x);    \
    v_add_f32(c[1].y,c[1].y,c[5].y);    \
    s_sync(lgkmcnt(0));                 \
    v_sub_f32(d[2].x,c[2].x,c[6].x);    \
    v_sub_f32(d[2].y,c[2].y,c[6].y);    \
    v_sub_f32(d[3].x,c[3].x,c[7].x);    \
    v_sub_f32(d[3].y,c[3].y,c[7].y);    \
    v_add_f32(c[2].x,c[2].x,c[6].x);    \
    v_add_f32(c[2].y,c[2].y,c[6].y);    \
    v_add_f32(c[3].x,c[3].x,c[7].x);    \
    v_add_f32(c[3].y,c[3].y,c[7].y);    \
    /*=============stage1=============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);    \
    v_add_f32(c[4].y,d[0].y,d[2].x);    \
    v_add_f32(c[6].x,d[0].x,d[2].y);    \
    v_sub_f32(c[6].y,d[0].y,d[2].x);    \
    v_sub_f32(c[5].x,d[1].x,d[3].y);    \
    v_add_f32(c[5].y,d[1].y,d[3].x);    \
    v_add_f32(c[7].x,d[1].x,d[3].y);    \
    v_sub_f32(c[7].y,d[1].y,d[3].x);    \
    v_sub_f32(d[0].x,c[0].x,c[2].x);    \
    v_sub_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[1].x,c[3].x);    \
    v_sub_f32(d[1].y,c[1].y,c[3].y);    \
    v_add_f32(c[0].x,c[0].x,c[2].x);    \
    v_add_f32(c[0].y,c[0].y,c[2].y);    \
    v_add_f32(c[1].x,c[1].x,c[3].x);    \
    v_add_f32(c[1].y,c[1].y,c[3].y);    \
    /*=============stage2=============*/\
    v_sub_f32(c[2].x,d[0].x,d[1].y);    \
    v_add_f32(c[2].y,d[0].y,d[1].x);    \
    v_add_f32(c[3].x,d[0].x,d[1].y);    \
    v_sub_f32(c[3].y,d[0].y,d[1].x);    \
    v_sub_f32(d[2].x,c[5].x,c[5].y);    \
    v_add_f32(d[2].y,c[5].x,c[5].y);    \
    v_add_f32(d[3].x,c[7].y,c[7].x);    \
    v_sub_f32(d[3].y,c[7].y,c[7].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);\
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);\
    v_fma_f32(c[5].x,C1y,d[2].x,c[4].x);\
    v_fma_f32(c[5].y,C1y,d[2].y,c[4].y);\
    v_fma_f32(c[7].x,C1x,d[3].x,c[6].x);\
    v_fma_f32(c[7].y,C1x,d[3].y,c[6].y);\
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
    V_MAC_F32(c[4].y,C1x,d[2].y);       \
    V_MAC_F32(c[6].x,C1y,d[3].x);       \
    V_MAC_F32(c[6].y,C1y,d[3].y);       \
}

#define FFT8_C2(c){                     \
    v_add_f32(c[2].x,c[1].y,c[1].x);    \
    v_sub_f32(c[2].y,c[1].y,c[1].x);    \
    v_fma_f32(c[5].x,C1y,c[2].x,c[0].x);\
    v_fma_f32(c[5].y,C1y,c[2].y,c[0].y);\
    v_fma_f32(c[7].x,C1y,c[2].y,c[0].x);\
    v_fma_f32(c[7].y,C1x,c[2].x,c[0].y);\
    v_fma_f32(c[4].x,C1x,c[2].x,c[0].x);\
    v_fma_f32(c[4].y,C1x,c[2].y,c[0].y);\
    v_fma_f32(c[6].x,C1x,c[2].y,c[0].x);\
    v_fma_f32(c[6].y,C1y,c[2].x,c[0].y);\
    v_add_f32(c[2].x,c[0].x,c[1].y);    \
    v_sub_f32(c[2].y,c[0].y,c[1].x);    \
    v_sub_f32(c[3].x,c[0].x,c[1].y);    \
    v_add_f32(c[3].y,c[0].y,c[1].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);\
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);\
}

#define IFFT8_C2(c){                    \
    v_sub_f32(c[2].x,c[1].x,c[1].y);    \
    v_add_f32(c[2].y,c[1].x,c[1].y);    \
    v_fma_f32(c[5].x,C1y,c[2].x,c[0].x);\
    v_fma_f32(c[5].y,C1y,c[2].y,c[0].y);\
    v_fma_f32(c[7].x,C1x,c[2].y,c[0].x);\
    v_fma_f32(c[7].y,C1y,c[2].x,c[0].y);\
    v_fma_f32(c[4].x,C1x,c[2].x,c[0].x);\
    v_fma_f32(c[4].y,C1x,c[2].y,c[0].y);\
    v_fma_f32(c[6].x,C1y,c[2].y,c[0].x);\
    v_fma_f32(c[6].y,C1x,c[2].x,c[0].y);\
    v_sub_f32(c[2].x,c[0].x,c[1].y);    \
    v_add_f32(c[2].y,c[0].y,c[1].x);    \
    v_add_f32(c[3].x,c[0].x,c[1].y);    \
    v_sub_f32(c[3].y,c[0].y,c[1].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);\
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);\
}

#define FFT8_C3(c){                     \
    uint2* d=&c[8];                     \
    v_add_f32(d[0].x,c[0].x,c[2].x);    \
    v_add_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[0].x,c[2].x);    \
    v_sub_f32(d[1].y,c[0].y,c[2].y);    \
    v_add_f32(c[4].x,c[0].x,c[2].y);    \
    v_sub_f32(c[4].y,c[0].y,c[2].x);    \
    v_sub_f32(c[6].x,c[0].x,c[2].y);    \
    v_add_f32(c[6].y,c[0].y,c[2].x);    \
    v_add_f32(c[2].x,d[1].x,c[1].y);    \
    v_sub_f32(c[2].y,d[1].y,c[1].x);    \
    v_sub_f32(c[3].x,d[1].x,c[1].y);    \
    v_add_f32(c[3].y,d[1].y,c[1].x);    \
    v_add_f32(d[2].x,c[1].x,c[1].y);    \
    v_sub_f32(d[2].y,c[1].x,c[1].y);    \
    v_fma_f32(c[5].x,C1y,d[2].x,c[4].x);\
    v_fma_f32(c[5].y,C1x,d[2].y,c[4].y);\
    v_fma_f32(c[7].x,C1x,d[2].y,c[6].x);\
    v_fma_f32(c[7].y,C1x,d[2].x,c[6].y);\
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
    V_MAC_F32(c[4].y,C1y,d[2].y);       \
    V_MAC_F32(c[6].x,C1y,d[2].y);       \
    V_MAC_F32(c[6].y,C1y,d[2].x);       \
    v_add_f32(c[0].x,d[0].x,c[1].x);    \
    v_add_f32(c[0].y,d[0].y,c[1].y);    \
    v_sub_f32(c[1].x,d[0].x,c[1].x);    \
    v_sub_f32(c[1].y,d[0].y,c[1].y);    \
}

#define IFFT8_C3(c){                    \
    uint2* d=&c[8];                     \
    v_add_f32(d[0].x,c[0].x,c[2].x);    \
    v_add_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[0].x,c[2].x);    \
    v_sub_f32(d[1].y,c[0].y,c[2].y);    \
    v_sub_f32(c[4].x,c[0].x,c[2].y);    \
    v_add_f32(c[4].y,c[0].y,c[2].x);    \
    v_add_f32(c[6].x,c[0].x,c[2].y);    \
    v_sub_f32(c[6].y,c[0].y,c[2].x);    \
    v_sub_f32(c[2].x,d[1].x,c[1].y);    \
    v_add_f32(c[2].y,d[1].y,c[1].x);    \
    v_add_f32(c[3].x,d[1].x,c[1].y);    \
    v_sub_f32(c[3].y,d[1].y,c[1].x);    \
    v_sub_f32(d[2].x,c[1].y,c[1].x);    \
    v_add_f32(d[2].y,c[1].y,c[1].x);    \
    v_fma_f32(c[5].x,C1x,d[2].x,c[4].x);\
    v_fma_f32(c[5].y,C1y,d[2].y,c[4].y);\
    v_fma_f32(c[7].x,C1x,d[2].y,c[6].x);\
    v_fma_f32(c[7].y,C1x,d[2].x,c[6].y);\
    V_MAC_F32(c[4].x,C1y,d[2].x);       \
    V_MAC_F32(c[4].y,C1x,d[2].y);       \
    V_MAC_F32(c[6].x,C1y,d[2].y);       \
    V_MAC_F32(c[6].y,C1y,d[2].x);       \
    v_add_f32(c[0].x,d[0].x,c[1].x);    \
    v_add_f32(c[0].y,d[0].y,c[1].y);    \
    v_sub_f32(c[1].x,d[0].x,c[1].x);    \
    v_sub_f32(c[1].y,d[0].y,c[1].y);    \
}

#define HFFT16(c,sst,sld,u,stemp,M){            \
    FFT8##M(c);                                 \
    uint2* d=&c[8];                             \
    v_cmp_u32(zero,u,ne);                       \
    s_andexec_b64(stemp,vcc);                   \
    v_exch_b32(c[1].x,c[1].y);                  \
    v_mul_f32(c[1].y,nfone,c[1].y);             \
    v_mul_f32(d[0].x,C1x,c[2].y);               \
    v_mul_f32(d[0].y,C1x,c[3].y);               \
    v_mul_f32(d[1].x,C2x,c[4].y);               \
    v_mul_f32(d[1].y,C0x,c[5].y);               \
    v_mul_f32(d[2].x,C0x,c[6].y);               \
    v_mul_f32(d[2].y,C2x,c[7].y);               \
    v_mul_f32(c[2].y,C1x,c[2].y);               \
    v_mul_f32(c[3].y,C1y,c[3].y);               \
    v_mul_f32(c[4].y,C0x,c[4].y);               \
    v_mul_f32(c[5].y,C2y,c[5].y);               \
    v_mul_f32(c[6].y,C2x,c[6].y);               \
    v_mul_f32(c[7].y,C0y,c[7].y);               \
    V_MAC_F32(c[2].y,C1y,c[2].x);               \
    V_MAC_F32(c[3].y,C1y,c[3].x);               \
    V_MAC_F32(c[4].y,C2y,c[4].x);               \
    V_MAC_F32(c[5].y,C0y,c[5].x);               \
    V_MAC_F32(c[6].y,C0y,c[6].x);               \
    V_MAC_F32(c[7].y,C2y,c[7].x);               \
    v_fma_f32(c[2].x,C1x,c[2].x,d[0].x);        \
    v_fma_f32(c[3].x,C1y,c[3].x,d[0].y);        \
    v_fma_f32(c[4].x,C0x,c[4].x,d[1].x);        \
    v_fma_f32(c[5].x,C2y,c[5].x,d[1].y);        \
    v_fma_f32(c[6].x,C2x,c[6].x,d[2].x);        \
    v_fma_f32(c[7].x,C0y,c[7].x,d[2].y);        \
    s_mov_b64(exec,stemp);                      \
    uint32_t sign=u;                            \
    v_shl_or_b32(sign,u,31,fone);               \
    dpp_shf_xor_b32(d[0].x,c[0].x,1);           \
    dpp_shf_xor_b32(d[0].y,c[4].x,1);           \
    dpp_shf_xor_b32(d[1].x,c[2].x,1);           \
    dpp_shf_xor_b32(d[1].y,c[6].x,1);           \
    dpp_shf_xor_b32(d[2].x,c[1].x,1);           \
    dpp_shf_xor_b32(d[2].y,c[5].x,1);           \
    dpp_shf_xor_b32(d[3].x,c[3].x,1);           \
    dpp_shf_xor_b32(d[3].y,c[7].x,1);           \
    V_MAC_F32(d[0].x,sign,c[0].x);              \
    V_MAC_F32(d[0].y,sign,c[4].x);              \
    V_MAC_F32(d[1].x,sign,c[2].x);              \
    V_MAC_F32(d[1].y,sign,c[6].x);              \
    V_MAC_F32(d[2].x,sign,c[1].x);              \
    V_MAC_F32(d[2].y,sign,c[5].x);              \
    V_MAC_F32(d[3].x,sign,c[3].x);              \
    V_MAC_F32(d[3].y,sign,c[7].x);              \
    lsst_b32x2(sst,0x0,d[0].x,0x1,d[0].y);      \
    lsst_b32x2(sst,0x2,d[1].x,0x3,d[1].y);      \
    lsst_b32x2(sst,0x4,d[2].x,0x5,d[2].y);      \
    lsst_b32x2(sst,0x6,d[3].x,0x7,d[3].y);      \
    dpp_shf_xor_b32(d[0].x,c[0].y,1);           \
    dpp_shf_xor_b32(d[0].y,c[4].y,1);           \
    dpp_shf_xor_b32(d[1].x,c[2].y,1);           \
    dpp_shf_xor_b32(d[1].y,c[6].y,1);           \
    dpp_shf_xor_b32(d[2].x,c[1].y,1);           \
    dpp_shf_xor_b32(d[2].y,c[5].y,1);           \
    dpp_shf_xor_b32(d[3].x,c[3].y,1);           \
    dpp_shf_xor_b32(d[3].y,c[7].y,1);           \
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[0].x,sld,0*18,1*18);           \
    lsld_b32x2(c[2].x,sld,2*18,3*18);           \
    lsld_b32x2(c[4].x,sld,4*18,5*18);           \
    lsld_b32x2(c[6].x,sld,6*18,7*18);           \
    V_MAC_F32(d[0].x,sign,c[0].y);              \
    V_MAC_F32(d[0].y,sign,c[4].y);              \
    V_MAC_F32(d[1].x,sign,c[2].y);              \
    V_MAC_F32(d[1].y,sign,c[6].y);              \
    V_MAC_F32(d[2].x,sign,c[1].y);              \
    V_MAC_F32(d[2].y,sign,c[5].y);              \
    V_MAC_F32(d[3].x,sign,c[3].y);              \
    V_MAC_F32(d[3].y,sign,c[7].y);              \
    s_sync(lgkmcnt(0));                         \
    lsst_b32x2(sst,0x0,d[0].x,0x1,d[0].y);      \
    lsst_b32x2(sst,0x2,d[1].x,0x3,d[1].y);      \
    lsst_b32x2(sst,0x4,d[2].x,0x5,d[2].y);      \
    lsst_b32x2(sst,0x6,d[3].x,0x7,d[3].y);      \
    v_mul_f32(c[0].x,fhalf,c[0].x);             \
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[0].y,sld,0*18,1*18);           \
    lsld_b32x2(c[2].y,sld,2*18,3*18);           \
    lsld_b32x2(c[4].y,sld,4*18,5*18);           \
    lsld_b32x2(c[6].y,sld,6*18,7*18);           \
    dpp_ror_b32(d[1].x,c[0].x,1);               \
    s_sync(lgkmcnt(3));                         \
    v_mul_f32(c[0].y,fhalf,c[0].y);             \
    s_nop();                                    \
    dpp_srr_b32(d[1].x,d[1].x,1);               \
    dpp_ror_b32(d[1].y,c[0].y,1);               \
    v_sub_f32(c[8].y,d[1].x,c[0].x);            \
    v_add_f32(c[0].x,c[0].x,d[1].x);            \
    dpp_srr_b32(d[1].y,d[1].y,1);               \
    v_add_f32(c[8].x,d[1].y,c[0].y);            \
    v_sub_f32(c[0].y,c[0].y,d[1].y);            \
    s_sync(lgkmcnt(0));                         \
}
    
#define VFFT16(c,sst,sld){                   \
    FFT8(c);                                 \
    uint2* d=&c[8];                          \
    v_add_f32(d[0].x,c[0].x,c[0].y);         \
    v_add_f32(d[0].y,c[4].y,c[7].y);         \
    v_add_f32(d[1].x,c[2].y,c[3].y);         \
    v_add_f32(d[1].y,c[5].y,c[6].y);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_fma_f32(d[3].y,k1x,c[4].x,neg(d[0].y));\
    v_fma_f32(d[3].x,k3x,c[2].x,neg(d[1].x));\
    v_fma_f32(d[2].y,k5x,c[6].x,neg(d[1].y));\
    V_MAC_F32(d[3].y,sk0,c[7].x);            \
    V_MAC_F32(d[3].x,sk1,c[3].x);            \
    V_MAC_F32(d[2].y,sk2,c[5].x);            \
    V_MAC_F32(d[0].y,sk0,c[4].x);            \
    V_MAC_F32(d[1].x,sk1,c[2].x);            \
    V_MAC_F32(d[1].y,sk2,c[6].x);            \
    V_MAC_F32(d[0].y,k1x,c[7].x);            \
    V_MAC_F32(d[1].x,k3x,c[3].x);            \
    V_MAC_F32(d[1].y,k5x,c[5].x);            \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,c[1].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    v_sub_f32(d[0].x,c[0].x,c[0].y);         \
    v_sub_f32(d[0].y,c[7].x,c[4].x);         \
    v_sub_f32(d[1].x,c[3].x,c[2].x);         \
    v_sub_f32(d[1].y,c[5].x,c[6].x);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_mul_f32(d[2].x,nfone,c[1].y);          \
    v_fma_f32(d[3].y,sk0,c[7].y,d[0].y);     \
    v_fma_f32(d[3].x,sk1,c[3].y,d[1].x);     \
    v_fma_f32(d[2].y,sk2,c[5].y,d[1].y);     \
    s_sync(lgkmcnt(0));                      \
    lsld_b32x2(c[0].x,sld,0x0,0x2);          \
    lsld_b32x2(c[2].x,sld,0x4,0x6);          \
    lsld_b32x2(c[4].x,sld,0x8,0xa);          \
    lsld_b32x2(c[6].x,sld,0xc,0xe);          \
    V_MAC_F32(d[3].y,k1y,c[4].y);            \
    V_MAC_F32(d[3].x,k3y,c[2].y);            \
    V_MAC_F32(d[2].y,k5y,c[6].y);            \
    V_MAC_F32(d[0].y,sk0,c[4].y);            \
    V_MAC_F32(d[1].x,sk1,c[2].y);            \
    V_MAC_F32(d[1].y,sk2,c[6].y);            \
    V_MAC_F32(d[0].y,k1y,c[7].y);            \
    V_MAC_F32(d[1].x,k3y,c[3].y);            \
    V_MAC_F32(d[1].y,k5y,c[5].y);            \
    s_sync(lgkmcnt(0));                      \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,d[2].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    s_sync(lgkmcnt(0));                      \
    lsld_b32x2(c[0].y,sld,0x0,0x2);          \
    lsld_b32x2(c[2].y,sld,0x4,0x6);          \
    lsld_b32x2(c[4].y,sld,0x8,0xa);          \
    lsld_b32x2(c[6].y,sld,0xc,0xe);          \
    s_sync(lgkmcnt(0));                      \
}

#define VFFT16_C2(c,sst,sld){                \
    FFT8_C2(c);                              \
    uint2* d=&c[8];                          \
    v_add_f32(d[0].x,c[0].x,c[0].y);         \
    v_add_f32(d[0].y,c[4].y,c[7].y);         \
    v_add_f32(d[1].x,c[2].y,c[3].y);         \
    v_add_f32(d[1].y,c[5].y,c[6].y);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_fma_f32(d[3].y,k1x,c[4].x,neg(d[0].y));\
    v_fma_f32(d[3].x,k3x,c[2].x,neg(d[1].x));\
    v_fma_f32(d[2].y,k5x,c[6].x,neg(d[1].y));\
    V_MAC_F32(d[3].y,sk0,c[7].x);            \
    V_MAC_F32(d[3].x,sk1,c[3].x);            \
    V_MAC_F32(d[2].y,sk2,c[5].x);            \
    V_MAC_F32(d[0].y,sk0,c[4].x);            \
    V_MAC_F32(d[1].x,sk1,c[2].x);            \
    V_MAC_F32(d[1].y,sk2,c[6].x);            \
    V_MAC_F32(d[0].y,k1x,c[7].x);            \
    V_MAC_F32(d[1].x,k3x,c[3].x);            \
    V_MAC_F32(d[1].y,k5x,c[5].x);            \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,c[1].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    v_sub_f32(d[0].x,c[0].x,c[0].y);         \
    v_sub_f32(d[0].y,c[7].x,c[4].x);         \
    v_sub_f32(d[1].x,c[3].x,c[2].x);         \
    v_sub_f32(d[1].y,c[5].x,c[6].x);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_mul_f32(d[2].x,nfone,c[1].y);          \
    v_fma_f32(d[3].y,sk0,c[7].y,d[0].y);     \
    v_fma_f32(d[3].x,sk1,c[3].y,d[1].x);     \
    v_fma_f32(d[2].y,sk2,c[5].y,d[1].y);     \
    s_sync(lgkmcnt(0));                      \
    lsld_b32x2(c[0].x,sld,0,2);              \
    V_MAC_F32(d[3].y,k1y,c[4].y);            \
    V_MAC_F32(d[3].x,k3y,c[2].y);            \
    V_MAC_F32(d[2].y,k5y,c[6].y);            \
    V_MAC_F32(d[0].y,sk0,c[4].y);            \
    V_MAC_F32(d[1].x,sk1,c[2].y);            \
    V_MAC_F32(d[1].y,sk2,c[6].y);            \
    V_MAC_F32(d[0].y,k1y,c[7].y);            \
    V_MAC_F32(d[1].x,k3y,c[3].y);            \
    V_MAC_F32(d[1].y,k5y,c[5].y);            \
    s_sync(lgkmcnt(0));                      \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,d[2].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    s_sync(lgkmcnt(0));                      \
    lsld_b32x2(c[0].y,sld,0,2);              \
    s_sync(lgkmcnt(0));                      \
}

#define VFFT16_C3(c,sst,sld){                \
    FFT8_C3(c);                              \
    uint2* d=&c[8];                          \
    v_add_f32(d[0].x,c[0].x,c[0].y);         \
    v_add_f32(d[0].y,c[4].y,c[7].y);         \
    v_add_f32(d[1].x,c[2].y,c[3].y);         \
    v_add_f32(d[1].y,c[5].y,c[6].y);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_fma_f32(d[3].y,k1x,c[4].x,neg(d[0].y));\
    v_fma_f32(d[3].x,k3x,c[2].x,neg(d[1].x));\
    v_fma_f32(d[2].y,k5x,c[6].x,neg(d[1].y));\
    V_MAC_F32(d[3].y,sk0,c[7].x);            \
    V_MAC_F32(d[3].x,sk1,c[3].x);            \
    V_MAC_F32(d[2].y,sk2,c[5].x);            \
    V_MAC_F32(d[0].y,sk0,c[4].x);            \
    V_MAC_F32(d[1].x,sk1,c[2].x);            \
    V_MAC_F32(d[1].y,sk2,c[6].x);            \
    V_MAC_F32(d[0].y,k1x,c[7].x);            \
    V_MAC_F32(d[1].x,k3x,c[3].x);            \
    V_MAC_F32(d[1].y,k5x,c[5].x);            \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,c[1].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    v_sub_f32(d[0].x,c[0].x,c[0].y);         \
    v_sub_f32(d[0].y,c[7].x,c[4].x);         \
    v_sub_f32(d[1].x,c[3].x,c[2].x);         \
    v_sub_f32(d[1].y,c[5].x,c[6].x);         \
    v_mul_f32(d[0].y,k0x,d[0].y);            \
    v_mul_f32(d[1].x,k2x,d[1].x);            \
    v_mul_f32(d[1].y,k4x,d[1].y);            \
    v_mul_f32(d[2].x,nfone,c[1].y);          \
    v_fma_f32(d[3].y,sk0,c[7].y,d[0].y);     \
    v_fma_f32(d[3].x,sk1,c[3].y,d[1].x);     \
    v_fma_f32(d[2].y,sk2,c[5].y,d[1].y);     \
    s_sync(lgkmcnt(0));                      \
    lsld_b32(c[0].x,sld,0x00);               \
    lsld_b32(c[1].x,sld,0x08);               \
    lsld_b32(c[2].x,sld,0x10);               \
    V_MAC_F32(d[3].y,k1y,c[4].y);            \
    V_MAC_F32(d[3].x,k3y,c[2].y);            \
    V_MAC_F32(d[2].y,k5y,c[6].y);            \
    V_MAC_F32(d[0].y,sk0,c[4].y);            \
    V_MAC_F32(d[1].x,sk1,c[2].y);            \
    V_MAC_F32(d[1].y,sk2,c[6].y);            \
    V_MAC_F32(d[0].y,k1y,c[7].y);            \
    V_MAC_F32(d[1].x,k3y,c[3].y);            \
    V_MAC_F32(d[1].y,k5y,c[5].y);            \
    s_sync(lgkmcnt(0));                      \
    lsst_b32x2(sst,0*18,d[0].x,1*18,d[0].y); \
    lsst_b32x2(sst,2*18,d[1].x,3*18,d[1].y); \
    lsst_b32x2(sst,4*18,d[2].x,5*18,d[2].y); \
    lsst_b32x2(sst,6*18,d[3].x,7*18,d[3].y); \
    s_sync(lgkmcnt(0));                      \
    lsld_b32(c[0].y,sld,0x00);               \
    lsld_b32(c[1].y,sld,0x08);               \
    lsld_b32(c[2].y,sld,0x10);               \
    s_sync(lgkmcnt(0));                      \
}

#define HIFFT16(c,spa,spb,spc,u,stemp){     \
    uint2* d=&c[8];                         \
    v_sub_f32(c[0].x,c[0].x,c[8].y);        \
    v_add_f32(c[0].y,c[0].y,c[8].x);        \
    FFT16x16_C2R_RRENAME(c);                \
    lsst_b32x2(spa,0*18,c[0].x,1*18,c[1].x);\
    lsst_b32x2(spa,2*18,c[2].x,3*18,c[3].x);\
    lsst_b32x2(spa,4*18,c[4].x,5*18,c[5].x);\
    lsst_b32x2(spa,6*18,c[6].x,7*18,c[7].x);\
    s_sync(lgkmcnt(0));                     \
    lsld_b32x2(c[0].x,spb,0x0,0x2);         \
    lsld_b32x2(c[2].x,spb,0x4,0x6);         \
    lsld_b32x2(c[4].x,spb,0x8,0xa);         \
    lsld_b32x2(c[6].x,spb,0xc,0xe);         \
    s_sync(lgkmcnt(0));                     \
    lsst_b32x2(spa,0*18,c[0].y,1*18,c[1].y);\
    lsst_b32x2(spa,2*18,c[2].y,3*18,c[3].y);\
    lsst_b32x2(spa,4*18,c[4].y,5*18,c[5].y);\
    lsst_b32x2(spa,6*18,c[6].y,7*18,c[7].y);\
    s_sync(lgkmcnt(0));                     \
    lsld_b32x2(c[0].y,spb,0x0,0x2);         \
    lsld_b32x2(c[4].y,spb,0x8,0xa);         \
    lsld_b32x2(c[2].y,spb,0x4,0x6);         \
    lsld_b32x2(c[6].y,spb,0xc,0xe);         \
    IHFFT8(c)                               \
    v_cmp_u32(zero,u,ne);                   \
    s_andexec_b64(stemp,vcc);               \
    v_exch_b32(c[1].x,c[1].y);              \
    v_mul_f32(c[1].x,nfone,c[1].x);         \
    v_mul_f32(c[1].y,nfone,c[1].y);         \
    v_mul_f32(d[0].x,C1y,c[2].y);           \
    v_mul_f32(d[0].y,C1y,c[3].y);           \
    v_mul_f32(d[1].x,C2y,c[4].y);           \
    v_mul_f32(d[1].y,C0y,c[5].y);           \
    v_mul_f32(d[2].x,C0y,c[6].y);           \
    v_mul_f32(d[2].y,C2y,c[7].y);           \
    v_mul_f32(c[2].y,C1y,c[2].y);           \
    v_mul_f32(c[3].y,C1x,c[3].y);           \
    v_mul_f32(c[4].y,C0y,c[4].y);           \
    v_mul_f32(c[5].y,C2x,c[5].y);           \
    v_mul_f32(c[6].y,C2y,c[6].y);           \
    v_mul_f32(c[7].y,C0x,c[7].y);           \
    V_MAC_F32(c[2].y,C1y,c[2].x);           \
    V_MAC_F32(c[3].y,C1y,c[3].x);           \
    V_MAC_F32(c[4].y,C2y,c[4].x);           \
    V_MAC_F32(c[5].y,C0y,c[5].x);           \
    V_MAC_F32(c[6].y,C0y,c[6].x);           \
    V_MAC_F32(c[7].y,C2y,c[7].x);           \
    v_fma_f32(c[2].x,C1x,c[2].x,d[0].x);    \
    v_fma_f32(c[3].x,C1y,c[3].x,d[0].y);    \
    v_fma_f32(c[4].x,C0x,c[4].x,d[1].x);    \
    v_fma_f32(c[5].x,C2y,c[5].x,d[1].y);    \
    v_fma_f32(c[6].x,C2x,c[6].x,d[2].x);    \
    v_fma_f32(c[7].x,C0y,c[7].x,d[2].y);    \
    s_not_b64(exec,vcc);                    \
    v_mul_f32(c[1].y,nfone,c[1].y);         \
    v_mul_f32(c[2].y,nfone,c[2].y);         \
    v_mul_f32(c[3].y,nfone,c[3].y);         \
    v_mul_f32(c[4].y,nfone,c[4].y);         \
    v_mul_f32(c[5].y,nfone,c[5].y);         \
    v_mul_f32(c[6].y,nfone,c[6].y);         \
    v_mul_f32(c[7].y,nfone,c[7].y);         \
    s_mov_b64(exec,stemp);                  \
    uint32_t sign=u;                        \
    v_shl_or_b32(sign,u,31,fone);           \
    dpp_shf_xor_b32(d[0].x,c[0].x,1);       \
    dpp_shf_xor_b32(d[0].y,c[4].x,1);       \
    dpp_shf_xor_b32(d[1].x,c[2].x,1);       \
    dpp_shf_xor_b32(d[1].y,c[6].x,1);       \
    dpp_shf_xor_b32(d[2].x,c[1].x,1);       \
    dpp_shf_xor_b32(d[2].y,c[5].x,1);       \
    dpp_shf_xor_b32(d[3].x,c[3].x,1);       \
    dpp_shf_xor_b32(d[3].y,c[7].x,1);       \
    V_MAC_F32(d[0].x,sign,c[0].x);          \
    V_MAC_F32(d[0].y,sign,c[4].x);          \
    V_MAC_F32(d[1].x,sign,c[2].x);          \
    V_MAC_F32(d[1].y,sign,c[6].x);          \
    V_MAC_F32(d[2].x,sign,c[1].x);          \
    V_MAC_F32(d[2].y,sign,c[5].x);          \
    V_MAC_F32(d[3].x,sign,c[3].x);          \
    V_MAC_F32(d[3].y,sign,c[7].x);          \
    lsst_b32x2(spc,0,d[0].x,1,d[0].y);      \
    lsst_b32x2(spc,2,d[1].x,3,d[1].y);      \
    lsst_b32x2(spc,4,d[2].x,5,d[2].y);      \
    lsst_b32x2(spc,6,d[3].x,7,d[3].y);      \
    dpp_shf_xor_b32(d[0].x,c[0].y,1);       \
    dpp_shf_xor_b32(d[0].y,c[4].y,1);       \
    dpp_shf_xor_b32(d[1].x,c[2].y,1);       \
    dpp_shf_xor_b32(d[1].y,c[6].y,1);       \
    dpp_shf_xor_b32(d[2].x,c[1].y,1);       \
    dpp_shf_xor_b32(d[2].y,c[5].y,1);       \
    dpp_shf_xor_b32(d[3].x,c[3].y,1);       \
    dpp_shf_xor_b32(d[3].y,c[7].y,1);       \
    s_sync(lgkmcnt(0));                     \
    lsld_b32x2(c[0].x,spa,0*18,1*18);       \
    lsld_b32x2(c[2].x,spa,2*18,3*18);       \
    lsld_b32x2(c[4].x,spa,4*18,5*18);       \
    lsld_b32x2(c[6].x,spa,6*18,7*18);       \
    V_MAC_F32(d[0].x,sign,c[0].y);          \
    V_MAC_F32(d[0].y,sign,c[4].y);          \
    V_MAC_F32(d[1].x,sign,c[2].y);          \
    V_MAC_F32(d[1].y,sign,c[6].y);          \
    V_MAC_F32(d[2].x,sign,c[1].y);          \
    V_MAC_F32(d[2].y,sign,c[5].y);          \
    V_MAC_F32(d[3].x,sign,c[3].y);          \
    V_MAC_F32(d[3].y,sign,c[7].y);          \
    s_sync(lgkmcnt(0));                     \
    lsst_b32x2(spc,0,d[0].x,1,d[0].y);      \
    lsst_b32x2(spc,2,d[1].x,3,d[1].y);      \
    lsst_b32x2(spc,4,d[2].x,5,d[2].y);      \
    lsst_b32x2(spc,6,d[3].x,7,d[3].y);      \
    s_sync(lgkmcnt(0));                     \
    lsld_b32x2(c[0].y,spa,0*18,1*18);       \
    lsld_b32x2(c[6].y,spa,6*18,7*18);       \
    lsld_b32x2(c[2].y,spa,2*18,3*18);       \
    lsld_b32x2(c[4].y,spa,4*18,5*18);       \
}

#define VIFFT16(c,x,stemp){         \
    uint2* d=&c[8];                 \
    v_and_b32(v16,ic(7),x);         \
    v_cmp_u32(zero,v16,ne);         \
    v_cmov_b32(v17,nfone,fone,vcc); \
    s_sync(lgkmcnt(2));             \
    v_mul_f32(v16,v17,c[0].y);      \
    v_add_f32(c[0].y,c[0].x,v16);   \
    v_sub_f32(c[0].x,c[0].x,v16);   \
    v_add_f32(d[0].x,c[1].x,c[7].x);\
    v_sub_f32(d[0].y,c[1].y,c[7].y);\
    v_add_f32(d[1].x,c[1].y,c[7].y);\
    v_sub_f32(d[1].y,c[1].x,c[7].x);\
    v_mul_f32(c[1].x,C0y,d[1].x);   \
    v_mul_f32(c[1].y,C0x,d[1].y);   \
    V_MAC_F32(c[1].x,C2y,d[1].y);   \
    V_MAC_F32(c[1].y,C2y,d[1].x);   \
    v_sub_f32(c[7].x,d[0].x,c[1].x);\
    v_sub_f32(c[7].y,c[1].y,d[0].y);\
    v_add_f32(c[1].x,c[1].x,d[0].x);\
    v_add_f32(c[1].y,c[1].y,d[0].y);\
    s_sync(lgkmcnt(1));             \
    v_add_f32(d[0].x,c[2].x,c[6].x);\
    v_sub_f32(d[0].y,c[2].y,c[6].y);\
    v_add_f32(d[1].x,c[2].y,c[6].y);\
    v_sub_f32(d[1].y,c[2].x,c[6].x);\
    v_mul_f32(c[2].x,C1y,d[1].x);   \
    v_mul_f32(c[2].y,C1x,d[1].y);   \
    V_MAC_F32(c[2].x,C1y,d[1].y);   \
    V_MAC_F32(c[2].y,C1y,d[1].x);   \
    v_sub_f32(c[6].x,d[0].x,c[2].x);\
    v_sub_f32(c[6].y,c[2].y,d[0].y);\
    v_add_f32(c[2].x,c[2].x,d[0].x);\
    v_add_f32(c[2].y,c[2].y,d[0].y);\
    s_sync(lgkmcnt(0));             \
    v_add_f32(d[0].x,c[3].x,c[5].x);\
    v_sub_f32(d[0].y,c[3].y,c[5].y);\
    v_add_f32(d[1].x,c[3].y,c[5].y);\
    v_sub_f32(d[1].y,c[3].x,c[5].x);\
    v_mul_f32(c[3].x,C2y,d[1].x);   \
    v_mul_f32(c[3].y,C2x,d[1].y);   \
    V_MAC_F32(c[3].x,C0y,d[1].y);   \
    V_MAC_F32(c[3].y,C0y,d[1].x);   \
    v_sub_f32(c[5].x,d[0].x,c[3].x);\
    v_sub_f32(c[5].y,c[3].y,d[0].y);\
    v_add_f32(c[3].x,c[3].x,d[0].x);\
    v_add_f32(c[3].y,c[3].y,d[0].y);\
    v_mul_f32(c[4].x, f2,c[4].x);   \
    v_mul_f32(c[4].y,nf2,c[4].y);   \
    IFFT8(c);                       \
    s_andn1exec_b64(stemp,vcc);     \
    v_exch_b32(c[0].y,c[7].y);      \
    v_exch_b32(c[4].x,c[7].x);      \
    v_exch_b32(c[4].y,c[3].y);      \
    v_exch_b32(c[2].x,c[3].x);      \
    v_exch_b32(c[2].y,c[5].y);      \
    v_exch_b32(c[6].x,c[5].x);      \
    v_exch_b32(c[6].y,c[1].y);      \
    s_mov_b64(exec,stemp);          \
}

#define IFFT8_s3x3(c){                  \
    uint2* d=&c[8];                     \
    /*=============stage0=============*/\
    v_sub_f32(d[0].x,c[0].x,c[4].x);    \
    v_sub_f32(d[0].y,c[0].y,c[4].y);    \
    v_sub_f32(d[1].x,c[1].x,c[5].x);    \
    v_sub_f32(d[1].y,c[1].y,c[5].y);    \
    v_sub_f32(d[2].x,c[2].x,c[6].x);    \
    v_sub_f32(d[2].y,c[2].y,c[6].y);    \
    v_sub_f32(d[3].x,c[3].x,c[7].x);    \
    v_sub_f32(d[3].y,c[3].y,c[7].y);    \
    v_add_f32(c[0].x,c[0].x,c[4].x);    \
    v_add_f32(c[0].y,c[0].y,c[4].y);    \
    v_add_f32(c[1].x,c[1].x,c[5].x);    \
    v_add_f32(c[1].y,c[1].y,c[5].y);    \
    v_add_f32(c[2].x,c[2].x,c[6].x);    \
    v_add_f32(c[2].y,c[2].y,c[6].y);    \
    v_add_f32(c[3].x,c[3].x,c[7].x);    \
    v_add_f32(c[3].y,c[3].y,c[7].y);    \
    /*=============stage1=============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);    \
    v_add_f32(c[7].x,d[0].x,d[2].y);    \
    v_sub_f32(c[7].y,d[0].y,d[2].x);    \
    v_sub_f32(c[5].x,d[1].x,d[3].y);    \
    v_add_f32(c[5].y,d[1].y,d[3].x);    \
    v_add_f32(c[6].x,d[1].x,d[3].y);    \
    v_sub_f32(c[6].y,d[1].y,d[3].x);    \
    v_add_f32(c[0].x,c[0].x,c[2].x);    \
    v_add_f32(c[0].y,c[0].y,c[2].y);    \
    v_add_f32(c[1].x,c[1].x,c[3].x);    \
    v_add_f32(c[1].y,c[1].y,c[3].y);    \
    /*=============stage2=============*/\
    v_sub_f32(d[2].x,c[5].x,c[5].y);    \
    v_add_f32(d[3].x,c[6].y,c[6].x);    \
    v_sub_f32(d[3].y,c[6].y,c[6].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    V_MAC_F32(c[7].x,C1x,d[3].x);       \
    V_MAC_F32(c[7].y,C1x,d[3].y);       \
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
}

#define VIFFT16_s3x3(c,x,stemp){    \
    uint2* d=&c[8];                 \
    v_and_b32(v16,ic(7),x);         \
    v_cmp_u32(zero,v16,ne);         \
    v_cmov_b32(v17,nfone,fone,vcc); \
    s_sync(lgkmcnt(2));             \
    v_mul_f32(v16,v17,c[0].y);      \
    v_add_f32(c[0].y,c[0].x,v16);   \
    v_sub_f32(c[0].x,c[0].x,v16);   \
    v_add_f32(d[0].x,c[1].x,c[7].x);\
    v_sub_f32(d[0].y,c[1].y,c[7].y);\
    v_add_f32(d[1].x,c[1].y,c[7].y);\
    v_sub_f32(d[1].y,c[1].x,c[7].x);\
    v_mul_f32(c[1].x,C0y,d[1].x);   \
    v_mul_f32(c[1].y,C0x,d[1].y);   \
    V_MAC_F32(c[1].x,C2y,d[1].y);   \
    V_MAC_F32(c[1].y,C2y,d[1].x);   \
    v_sub_f32(c[7].x,d[0].x,c[1].x);\
    v_sub_f32(c[7].y,c[1].y,d[0].y);\
    v_add_f32(c[1].x,c[1].x,d[0].x);\
    v_add_f32(c[1].y,c[1].y,d[0].y);\
    s_sync(lgkmcnt(1));             \
    v_add_f32(d[0].x,c[2].x,c[6].x);\
    v_sub_f32(d[0].y,c[2].y,c[6].y);\
    v_add_f32(d[1].x,c[2].y,c[6].y);\
    v_sub_f32(d[1].y,c[2].x,c[6].x);\
    v_mul_f32(c[2].x,C1y,d[1].x);   \
    v_mul_f32(c[2].y,C1x,d[1].y);   \
    V_MAC_F32(c[2].x,C1y,d[1].y);   \
    V_MAC_F32(c[2].y,C1y,d[1].x);   \
    v_sub_f32(c[6].x,d[0].x,c[2].x);\
    v_sub_f32(c[6].y,c[2].y,d[0].y);\
    v_add_f32(c[2].x,c[2].x,d[0].x);\
    v_add_f32(c[2].y,c[2].y,d[0].y);\
    s_sync(lgkmcnt(0));             \
    v_add_f32(d[0].x,c[3].x,c[5].x);\
    v_sub_f32(d[0].y,c[3].y,c[5].y);\
    v_add_f32(d[1].x,c[3].y,c[5].y);\
    v_sub_f32(d[1].y,c[3].x,c[5].x);\
    v_mul_f32(c[3].x,C2y,d[1].x);   \
    v_mul_f32(c[3].y,C2x,d[1].y);   \
    V_MAC_F32(c[3].x,C0y,d[1].y);   \
    V_MAC_F32(c[3].y,C0y,d[1].x);   \
    v_sub_f32(c[5].x,d[0].x,c[3].x);\
    v_sub_f32(c[5].y,c[3].y,d[0].y);\
    v_add_f32(c[3].x,c[3].x,d[0].x);\
    v_add_f32(c[3].y,c[3].y,d[0].y);\
    v_mul_f32(c[4].x, f2,c[4].x);   \
    v_mul_f32(c[4].y,nf2,c[4].y);   \
    IFFT8_s3x3(c);                  \
    s_andn1exec_b64(stemp,vcc);     \
    v_exch_b32(c[0].y,c[7].y);      \
    v_exch_b32(c[4].x,c[7].x);      \
    s_mov_b64(exec,stemp);          \
}

#define IFFT8_s5x5(c){                  \
    uint2* d=&c[8];                     \
    /*=============stage0=============*/\
    v_sub_f32(d[0].x,c[0].x,c[4].x);    \
    v_sub_f32(d[0].y,c[0].y,c[4].y);    \
    v_sub_f32(d[1].x,c[1].x,c[5].x);    \
    v_sub_f32(d[1].y,c[1].y,c[5].y);    \
    v_sub_f32(d[2].x,c[2].x,c[6].x);    \
    v_sub_f32(d[2].y,c[2].y,c[6].y);    \
    v_sub_f32(d[3].x,c[3].x,c[7].x);    \
    v_sub_f32(d[3].y,c[3].y,c[7].y);    \
    v_add_f32(c[0].x,c[0].x,c[4].x);    \
    v_add_f32(c[0].y,c[0].y,c[4].y);    \
    v_add_f32(c[1].x,c[1].x,c[5].x);    \
    v_add_f32(c[1].y,c[1].y,c[5].y);    \
    v_add_f32(c[2].x,c[2].x,c[6].x);    \
    v_add_f32(c[2].y,c[2].y,c[6].y);    \
    v_add_f32(c[3].x,c[3].x,c[7].x);    \
    v_add_f32(c[3].y,c[3].y,c[7].y);    \
    /*=============stage1=============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);    \
    v_add_f32(c[4].y,d[0].y,d[2].x);    \
    v_add_f32(c[7].x,d[0].x,d[2].y);    \
    v_sub_f32(c[7].y,d[0].y,d[2].x);    \
    v_sub_f32(c[5].x,d[1].x,d[3].y);    \
    v_add_f32(c[5].y,d[1].y,d[3].x);    \
    v_add_f32(c[6].x,d[1].x,d[3].y);    \
    v_sub_f32(c[6].y,d[1].y,d[3].x);    \
    v_sub_f32(d[0].x,c[0].x,c[2].x);    \
    v_sub_f32(d[0].y,c[0].y,c[2].y);    \
    v_sub_f32(d[1].x,c[1].x,c[3].x);    \
    v_sub_f32(d[1].y,c[1].y,c[3].y);    \
    v_add_f32(c[0].x,c[0].x,c[2].x);    \
    v_add_f32(c[0].y,c[0].y,c[2].y);    \
    v_add_f32(c[1].x,c[1].x,c[3].x);    \
    v_add_f32(c[1].y,c[1].y,c[3].y);    \
    /*=============stage2=============*/\
    v_sub_f32(c[2].x,d[0].x,d[1].y);    \
    v_add_f32(c[3].x,d[0].x,d[1].y);    \
    v_sub_f32(c[3].y,d[0].y,d[1].x);    \
    v_sub_f32(d[2].x,c[5].x,c[5].y);    \
    v_add_f32(d[2].y,c[5].x,c[5].y);    \
    v_add_f32(d[3].x,c[6].y,c[6].x);    \
    v_sub_f32(d[3].y,c[6].y,c[6].x);    \
    v_add_f32(c[0].x,c[0].x,c[1].x);    \
    v_add_f32(c[0].y,c[0].y,c[1].y);    \
    V_MAC_F32(c[7].x,C1x,d[3].x);       \
    V_MAC_F32(c[7].y,C1x,d[3].y);       \
    V_MAC_F32(c[4].x,C1x,d[2].x);       \
    V_MAC_F32(c[4].y,C1x,d[2].y);       \
}

#define VIFFT16_s5x5(c,x,stemp){    \
    uint2* d=&c[8];                 \
    v_and_b32(v16,ic(7),x);         \
    v_cmp_u32(zero,v16,ne);         \
    v_cmov_b32(v17,nfone,fone,vcc); \
    s_sync(lgkmcnt(2));             \
    v_mul_f32(v16,v17,c[0].y);      \
    v_add_f32(c[0].y,c[0].x,v16);   \
    v_sub_f32(c[0].x,c[0].x,v16);   \
    v_add_f32(d[0].x,c[1].x,c[7].x);\
    v_sub_f32(d[0].y,c[1].y,c[7].y);\
    v_add_f32(d[1].x,c[1].y,c[7].y);\
    v_sub_f32(d[1].y,c[1].x,c[7].x);\
    v_mul_f32(c[1].x,C0y,d[1].x);   \
    v_mul_f32(c[1].y,C0x,d[1].y);   \
    V_MAC_F32(c[1].x,C2y,d[1].y);   \
    V_MAC_F32(c[1].y,C2y,d[1].x);   \
    v_sub_f32(c[7].x,d[0].x,c[1].x);\
    v_sub_f32(c[7].y,c[1].y,d[0].y);\
    v_add_f32(c[1].x,c[1].x,d[0].x);\
    v_add_f32(c[1].y,c[1].y,d[0].y);\
    s_sync(lgkmcnt(1));             \
    v_add_f32(d[0].x,c[2].x,c[6].x);\
    v_sub_f32(d[0].y,c[2].y,c[6].y);\
    v_add_f32(d[1].x,c[2].y,c[6].y);\
    v_sub_f32(d[1].y,c[2].x,c[6].x);\
    v_mul_f32(c[2].x,C1y,d[1].x);   \
    v_mul_f32(c[2].y,C1x,d[1].y);   \
    V_MAC_F32(c[2].x,C1y,d[1].y);   \
    V_MAC_F32(c[2].y,C1y,d[1].x);   \
    v_sub_f32(c[6].x,d[0].x,c[2].x);\
    v_sub_f32(c[6].y,c[2].y,d[0].y);\
    v_add_f32(c[2].x,c[2].x,d[0].x);\
    v_add_f32(c[2].y,c[2].y,d[0].y);\
    s_sync(lgkmcnt(0));             \
    v_add_f32(d[0].x,c[3].x,c[5].x);\
    v_sub_f32(d[0].y,c[3].y,c[5].y);\
    v_add_f32(d[1].x,c[3].y,c[5].y);\
    v_sub_f32(d[1].y,c[3].x,c[5].x);\
    v_mul_f32(c[3].x,C2y,d[1].x);   \
    v_mul_f32(c[3].y,C2x,d[1].y);   \
    V_MAC_F32(c[3].x,C0y,d[1].y);   \
    V_MAC_F32(c[3].y,C0y,d[1].x);   \
    v_sub_f32(c[5].x,d[0].x,c[3].x);\
    v_sub_f32(c[5].y,c[3].y,d[0].y);\
    v_add_f32(c[3].x,c[3].x,d[0].x);\
    v_add_f32(c[3].y,c[3].y,d[0].y);\
    v_mul_f32(c[4].x, f2,c[4].x);   \
    v_mul_f32(c[4].y,nf2,c[4].y);   \
    IFFT8_s5x5(c);                  \
    s_andn1exec_b64(stemp,vcc);     \
    v_exch_b32(c[0].y,c[7].y);      \
    v_exch_b32(c[4].x,c[7].x);      \
    v_exch_b32(c[4].y,c[3].y);      \
    v_exch_b32(c[2].x,c[3].x);      \
    s_mov_b64(exec,stemp);          \
}

#define FFT16x16_R2C_LDR(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny){\
    VZERO16(__c[0].x);                            \
    s_mov_b64(s8,exec);                           \
    v_cmp_u32(s10,__nx,__x,gt);                   \
    v_cmp_u32(__ncells,__icell,gt);               \
    s_and_b64(exec,vcc,s10);                      \
    ldg_b32(__c[0].x,__base,__vo,0);              \
    if(__ny>1){ s_shl_b32(__nx,__nx,2); }         \
    for( uint32_t i=1; i<16u; ++i ){              \
        if(__ny>i){                               \
            S_ADD_U64_U32(__base,__base,__nx);    \
            ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        }                                         \
    }                                             \
    s_mov_b64(exec,s8);                           \
}

#define FFT16x16_R2C_LDR_FLIP(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny){\
    VZERO16(__c[0].x);                            \
    s_mov_b64(s8,exec);                           \
    v_cmp_u32(s10,__nx,__x,gt);                   \
    v_cmp_u32(__ncells,__icell,gt);               \
    s_and_b64(exec,vcc,s10);                      \
    ldg_b32(__c[0].x,__base,__vo,0);              \
    if(__ny>1){ s_shl_b32(__nx,__nx,2); }         \
    for( int i=1; i<16; ++i ){                    \
        if(__ny>i){                               \
            S_SUB_U64_U32(__base,__base,__nx);    \
            ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        }                                         \
    }                                             \
    s_mov_b64(exec,s8);                           \
}

#define FFT16x16_R2C_LDR_PAD(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny,__pad_y){\
    VZERO16(__c[0].x);                          \
    s_mov_b64(s8,exec);                         \
    v_cmp_i32(s12,__x,zero,ge);                 \
    v_cmp_i32(s14,__x,__nx,lt);                 \
    v_cmp_u32(__ncells,__icell,gt);             \
    s_and_b64(s12,s12,s14);                     \
    s_and_b64(exec,vcc,s12);                    \
    ldg_b32(CPTR(__c)[__pad_y],__base,__vo,0x0);\
    if(__pad_y<15){ s_shl_b32(__nx,__nx,2); }   \
    for( int i=__pad_y+1; i<16; ++i ){          \
        s_cmpk_u32(__ny,i-__pad_y,gt);          \
        s_cbra_scc0(0);                         \
        S_ADD_U64_U32(__base,__base,__nx);      \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);  \
    }                                           \
__lable__(0);                                   \
    s_mov_b64(exec,s8);                         \
}

#define FFT16x16_R2C_LDR_SPLIT(__c,__base,__vo,__x,__icell,__ncells,__nx){\
    VZERO16(__c[0].x);                      \
    s_mov_b64(s8,exec);                     \
    v_cmp_u32(s10,__nx,__x,gt);             \
    v_cmp_u32(__ncells,__icell,gt);         \
    s_and_b64(exec,vcc,s10);                \
    ldg_b32(__c[0].x,__base,__vo,0);        \
    s_shl_b32(__nx,__nx,2);                 \
    for( int i=1; i<16; ++i ){              \
        S_ADD_U64_U32(__base,__base,__nx);  \
        ldg_b32(CPTR(__c)[i],__base,__vo,0);\
    }                                       \
    s_mov_b64(exec,s8);                     \
}

#define FFT16x16_R2C_LDR_SPLIT_EX(__c,__base,__vo,__x,__y,__icell,__ncells,__nx){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__nx,__x,gt);               \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<16; ++i ){                \
        v_cmpx_u32(ic(i),__y,lt);             \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_LDR_SPLIT_PAD(__c,__base,__vo,__x,__y,__icell,__ncells,__nx,__ny){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_i32(s10,__x,zero,ge);               \
    v_cmp_i32(s12,__nx,__x,gt);               \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(s10,s10,s12);                   \
    s_and_b64(s10,s10,vcc);                   \
    s_shl_b32(__nx,__nx,2);                   \
    s_mov_b64(exec,s10);                      \
    for( int i=0; i<16; ++i ){                \
        v_cmp_i32(s12,__y,zero,ge);           \
        v_cmp_i32(__ny,__y,gt);               \
        s_and_b64(exec,vcc,s12);              \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        if(i<15){                             \
            v_add_u32(__vo,__nx,__vo);        \
            s_mov_b64(exec,s10);              \
            v_add_i32(__y,ic(1),__y);         \
        }                                     \
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_LDR_SPLIT_NOV(__c,__base,__vo,__x,__vax,__vay,__icell,__ncells,__nx){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__vax,__x,gt);              \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<16; ++i ){                \
        S_ADD_U64_U32(__base,__base,__nx);    \
        v_cmpx_u32(ic(i),__vay,lt);           \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_XLDR_EX(__c,__base,__vo,__x,__y,__chn,__nc,__nx){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__nx,__x,gt);               \
    v_cmp_u32(__nc,__chn,gt);                 \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<16; ++i ){                \
        s_cmpk_u32(__y,i,gt);                 \
        s_cbra_scc0(0);                       \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
__lable__(0);                                 \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_XLDR_PAD(__c,__base,__vo,__x,__y,__chn,__nc,__nx,__ny){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_i32(s10,__x,zero,ge);               \
    v_cmp_i32(s12,__nx,__x,gt);               \
    v_cmp_u32(__nc,__chn,gt);                 \
    s_and_b64(s10,s10,s12);                   \
    s_and_b64(exec,vcc,s10);                  \
    s_shl_b32(__nx,__nx,2);                   \
    s_cmpk_i32(__y,0,ge);                     \
    s_cbra_scc0(0);                           \
    s_cmp_i32(__y,__ny,lt);                   \
    s_cbra_scc0(15);                          \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    S_ADD_U64_U32(__base,__base,__nx);        \
    for( int i=1; i<16; ++i ){                \
    __lable__(i-1);                           \
        s_addk_i32(__y,1);                    \
        s_cmpk_i32(__y,0,ge);                 \
        s_cbra_scc0(i-1);                     \
        s_cmp_i32(__y,__ny,lt);               \
        s_cbra_scc0(15);                      \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        if(i<15){                             \
            S_ADD_U64_U32(__base,__base,__nx);\
        }                                     \
    }                                         \
__lable__(15);                                \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_XLDR_NOV(__c,__base,__vo,__x,__vax,__vay,__chn,__nc,__nx){\
    VZERO16(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__vax,__x,gt);              \
    v_cmp_u32(__nc,__chn,gt);                 \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<16; ++i ){                \
        s_cmpk_u32(__vay,i,gt);               \
        s_cbra_scc0(0);                       \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
__lable__(0);                                 \
    s_mov_b64(exec,s8);                       \
}

#define FFT16x16_R2C_PERMST(__base,__vo,__o,__c,__sst,__sld,__mask){\
    s_sync(lgkmcnt(0)); s_barrier();      \
    STS_B32x9(__sst,16,__c,.x);           \
    S_ADD_U64(__base+0x02,__base+0x0,__o);\
    S_ADD_U64(__base+0x04,__base+0x2,__o);\
    s_sync(lgkmcnt(0)); s_barrier();      \
    LDS_B32x9(__c,__sld,16,.x);           \
    S_ADD_U64(__base+0x06,__base+0x4,__o);\
    S_ADD_U64(__base+0x08,__base+0x6,__o);\
    s_sync(lgkmcnt(0)); s_barrier();      \
    STS_B32x9(__sst,16,__c,.y);           \
    S_ADD_U64(__base+0x0a,__base+0x8,__o);\
    S_ADD_U64(__base+0x0c,__base+0xa,__o);\
    s_sync(lgkmcnt(0)); s_barrier();      \
    LDS_B32x9(__c,__sld,16,.y);           \
    S_ADD_U64(__base+0x0e,__base+0xc,__o);\
    S_ADD_U64(__base+0x10,__base+0xe,__o);\
    s_mov_b64(exec,__mask);               \
    s_sync(lgkmcnt(0));                   \
    v_exch_b32(__c[0].y,__c[1].x);        \
    v_exch_b32(__c[2].y,__c[3].x);        \
    v_exch_b32(__c[4].y,__c[5].x);        \
    v_exch_b32(__c[6].y,__c[7].x);        \
    stg_b64(__base+0x00,__vo,0,v0 );      \
    stg_b64(__base+0x02,__vo,0,v8 );      \
    stg_b64(__base+0x04,__vo,0,v2 );      \
    stg_b64(__base+0x06,__vo,0,v10);      \
    stg_b64(__base+0x08,__vo,0,v4 );      \
    stg_b64(__base+0x0a,__vo,0,v12);      \
    stg_b64(__base+0x0c,__vo,0,v6 );      \
    stg_b64(__base+0x0e,__vo,0,v14);      \
    stg_b64(__base+0x10,__vo,0,v16);      \
    s_endp();                             \
}

#define FFT16x16_C2R_LDPERM(__c,__base,__vo,__p0,__p1,__p2,__x,__y,__u,__bks,__mask,stemp){\
    uint32_t __sst=__vo+1;                                       \
    uint32_t __sld=__vo+2;                                       \
    s_andexec_b64(stemp,__mask);                                 \
    ldg_b64(__c[0].x,__base,__vo,0x0);                           \
    s_shl_b32(__bks,__bks,7);                                    \
    for( int i=1; i<9; ++i ){                                    \
        S_ADD_U64_U32(__base,__base,__bks);                      \
        ldg_b64(__c[i].x,__base,__vo,0x0);                       \
    }                                                            \
    s_movk_i32(stemp+2,145);                                     \
    s_mov_b64(exec,stemp);                                       \
    v_mad_u24(__sst,stemp+2,__x,__y);                            \
    v_mad_u24(__sld,stemp+2,__y,__x);                            \
    v_shl_b32(__sst,__sst,2);                                    \
    v_shl_b32(__sld,__sld,2);                                    \
    FFT16x16_C2R_CALC_LDS_PTRS(__p0,__p1,__p2,__x,__y,__u,stemp);\
    FFT16x16_SET_RF();                                           \
    s_sync(vmcnt(0));                                            \
    STS_B32x9(__sst,16,__c,.x);                                  \
    s_sync(lgkmcnt(0)); s_barrier();                             \
    LDS_B32x9(__c,__sld,16,.x);                                  \
    s_sync(lgkmcnt(0)); s_barrier();                             \
    STS_B32x9(__sst,16,__c,.y);                                  \
    s_sync(lgkmcnt(0)); s_barrier();                             \
    LDS_B32x9(__c,__sld,16,.y);                                  \
    s_sync(lgkmcnt(0)); s_barrier();                             \
}

#define FFT16x16_C2R_ST(__base,__vo,__c,__flipx,__icell,__ncells,__nx,__ny){\
    v_cmp_u32(s2,__icell,__ncells,lt);                  \
    v_cmp_u32(__nx,__flipx,gt);                         \
    s_and_b64(exec,vcc,s2);                             \
    stg_b32(__base,__vo,0x0,__c[0].x);                  \
    if(__ny>1){                                         \
        s_shl_b32(__nx,__nx,2);                         \
        S_ADD_U64_U32(__base,__base,__nx);              \
        stg_b32(__base,__vo,0x0,__c[0].y);              \
    }                                                   \
    for( int i=1; i<8; ++i ){                           \
        if(__ny>(i*2+0)){                               \
            S_ADD_U64_U32(__base,__base,__nx);          \
            stg_b32(__base,__vo,0x0,__c[ga_brev3[i]].x);\
        }                                               \
        if(__ny>(i*2+1)){                               \
            S_ADD_U64_U32(__base,__base,__nx);          \
            stg_b32(__base,__vo,0x0,__c[ga_brev3[i]].y);\
        }                                               \
    }                                                   \
    s_endp();                                           \
}

#define FFT16x16_C2R_ST_SPLICE(__base,__vo,__c,__flipx,__icell,__ncells,__vax,__vay,__nx){\
    v_cmp_u32(s2,__icell,__ncells,lt);              \
    v_cmp_u32(__flipx,__vax,lt);                    \
	s_shl_b32(__nx,__nx,2);                         \
    s_and_b64(exec,vcc,s2);                         \
    stg_b32(__base,__vo,0x0,__c[ga_brev3[0]].x);    \
    S_ADD_U64_U32(__base,__base,__nx);              \
    v_cmpx_u32(ic(1),__vay,lt);                     \
    stg_b32(__base,__vo,0x0,__c[ga_brev3[0]].y);    \
    for( int i=1; i<8; ++i ){                       \
        S_ADD_U64_U32(__base,__base,__nx);          \
        v_cmpx_u32(ic(i*2+0),__vay,lt);             \
        stg_b32(__base,__vo,0x0,__c[ga_brev3[i]].x);\
        S_ADD_U64_U32(__base,__base,__nx);          \
        v_cmpx_u32(ic(i*2+1),__vay,lt);             \
        stg_b32(__base,__vo,0x0,__c[ga_brev3[i]].y);\
    }                                               \
    s_endp();                                       \
}

#endif
