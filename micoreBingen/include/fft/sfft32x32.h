#ifndef __sfft32x32_h__
#define __sfft32x32_h__

#include"fft.h"

#define FFT32x32_SET_RF(){                           \
    s_movk_b32(C0x,float_as_uint( 0.7071067811865f));\
    s_movk_b32(C0y,float_as_uint(-0.7071067811865f));\
    s_movk_b32(C1x,float_as_uint( 0.3826834323651f));\
    s_movk_b32(C1y,float_as_uint(-0.3826834323651f));\
    s_movk_b32(C2x,float_as_uint( 0.9238795325113f));\
    s_movk_b32(C2y,float_as_uint(-0.9238795325113f));\
    s_movk_b32(C3x,float_as_uint( 2.4142135623731f));\
    s_movk_b32(C3y,float_as_uint(-2.4142135623731f));\
    s_movk_b32(C4x,float_as_uint( 0.4142135623731f));\
    s_movk_b32(C4y,float_as_uint(-0.4142135623731f));\
    s_movk_b32(C5x,float_as_uint( 0.9807852804032f));\
    s_movk_b32(C5y,float_as_uint(-0.9807852804032f));\
    s_movk_b32(C6x,float_as_uint( 0.1950903220161f));\
    s_movk_b32(C6y,float_as_uint(-0.1950903220161f));\
    s_movk_b32(C7x,float_as_uint( 0.8314696123025f));\
    s_movk_b32(C7y,float_as_uint(-0.8314696123025f));\
    s_movk_b32(C8x,float_as_uint( 0.5555702330196f));\
    s_movk_b32(C8y,float_as_uint(-0.5555702330196f));\
}

#define FFT32x32_SET_SCOEF(){                        \
    s_movk_b32(sk0,float_as_uint( 0.4024548389919f));\
    s_movk_b32(sk1,float_as_uint( 0.3086582838174f));\
    s_movk_b32(sk2,float_as_uint( 0.2222148834902f));\
    s_movk_b32(sk3,float_as_uint( 0.1464466094067f));\
    s_movk_b32(sk4,float_as_uint( 0.0842651938487f));\
    s_movk_b32(sk5,float_as_uint( 0.0380602337443f));\
    s_movk_b32(sk6,float_as_uint( 0.0096073597984f));\
    s_movk_b32(k0x,float_as_uint( 0.4903926402016f));\
    s_movk_b32(k0y,float_as_uint(-0.4903926402016f));\
    s_movk_b32(k1x,float_as_uint( 0.5975451610080f));\
    s_movk_b32(k1y,float_as_uint(-0.5975451610080f));\
    s_movk_b32(k2x,float_as_uint( 0.4619397662556f));\
    s_movk_b32(k2y,float_as_uint(-0.4619397662556f));\
    s_movk_b32(k3x,float_as_uint( 0.6913417161825f));\
    s_movk_b32(k3y,float_as_uint(-0.6913417161825f));\
    s_movk_b32(k4x,float_as_uint( 0.4157348061512f));\
    s_movk_b32(k4y,float_as_uint(-0.4157348061512f));\
    s_movk_b32(k5x,float_as_uint( 0.7777851165098f));\
    s_movk_b32(k5y,float_as_uint(-0.7777851165098f));\
    s_movk_b32(k6x,float_as_uint( 0.3535533905932f));\
    s_movk_b32(k6y,float_as_uint(-0.3535533905932f));\
    s_movk_b32(k7x,float_as_uint( 0.8535533905932f));\
    s_movk_b32(k7y,float_as_uint(-0.8535533905932f));\
    s_movk_b32(k8x,float_as_uint( 0.2777851165098f));\
    s_movk_b32(k8y,float_as_uint(-0.2777851165098f));\
    s_movk_b32(k9x,float_as_uint( 0.9157348061512f));\
    s_movk_b32(k9y,float_as_uint(-0.9157348061512f));\
    s_movk_b32(kax,float_as_uint( 0.1913417161825f));\
    s_movk_b32(kay,float_as_uint(-0.1913417161825f));\
    s_movk_b32(kbx,float_as_uint( 0.9619397662556f));\
    s_movk_b32(kby,float_as_uint(-0.9619397662556f));\
    s_movk_b32(kcx,float_as_uint( 0.0975451610080f));\
    s_movk_b32(kcy,float_as_uint(-0.0975451610080f));\
    s_movk_b32(kdx,float_as_uint( 0.9903926402016f));\
    s_movk_b32(kdy,float_as_uint(-0.9903926402016f));\
}

#define FFT32x32_C2R_RRENAME(c){\
    v_exch_b32(c[ 0].y,c[ 1].x);\
    v_exch_b32(c[ 2].y,c[ 3].x);\
    v_exch_b32(c[ 4].y,c[ 5].x);\
    v_exch_b32(c[ 6].y,c[ 7].x);\
    v_exch_b32(c[ 8].y,c[ 9].x);\
    v_exch_b32(c[10].y,c[11].x);\
    v_exch_b32(c[12].y,c[13].x);\
    v_exch_b32(c[14].y,c[15].x);\
    c[ 0].y=v2 ; c[ 1].x=v1 ;   \
    c[ 2].y=v6 ; c[ 3].x=v5 ;   \
    c[ 4].y=v10; c[ 5].x=v9 ;   \
    c[ 6].y=v14; c[ 7].x=v13;   \
    c[ 8].y=v18; c[ 9].x=v17;   \
    c[10].y=v22; c[11].x=v21;   \
    c[12].y=v26; c[13].x=v25;   \
    c[14].y=v30; c[15].x=v29;   \
}

#define FFT32x32_R2C_CALC_LDS_PTRS(__aperm,__p0,__p1,__p2,__q0,__q1,__x,__y,__p,__q,__u,__v,stemp){\
    v_sub_u32(__p0,ic(32),__x);       \
    v_and_b32(__p1,ic(1),__y);        \
    v_and_b32(__p2,ic(31),__p0);      \
    v_shl_or_b32(__aperm,__p1,5,__p2);\
    v_shl_b32(__aperm,__aperm,2);     \
    v_mulk_u24(__p0,0x880,__y);       \
    v_mulk_u24(__p1,0x088,__v);       \
    v_add_u32(__p2,__p0,__p1);        \
    s_movk_i32(stemp,545);            \
    v_shl_add_u32(__p0,__x,2,__p0);   \
    v_shl_add_u32(__p1,__u,2,__p2);   \
    v_shl_add_u32(__p2,__u,6,__p2);   \
    v_mad_u24(__q0,stemp,__y,__x);    \
    v_mad_u24(__q1,stemp,__p,__q);    \
    v_addk_u32(__p0+1,0x440,__p0);    \
    v_shl_b32(__q0,__q0,2);           \
    v_shl_b32(__q1,__q1,2);           \
}

#define FFT32x32_C2R_CALC_LDS_PTRS(__a,__b,__c,__x,__y,__u,__t){\
    v_shr_b32(__b,__x,1);        \
    v_mulk_u24(__c,0x8c0,__y);   \
    v_mulk_u24(__a,0x08c,__b);   \
    v_mulk_u24(__b,0x088,__b);   \
    v_shl_add_u32(__b,__u,2,__b);\
    v_shl_add_u32(__t,__u,6,__a);\
    v_shl_add_u32(__a,__x,2,__c);\
    v_add_u32(__b,__b,__c);      \
    v_add_u32(__c,__c,__t);      \
    v_addk_u32(__a+1,0x440,__a); \
}

#define FFT16(c){                         \
    uint2* d=&c[16];                      \
    /*==============stage0==============*/\
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);     \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);     \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);     \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);     \
    v_sub_f32(d[2].x,c[2].x,c[10].x);     \
    v_sub_f32(d[2].y,c[2].y,c[10].y);     \
    v_sub_f32(d[3].x,c[3].x,c[11].x);     \
    v_sub_f32(d[3].y,c[3].y,c[11].y);     \
    v_sub_f32(d[4].x,c[4].x,c[12].x);     \
    v_sub_f32(d[4].y,c[4].y,c[12].y);     \
    v_sub_f32(d[5].x,c[5].x,c[13].x);     \
    v_sub_f32(d[5].y,c[5].y,c[13].y);     \
    v_sub_f32(d[6].x,c[6].x,c[14].x);     \
    v_sub_f32(d[6].y,c[6].y,c[14].y);     \
    v_sub_f32(d[7].x,c[7].x,c[15].x);     \
    v_sub_f32(d[7].y,c[7].y,c[15].y);     \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);     \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);     \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);     \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);     \
    v_add_f32(c[2].x,c[2].x,c[10].x);     \
    v_add_f32(c[2].y,c[2].y,c[10].y);     \
    v_add_f32(c[3].x,c[3].x,c[11].x);     \
    v_add_f32(c[3].y,c[3].y,c[11].y);     \
    v_add_f32(c[4].x,c[4].x,c[12].x);     \
    v_add_f32(c[4].y,c[4].y,c[12].y);     \
    v_add_f32(c[5].x,c[5].x,c[13].x);     \
    v_add_f32(c[5].y,c[5].y,c[13].y);     \
    v_add_f32(c[6].x,c[6].x,c[14].x);     \
    v_add_f32(c[6].y,c[6].y,c[14].y);     \
    v_add_f32(c[7].x,c[7].x,c[15].x);     \
    v_add_f32(c[7].y,c[7].y,c[15].y);     \
    /*==============stage1==============*/\
    v_add_f32(c[ 8].x,d[0].x,d[4].y);     \
    v_sub_f32(c[ 8].y,d[0].y,d[4].x);     \
    v_sub_f32(c[12].x,d[0].x,d[4].y);     \
    v_add_f32(c[12].y,d[0].y,d[4].x);     \
    v_add_f32(c[ 9].x,d[1].x,d[5].y);     \
    v_sub_f32(c[ 9].y,d[1].y,d[5].x);     \
    v_sub_f32(c[13].x,d[1].x,d[5].y);     \
    v_add_f32(c[13].y,d[1].y,d[5].x);     \
    v_add_f32(c[10].x,d[2].x,d[6].y);     \
    v_sub_f32(c[10].y,d[2].y,d[6].x);     \
    v_sub_f32(c[14].x,d[2].x,d[6].y);     \
    v_add_f32(c[14].y,d[2].y,d[6].x);     \
    v_add_f32(c[11].x,d[3].x,d[7].y);     \
    v_sub_f32(c[11].y,d[3].y,d[7].x);     \
    v_sub_f32(c[15].x,d[3].x,d[7].y);     \
    v_add_f32(c[15].y,d[3].y,d[7].x);     \
    v_sub_f32(d[0].x,c[0].x,c[4].x);      \
    v_sub_f32(d[0].y,c[0].y,c[4].y);      \
    v_sub_f32(d[1].x,c[1].x,c[5].x);      \
    v_sub_f32(d[1].y,c[1].y,c[5].y);      \
    v_sub_f32(d[2].x,c[2].x,c[6].x);      \
    v_sub_f32(d[2].y,c[2].y,c[6].y);      \
    v_sub_f32(d[3].x,c[3].x,c[7].x);      \
    v_sub_f32(d[3].y,c[3].y,c[7].y);      \
    v_add_f32(c[0].x,c[0].x,c[4].x);      \
    v_add_f32(c[0].y,c[0].y,c[4].y);      \
    v_add_f32(c[1].x,c[1].x,c[5].x);      \
    v_add_f32(c[1].y,c[1].y,c[5].y);      \
    v_add_f32(c[2].x,c[2].x,c[6].x);      \
    v_add_f32(c[2].y,c[2].y,c[6].y);      \
    v_add_f32(c[3].x,c[3].x,c[7].x);      \
    v_add_f32(c[3].y,c[3].y,c[7].y);      \
    /*==============stage2==============*/\
    v_add_f32(c[4].x,d[0].x,d[2].y);      \
    v_sub_f32(c[4].y,d[0].y,d[2].x);      \
    v_sub_f32(c[6].x,d[0].x,d[2].y);      \
    v_add_f32(c[6].y,d[0].y,d[2].x);      \
    v_add_f32(c[5].x,d[1].x,d[3].y);      \
    v_sub_f32(c[5].y,d[1].y,d[3].x);      \
    v_sub_f32(c[7].x,d[1].x,d[3].y);      \
    v_add_f32(c[7].y,d[1].y,d[3].x);      \
    v_sub_f32(d[0].x,c[0].x,c[2].x);      \
    v_sub_f32(d[0].y,c[0].y,c[2].y);      \
    v_sub_f32(d[1].x,c[1].x,c[3].x);      \
    v_sub_f32(d[1].y,c[1].y,c[3].y);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(d[6].x,c[1].x,c[3].x);      \
    v_add_f32(d[6].y,c[1].y,c[3].y);      \
    v_add_f32(d[2].x,c[10].y,c[10].x);    \
    v_sub_f32(d[2].y,c[10].y,c[10].x);    \
    v_add_f32(d[3].x,c[11].y,c[11].x);    \
    v_sub_f32(d[3].y,c[11].y,c[11].x);    \
    v_sub_f32(d[4].x,c[14].x,c[14].y);    \
    v_add_f32(d[4].y,c[14].x,c[14].y);    \
    v_sub_f32(d[5].x,c[15].x,c[15].y);    \
    v_add_f32(d[5].y,c[15].x,c[15].y);    \
    v_fma_f32(c[10].x,C0y,d[2].x,c[ 8].x);\
    v_fma_f32(c[10].y,C0y,d[2].y,c[ 8].y);\
    v_fma_f32(c[11].x,C0y,d[3].x,c[ 9].x);\
    v_fma_f32(c[11].y,C0y,d[3].y,c[ 9].y);\
    v_fma_f32(c[14].x,C0x,d[4].x,c[12].x);\
    v_fma_f32(c[14].y,C0x,d[4].y,c[12].y);\
    v_fma_f32(c[15].x,C0x,d[5].x,c[13].x);\
    v_fma_f32(c[15].y,C0x,d[5].y,c[13].y);\
    V_MAC_F32(c[ 8].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 8].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);        \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);        \
    V_MAC_F32(c[12].x,C0y,d[4].x);        \
    V_MAC_F32(c[12].y,C0y,d[4].y);        \
    V_MAC_F32(c[13].x,C0y,d[5].x);        \
    V_MAC_F32(c[13].y,C0y,d[5].y);        \
    /*==============stage3==============*/\
    v_sub_f32(c[1].x,c[0].x,d[6].x);      \
    v_sub_f32(c[1].y,c[0].y,d[6].y);      \
    v_add_f32(c[0].x,c[0].x,d[6].x);      \
    v_add_f32(c[0].y,c[0].y,d[6].y);      \
    v_add_f32(c[2].x,d[0].x,d[1].y);      \
    v_sub_f32(c[2].y,d[0].y,d[1].x);      \
    v_sub_f32(c[3].x,d[0].x,d[1].y);      \
    v_add_f32(c[3].y,d[0].y,d[1].x);      \
    v_add_f32(d[2].x,c[5].y,c[5].x);      \
    v_sub_f32(d[2].y,c[5].y,c[5].x);      \
    v_sub_f32(d[3].x,c[7].x,c[7].y);      \
    v_add_f32(d[3].y,c[7].x,c[7].y);      \
    v_fma_f32(d[4].x,C3x,c[ 9].x,c[ 9].y);\
    v_fma_f32(d[4].y,C3y,c[ 9].y,c[ 9].x);\
    v_fma_f32(d[5].x,C4y,c[11].x,c[11].y);\
    v_fma_f32(d[5].y,C4x,c[11].y,c[11].x);\
    v_fma_f32(d[6].x,C4x,c[13].x,c[13].y);\
    v_fma_f32(d[6].y,C4y,c[13].y,c[13].x);\
    v_fma_f32(d[7].x,C3y,c[15].x,c[15].y);\
    v_fma_f32(d[7].y,C3x,c[15].y,c[15].x);\
    v_fma_f32(c[ 5].x,C0y,d[2].x,c[ 4].x);\
    v_fma_f32(c[ 5].y,C0y,d[2].y,c[ 4].y);\
    v_fma_f32(c[ 7].x,C0x,d[3].x,c[ 6].x);\
    v_fma_f32(c[ 7].y,C0x,d[3].y,c[ 6].y);\
    v_fma_f32(c[ 9].x,C1y,d[4].x,c[ 8].x);\
    v_fma_f32(c[ 9].y,C1x,d[4].y,c[ 8].y);\
    v_fma_f32(c[11].x,C2y,d[5].x,c[10].x);\
    v_fma_f32(c[11].y,C2x,d[5].y,c[10].y);\
    v_fma_f32(c[13].x,C2y,d[6].x,c[12].x);\
    v_fma_f32(c[13].y,C2x,d[6].y,c[12].y);\
    v_fma_f32(c[15].x,C1y,d[7].x,c[14].x);\
    v_fma_f32(c[15].y,C1x,d[7].y,c[14].y);\
    V_MAC_F32(c[ 4].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 4].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 6].x,C0y,d[3].x);        \
    V_MAC_F32(c[ 6].y,C0y,d[3].y);        \
    V_MAC_F32(c[ 8].x,C1x,d[4].x);        \
    V_MAC_F32(c[ 8].y,C1y,d[4].y);        \
    V_MAC_F32(c[10].x,C2x,d[5].x);        \
    V_MAC_F32(c[10].y,C2y,d[5].y);        \
    V_MAC_F32(c[12].x,C2x,d[6].x);        \
    V_MAC_F32(c[12].y,C2y,d[6].y);        \
    V_MAC_F32(c[14].x,C1x,d[7].x);        \
    V_MAC_F32(c[14].y,C1y,d[7].y);        \
}

#define IFFT16(c){                        \
    uint2* d=&c[16];                      \
    /*==============stage0==============*/\
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);     \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);     \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);     \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);     \
    v_sub_f32(d[2].x,c[2].x,c[10].x);     \
    v_sub_f32(d[2].y,c[2].y,c[10].y);     \
    v_sub_f32(d[3].x,c[3].x,c[11].x);     \
    v_sub_f32(d[3].y,c[3].y,c[11].y);     \
    v_sub_f32(d[4].x,c[4].x,c[12].x);     \
    v_sub_f32(d[4].y,c[4].y,c[12].y);     \
    v_sub_f32(d[5].x,c[5].x,c[13].x);     \
    v_sub_f32(d[5].y,c[5].y,c[13].y);     \
    v_sub_f32(d[6].x,c[6].x,c[14].x);     \
    v_sub_f32(d[6].y,c[6].y,c[14].y);     \
    v_sub_f32(d[7].x,c[7].x,c[15].x);     \
    v_sub_f32(d[7].y,c[7].y,c[15].y);     \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);     \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);     \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);     \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);     \
    v_add_f32(c[2].x,c[2].x,c[10].x);     \
    v_add_f32(c[2].y,c[2].y,c[10].y);     \
    v_add_f32(c[3].x,c[3].x,c[11].x);     \
    v_add_f32(c[3].y,c[3].y,c[11].y);     \
    v_add_f32(c[4].x,c[4].x,c[12].x);     \
    v_add_f32(c[4].y,c[4].y,c[12].y);     \
    v_add_f32(c[5].x,c[5].x,c[13].x);     \
    v_add_f32(c[5].y,c[5].y,c[13].y);     \
    v_add_f32(c[6].x,c[6].x,c[14].x);     \
    v_add_f32(c[6].y,c[6].y,c[14].y);     \
    v_add_f32(c[7].x,c[7].x,c[15].x);     \
    v_add_f32(c[7].y,c[7].y,c[15].y);     \
    /*==============stage1==============*/\
    v_sub_f32(c[ 8].x,d[0].x,d[4].y);     \
    v_add_f32(c[ 8].y,d[0].y,d[4].x);     \
    v_add_f32(c[12].x,d[0].x,d[4].y);     \
    v_sub_f32(c[12].y,d[0].y,d[4].x);     \
    v_sub_f32(c[ 9].x,d[1].x,d[5].y);     \
    v_add_f32(c[ 9].y,d[1].y,d[5].x);     \
    v_add_f32(c[13].x,d[1].x,d[5].y);     \
    v_sub_f32(c[13].y,d[1].y,d[5].x);     \
    v_sub_f32(c[10].x,d[2].x,d[6].y);     \
    v_add_f32(c[10].y,d[2].y,d[6].x);     \
    v_add_f32(c[14].x,d[2].x,d[6].y);     \
    v_sub_f32(c[14].y,d[2].y,d[6].x);     \
    v_sub_f32(c[11].x,d[3].x,d[7].y);     \
    v_add_f32(c[11].y,d[3].y,d[7].x);     \
    v_add_f32(c[15].x,d[3].x,d[7].y);     \
    v_sub_f32(c[15].y,d[3].y,d[7].x);     \
    v_sub_f32(d[0].x,c[0].x,c[4].x);      \
    v_sub_f32(d[0].y,c[0].y,c[4].y);      \
    v_sub_f32(d[1].x,c[1].x,c[5].x);      \
    v_sub_f32(d[1].y,c[1].y,c[5].y);      \
    v_sub_f32(d[2].x,c[2].x,c[6].x);      \
    v_sub_f32(d[2].y,c[2].y,c[6].y);      \
    v_sub_f32(d[3].x,c[3].x,c[7].x);      \
    v_sub_f32(d[3].y,c[3].y,c[7].y);      \
    v_add_f32(c[0].x,c[0].x,c[4].x);      \
    v_add_f32(c[0].y,c[0].y,c[4].y);      \
    v_add_f32(c[1].x,c[1].x,c[5].x);      \
    v_add_f32(c[1].y,c[1].y,c[5].y);      \
    v_add_f32(c[2].x,c[2].x,c[6].x);      \
    v_add_f32(c[2].y,c[2].y,c[6].y);      \
    v_add_f32(c[3].x,c[3].x,c[7].x);      \
    v_add_f32(c[3].y,c[3].y,c[7].y);      \
    /*==============stage2==============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);      \
    v_add_f32(c[4].y,d[0].y,d[2].x);      \
    v_add_f32(c[6].x,d[0].x,d[2].y);      \
    v_sub_f32(c[6].y,d[0].y,d[2].x);      \
    v_sub_f32(c[5].x,d[1].x,d[3].y);      \
    v_add_f32(c[5].y,d[1].y,d[3].x);      \
    v_add_f32(c[7].x,d[1].x,d[3].y);      \
    v_sub_f32(c[7].y,d[1].y,d[3].x);      \
    v_sub_f32(d[0].x,c[0].x,c[2].x);      \
    v_sub_f32(d[0].y,c[0].y,c[2].y);      \
    v_sub_f32(d[1].x,c[1].x,c[3].x);      \
    v_sub_f32(d[1].y,c[1].y,c[3].y);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(d[6].x,c[ 1].x,c[ 3].x);    \
    v_add_f32(d[6].y,c[ 1].y,c[ 3].y);    \
    v_sub_f32(d[2].x,c[10].x,c[10].y);    \
    v_add_f32(d[2].y,c[10].x,c[10].y);    \
    v_sub_f32(d[3].x,c[11].x,c[11].y);    \
    v_add_f32(d[3].y,c[11].x,c[11].y);    \
    v_add_f32(d[4].x,c[14].y,c[14].x);    \
    v_sub_f32(d[4].y,c[14].y,c[14].x);    \
    v_add_f32(d[5].x,c[15].y,c[15].x);    \
    v_sub_f32(d[5].y,c[15].y,c[15].x);    \
    v_fma_f32(c[10].x,C0y,d[2].x,c[ 8].x);\
    v_fma_f32(c[10].y,C0y,d[2].y,c[ 8].y);\
    v_fma_f32(c[11].x,C0y,d[3].x,c[ 9].x);\
    v_fma_f32(c[11].y,C0y,d[3].y,c[ 9].y);\
    v_fma_f32(c[14].x,C0x,d[4].x,c[12].x);\
    v_fma_f32(c[14].y,C0x,d[4].y,c[12].y);\
    v_fma_f32(c[15].x,C0x,d[5].x,c[13].x);\
    v_fma_f32(c[15].y,C0x,d[5].y,c[13].y);\
    V_MAC_F32(c[ 8].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 8].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);        \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);        \
    V_MAC_F32(c[12].x,C0y,d[4].x);        \
    V_MAC_F32(c[12].y,C0y,d[4].y);        \
    V_MAC_F32(c[13].x,C0y,d[5].x);        \
    V_MAC_F32(c[13].y,C0y,d[5].y);        \
    /*==============stage3==============*/\
    v_sub_f32(c[1].x,c[0].x,d[6].x);      \
    v_sub_f32(c[1].y,c[0].y,d[6].y);      \
    v_add_f32(c[0].x,c[0].x,d[6].x);      \
    v_add_f32(c[0].y,c[0].y,d[6].y);      \
    v_sub_f32(c[2].x,d[0].x,d[1].y);      \
    v_add_f32(c[2].y,d[0].y,d[1].x);      \
    v_add_f32(c[3].x,d[0].x,d[1].y);      \
    v_sub_f32(c[3].y,d[0].y,d[1].x);      \
    v_sub_f32(d[2].x,c[5].x,c[5].y);      \
    v_add_f32(d[2].y,c[5].x,c[5].y);      \
    v_add_f32(d[3].x,c[7].y,c[7].x);      \
    v_sub_f32(d[3].y,c[7].y,c[7].x);      \
    v_fma_f32(d[4].x,C3y,c[ 9].x,c[ 9].y);\
    v_fma_f32(d[4].y,C3x,c[ 9].y,c[ 9].x);\
    v_fma_f32(d[5].x,C4x,c[11].x,c[11].y);\
    v_fma_f32(d[5].y,C4y,c[11].y,c[11].x);\
    v_fma_f32(d[6].x,C4y,c[13].x,c[13].y);\
    v_fma_f32(d[6].y,C4x,c[13].y,c[13].x);\
    v_fma_f32(d[7].x,C3x,c[15].x,c[15].y);\
    v_fma_f32(d[7].y,C3y,c[15].y,c[15].x);\
    v_fma_f32(c[ 5].x,C0y,d[2].x,c[ 4].x);\
    v_fma_f32(c[ 5].y,C0y,d[2].y,c[ 4].y);\
    v_fma_f32(c[ 7].x,C0x,d[3].x,c[ 6].x);\
    v_fma_f32(c[ 7].y,C0x,d[3].y,c[ 6].y);\
    v_fma_f32(c[ 9].x,C1x,d[4].x,c[ 8].x);\
    v_fma_f32(c[ 9].y,C1y,d[4].y,c[ 8].y);\
    v_fma_f32(c[11].x,C2x,d[5].x,c[10].x);\
    v_fma_f32(c[11].y,C2y,d[5].y,c[10].y);\
    v_fma_f32(c[13].x,C2x,d[6].x,c[12].x);\
    v_fma_f32(c[13].y,C2y,d[6].y,c[12].y);\
    v_fma_f32(c[15].x,C1x,d[7].x,c[14].x);\
    v_fma_f32(c[15].y,C1y,d[7].y,c[14].y);\
    V_MAC_F32(c[ 4].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 4].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 6].x,C0y,d[3].x);        \
    V_MAC_F32(c[ 6].y,C0y,d[3].y);        \
    V_MAC_F32(c[ 8].x,C1y,d[4].x);        \
    V_MAC_F32(c[ 8].y,C1x,d[4].y);        \
    V_MAC_F32(c[10].x,C2y,d[5].x);        \
    V_MAC_F32(c[10].y,C2x,d[5].y);        \
    V_MAC_F32(c[12].x,C2y,d[6].x);        \
    V_MAC_F32(c[12].y,C2x,d[6].y);        \
    V_MAC_F32(c[14].x,C1y,d[7].x);        \
    V_MAC_F32(c[14].y,C1x,d[7].y);        \
}

#define IHFFT16(c){                       \
    uint2* d=&c[16];                      \
    /*==============stage0==============*/\
    s_sync(lgkmcnt(6));                   \
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);     \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);     \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);     \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);     \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);     \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);     \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);     \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);     \
    s_sync(lgkmcnt(4));                   \
    v_sub_f32(d[2].x,c[2].x,c[10].x);     \
    v_sub_f32(d[2].y,c[2].y,c[10].y);     \
    v_sub_f32(d[3].x,c[3].x,c[11].x);     \
    v_sub_f32(d[3].y,c[3].y,c[11].y);     \
    v_add_f32(c[2].x,c[2].x,c[10].x);     \
    v_add_f32(c[2].y,c[2].y,c[10].y);     \
    v_add_f32(c[3].x,c[3].x,c[11].x);     \
    v_add_f32(c[3].y,c[3].y,c[11].y);     \
    s_sync(lgkmcnt(2));                   \
    v_sub_f32(d[4].x,c[4].x,c[12].x);     \
    v_sub_f32(d[4].y,c[4].y,c[12].y);     \
    v_sub_f32(d[5].x,c[5].x,c[13].x);     \
    v_sub_f32(d[5].y,c[5].y,c[13].y);     \
    v_add_f32(c[4].x,c[4].x,c[12].x);     \
    v_add_f32(c[4].y,c[4].y,c[12].y);     \
    v_add_f32(c[5].x,c[5].x,c[13].x);     \
    v_add_f32(c[5].y,c[5].y,c[13].y);     \
    s_sync(lgkmcnt(0));                   \
    v_sub_f32(d[6].x,c[6].x,c[14].x);     \
    v_sub_f32(d[6].y,c[6].y,c[14].y);     \
    v_sub_f32(d[7].x,c[7].x,c[15].x);     \
    v_sub_f32(d[7].y,c[7].y,c[15].y);     \
    v_add_f32(c[6].x,c[6].x,c[14].x);     \
    v_add_f32(c[6].y,c[6].y,c[14].y);     \
    v_add_f32(c[7].x,c[7].x,c[15].x);     \
    v_add_f32(c[7].y,c[7].y,c[15].y);     \
    /*==============stage1==============*/\
    v_sub_f32(c[ 8].x,d[0].x,d[4].y);     \
    v_add_f32(c[ 8].y,d[0].y,d[4].x);     \
    v_add_f32(c[12].x,d[0].x,d[4].y);     \
    v_sub_f32(c[12].y,d[0].y,d[4].x);     \
    v_sub_f32(c[ 9].x,d[1].x,d[5].y);     \
    v_add_f32(c[ 9].y,d[1].y,d[5].x);     \
    v_add_f32(c[13].x,d[1].x,d[5].y);     \
    v_sub_f32(c[13].y,d[1].y,d[5].x);     \
    v_sub_f32(c[10].x,d[2].x,d[6].y);     \
    v_add_f32(c[10].y,d[2].y,d[6].x);     \
    v_add_f32(c[14].x,d[2].x,d[6].y);     \
    v_sub_f32(c[14].y,d[2].y,d[6].x);     \
    v_sub_f32(c[11].x,d[3].x,d[7].y);     \
    v_add_f32(c[11].y,d[3].y,d[7].x);     \
    v_add_f32(c[15].x,d[3].x,d[7].y);     \
    v_sub_f32(c[15].y,d[3].y,d[7].x);     \
    v_sub_f32(d[0].x,c[0].x,c[4].x);      \
    v_sub_f32(d[0].y,c[0].y,c[4].y);      \
    v_sub_f32(d[1].x,c[1].x,c[5].x);      \
    v_sub_f32(d[1].y,c[1].y,c[5].y);      \
    v_sub_f32(d[2].x,c[2].x,c[6].x);      \
    v_sub_f32(d[2].y,c[2].y,c[6].y);      \
    v_sub_f32(d[3].x,c[3].x,c[7].x);      \
    v_sub_f32(d[3].y,c[3].y,c[7].y);      \
    v_add_f32(c[0].x,c[0].x,c[4].x);      \
    v_add_f32(c[0].y,c[0].y,c[4].y);      \
    v_add_f32(c[1].x,c[1].x,c[5].x);      \
    v_add_f32(c[1].y,c[1].y,c[5].y);      \
    v_add_f32(c[2].x,c[2].x,c[6].x);      \
    v_add_f32(c[2].y,c[2].y,c[6].y);      \
    v_add_f32(c[3].x,c[3].x,c[7].x);      \
    v_add_f32(c[3].y,c[3].y,c[7].y);      \
    /*==============stage2==============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);      \
    v_add_f32(c[4].y,d[0].y,d[2].x);      \
    v_add_f32(c[6].x,d[0].x,d[2].y);      \
    v_sub_f32(c[6].y,d[0].y,d[2].x);      \
    v_sub_f32(c[5].x,d[1].x,d[3].y);      \
    v_add_f32(c[5].y,d[1].y,d[3].x);      \
    v_add_f32(c[7].x,d[1].x,d[3].y);      \
    v_sub_f32(c[7].y,d[1].y,d[3].x);      \
    v_sub_f32(d[0].x,c[0].x,c[2].x);      \
    v_sub_f32(d[0].y,c[0].y,c[2].y);      \
    v_sub_f32(d[1].x,c[1].x,c[3].x);      \
    v_sub_f32(d[1].y,c[1].y,c[3].y);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(d[6].x,c[ 1].x,c[ 3].x);    \
    v_add_f32(d[6].y,c[ 1].y,c[ 3].y);    \
    v_sub_f32(d[2].x,c[10].x,c[10].y);    \
    v_add_f32(d[2].y,c[10].x,c[10].y);    \
    v_sub_f32(d[3].x,c[11].x,c[11].y);    \
    v_add_f32(d[3].y,c[11].x,c[11].y);    \
    v_add_f32(d[4].x,c[14].y,c[14].x);    \
    v_sub_f32(d[4].y,c[14].y,c[14].x);    \
    v_add_f32(d[5].x,c[15].y,c[15].x);    \
    v_sub_f32(d[5].y,c[15].y,c[15].x);    \
    v_fma_f32(c[10].x,C0y,d[2].x,c[ 8].x);\
    v_fma_f32(c[10].y,C0y,d[2].y,c[ 8].y);\
    v_fma_f32(c[11].x,C0y,d[3].x,c[ 9].x);\
    v_fma_f32(c[11].y,C0y,d[3].y,c[ 9].y);\
    v_fma_f32(c[14].x,C0x,d[4].x,c[12].x);\
    v_fma_f32(c[14].y,C0x,d[4].y,c[12].y);\
    v_fma_f32(c[15].x,C0x,d[5].x,c[13].x);\
    v_fma_f32(c[15].y,C0x,d[5].y,c[13].y);\
    V_MAC_F32(c[ 8].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 8].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);        \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);        \
    V_MAC_F32(c[12].x,C0y,d[4].x);        \
    V_MAC_F32(c[12].y,C0y,d[4].y);        \
    V_MAC_F32(c[13].x,C0y,d[5].x);        \
    V_MAC_F32(c[13].y,C0y,d[5].y);        \
    /*==============stage3==============*/\
    v_sub_f32(c[1].x,c[0].x,d[6].x);      \
    v_sub_f32(c[1].y,c[0].y,d[6].y);      \
    v_add_f32(c[0].x,c[0].x,d[6].x);      \
    v_add_f32(c[0].y,c[0].y,d[6].y);      \
    v_sub_f32(c[2].x,d[0].x,d[1].y);      \
    v_add_f32(c[2].y,d[0].y,d[1].x);      \
    v_add_f32(c[3].x,d[0].x,d[1].y);      \
    v_sub_f32(c[3].y,d[0].y,d[1].x);      \
    v_sub_f32(d[2].x,c[5].x,c[5].y);      \
    v_add_f32(d[2].y,c[5].x,c[5].y);      \
    v_add_f32(d[3].x,c[7].y,c[7].x);      \
    v_sub_f32(d[3].y,c[7].y,c[7].x);      \
    v_fma_f32(d[4].x,C3y,c[ 9].x,c[ 9].y);\
    v_fma_f32(d[4].y,C3x,c[ 9].y,c[ 9].x);\
    v_fma_f32(d[5].x,C4x,c[11].x,c[11].y);\
    v_fma_f32(d[5].y,C4y,c[11].y,c[11].x);\
    v_fma_f32(d[6].x,C4y,c[13].x,c[13].y);\
    v_fma_f32(d[6].y,C4x,c[13].y,c[13].x);\
    v_fma_f32(d[7].x,C3x,c[15].x,c[15].y);\
    v_fma_f32(d[7].y,C3y,c[15].y,c[15].x);\
    v_fma_f32(c[ 5].x,C0y,d[2].x,c[ 4].x);\
    v_fma_f32(c[ 5].y,C0y,d[2].y,c[ 4].y);\
    v_fma_f32(c[ 7].x,C0x,d[3].x,c[ 6].x);\
    v_fma_f32(c[ 7].y,C0x,d[3].y,c[ 6].y);\
    v_fma_f32(c[ 9].x,C1x,d[4].x,c[ 8].x);\
    v_fma_f32(c[ 9].y,C1y,d[4].y,c[ 8].y);\
    v_fma_f32(c[11].x,C2x,d[5].x,c[10].x);\
    v_fma_f32(c[11].y,C2y,d[5].y,c[10].y);\
    v_fma_f32(c[13].x,C2x,d[6].x,c[12].x);\
    v_fma_f32(c[13].y,C2y,d[6].y,c[12].y);\
    v_fma_f32(c[15].x,C1x,d[7].x,c[14].x);\
    v_fma_f32(c[15].y,C1y,d[7].y,c[14].y);\
    V_MAC_F32(c[ 4].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 4].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 6].x,C0y,d[3].x);        \
    V_MAC_F32(c[ 6].y,C0y,d[3].y);        \
    V_MAC_F32(c[ 8].x,C1y,d[4].x);        \
    V_MAC_F32(c[ 8].y,C1x,d[4].y);        \
    V_MAC_F32(c[10].x,C2y,d[5].x);        \
    V_MAC_F32(c[10].y,C2x,d[5].y);        \
    V_MAC_F32(c[12].x,C2y,d[6].x);        \
    V_MAC_F32(c[12].y,C2x,d[6].y);        \
    V_MAC_F32(c[14].x,C1y,d[7].x);        \
    V_MAC_F32(c[14].y,C1x,d[7].y);        \
}

#define FFT16_C2(c){                      \
    v_add_f32(c[2].x,c[0].x,c[1].y);      \
    v_sub_f32(c[2].y,c[0].y,c[1].x);      \
    v_sub_f32(c[3].x,c[0].x,c[1].y);      \
    v_add_f32(c[3].y,c[0].y,c[1].x);      \
    v_add_f32(c[8].x,c[1].x,c[1].y);      \
    v_sub_f32(c[8].y,c[1].x,c[1].y);      \
    v_fma_f32(c[ 4].x,C0x,c[ 8].x,c[0].x);\
    v_fma_f32(c[ 4].y,C0y,c[ 8].y,c[0].y);\
    v_fma_f32(c[ 5].x,C0y,c[ 8].x,c[0].x);\
    v_fma_f32(c[ 5].y,C0x,c[ 8].y,c[0].y);\
    v_fma_f32(c[ 6].x,C0y,c[ 8].y,c[0].x);\
    v_fma_f32(c[ 6].y,C0y,c[ 8].x,c[0].y);\
    v_fma_f32(c[ 7].x,C0x,c[ 8].y,c[0].x);\
    v_fma_f32(c[ 7].y,C0x,c[ 8].x,c[0].y);\
    v_fma_f32(c[ 9].x,C3x,c[ 1].x,c[1].y);\
    v_fma_f32(c[ 9].y,C3y,c[ 1].y,c[1].x);\
    v_fma_f32(c[ 8].x,C1x,c[ 9].x,c[0].x);\
    v_fma_f32(c[ 8].y,C1y,c[ 9].y,c[0].y);\
    v_fma_f32(c[ 9].x,C1y,c[ 9].x,c[0].x);\
    v_fma_f32(c[ 9].y,C1x,c[ 9].y,c[0].y);\
    v_fma_f32(c[11].x,C4y,c[ 1].x,c[1].y);\
    v_fma_f32(c[11].y,C4x,c[ 1].y,c[1].x);\
    v_fma_f32(c[10].x,C2x,c[11].x,c[0].x);\
    v_fma_f32(c[10].y,C2y,c[11].y,c[0].y);\
    v_fma_f32(c[11].x,C2y,c[11].x,c[0].x);\
    v_fma_f32(c[11].y,C2x,c[11].y,c[0].y);\
    v_fma_f32(c[13].x,C4x,c[ 1].x,c[1].y);\
    v_fma_f32(c[13].y,C4y,c[ 1].y,c[1].x);\
    v_fma_f32(c[12].x,C2x,c[13].x,c[0].x);\
    v_fma_f32(c[12].y,C2y,c[13].y,c[0].y);\
    v_fma_f32(c[13].x,C2y,c[13].x,c[0].x);\
    v_fma_f32(c[13].y,C2x,c[13].y,c[0].y);\
    v_fma_f32(c[15].x,C3y,c[ 1].x,c[1].y);\
    v_fma_f32(c[15].y,C3x,c[ 1].y,c[1].x);\
    v_fma_f32(c[14].x,C1x,c[15].x,c[0].x);\
    v_fma_f32(c[14].y,C1y,c[15].y,c[0].y);\
    v_fma_f32(c[15].x,C1y,c[15].x,c[0].x);\
    v_fma_f32(c[15].y,C1x,c[15].y,c[0].y);\
    v_add_f32(c[0].x,c[0].x,c[1].x);      \
    v_add_f32(c[0].y,c[0].y,c[1].y);      \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);  \
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);  \
}

#define IFFT16_C2(c){                     \
    v_sub_f32(c[2].x,c[0].x,c[1].y);      \
    v_add_f32(c[2].y,c[0].y,c[1].x);      \
    v_add_f32(c[3].x,c[0].x,c[1].y);      \
    v_sub_f32(c[3].y,c[0].y,c[1].x);      \
    v_add_f32(c[8].x,c[1].x,c[1].y);      \
    v_sub_f32(c[8].y,c[1].x,c[1].y);      \
    v_fma_f32(c[ 4].x,C0x,c[ 8].y,c[0].x);\
    v_fma_f32(c[ 4].y,C0x,c[ 8].x,c[0].y);\
    v_fma_f32(c[ 5].x,C0y,c[ 8].y,c[0].x);\
    v_fma_f32(c[ 5].y,C0y,c[ 8].x,c[0].y);\
    v_fma_f32(c[ 6].x,C0y,c[ 8].x,c[0].x);\
    v_fma_f32(c[ 6].y,C0x,c[ 8].y,c[0].y);\
    v_fma_f32(c[ 7].x,C0x,c[ 8].x,c[0].x);\
    v_fma_f32(c[ 7].y,C0y,c[ 8].y,c[0].y);\
    v_fma_f32(c[ 9].x,C3y,c[ 1].x,c[1].y);\
    v_fma_f32(c[ 9].y,C3x,c[ 1].y,c[1].x);\
    v_fma_f32(c[ 8].x,C1y,c[ 9].x,c[0].x);\
    v_fma_f32(c[ 8].y,C1x,c[ 9].y,c[0].y);\
    v_fma_f32(c[ 9].x,C1x,c[ 9].x,c[0].x);\
    v_fma_f32(c[ 9].y,C1y,c[ 9].y,c[0].y);\
    v_fma_f32(c[11].x,C4x,c[ 1].x,c[1].y);\
    v_fma_f32(c[11].y,C4y,c[ 1].y,c[1].x);\
    v_fma_f32(c[10].x,C2y,c[11].x,c[0].x);\
    v_fma_f32(c[10].y,C2x,c[11].y,c[0].y);\
    v_fma_f32(c[11].x,C2x,c[11].x,c[0].x);\
    v_fma_f32(c[11].y,C2y,c[11].y,c[0].y);\
    v_fma_f32(c[13].x,C4y,c[ 1].x,c[1].y);\
    v_fma_f32(c[13].y,C4x,c[ 1].y,c[1].x);\
    v_fma_f32(c[12].x,C2y,c[13].x,c[0].x);\
    v_fma_f32(c[12].y,C2x,c[13].y,c[0].y);\
    v_fma_f32(c[13].x,C2x,c[13].x,c[0].x);\
    v_fma_f32(c[13].y,C2y,c[13].y,c[0].y);\
    v_fma_f32(c[15].x,C3x,c[ 1].x,c[1].y);\
    v_fma_f32(c[15].y,C3y,c[ 1].y,c[1].x);\
    v_fma_f32(c[14].x,C1y,c[15].x,c[0].x);\
    v_fma_f32(c[14].y,C1x,c[15].y,c[0].y);\
    v_fma_f32(c[15].x,C1x,c[15].x,c[0].x);\
    v_fma_f32(c[15].y,C1y,c[15].y,c[0].y);\
    v_add_f32(c[0].x,c[0].x,c[1].x);      \
    v_add_f32(c[0].y,c[0].y,c[1].y);      \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);  \
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);  \
}

#define FFT16_C3(c){                      \
    v_add_f32(c[4].x,c[0].x,c[2].y);      \
    v_sub_f32(c[4].y,c[0].y,c[2].x);      \
    v_sub_f32(c[6].x,c[0].x,c[2].y);      \
    v_add_f32(c[6].y,c[0].y,c[2].x);      \
    v_add_f32(c[3].x,c[2].x,c[2].y);      \
    v_sub_f32(c[3].y,c[2].x,c[2].y);      \
    v_fma_f32(c[ 8].x,C0x,c[3].x,c[0].x); \
    v_fma_f32(c[ 8].y,C0y,c[3].y,c[0].y); \
    v_fma_f32(c[10].x,C0y,c[3].x,c[0].x); \
    v_fma_f32(c[10].y,C0x,c[3].y,c[0].y); \
    v_fma_f32(c[12].x,C0y,c[3].y,c[0].x); \
    v_fma_f32(c[12].y,C0y,c[3].x,c[0].y); \
    v_fma_f32(c[14].x,C0x,c[3].y,c[0].x); \
    v_fma_f32(c[14].y,C0x,c[3].x,c[0].y); \
    v_add_f32(c[ 3].x,c[1].x,c[1].y);     \
    v_sub_f32(c[ 3].y,c[1].x,c[1].y);     \
    v_fma_f32(c[ 7].x,C0x,c[3].y,c[6].x); \
    v_fma_f32(c[ 7].y,C0x,c[3].x,c[6].y); \
    V_MAC_F32(c[ 6].x,C0y,c[3].y);        \
    V_MAC_F32(c[ 6].y,C0y,c[3].x);        \
    v_fma_f32(c[ 5].x,C0y,c[3].x,c[4].x); \
    v_fma_f32(c[ 5].y,C0x,c[3].y,c[4].y); \
    V_MAC_F32(c[ 4].x,C0x,c[3].x);        \
    V_MAC_F32(c[ 4].y,C0y,c[3].y);        \
    v_fma_f32(c[ 3].x,C3x,c[1].x,c[1].y); \
    v_fma_f32(c[ 3].y,C3y,c[1].y,c[1].x); \
    v_fma_f32(c[ 9].x,C1y,c[3].x,c[8].x); \
    v_fma_f32(c[ 9].y,C1x,c[3].y,c[8].y); \
    V_MAC_F32(c[ 8].x,C1x,c[3].x);        \
    V_MAC_F32(c[ 8].y,C1y,c[3].y);        \
    v_fma_f32(c[ 3].x,C4y,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C4x,c[1].y,c[ 1].x);\
    v_fma_f32(c[11].x,C2y,c[3].x,c[10].x);\
    v_fma_f32(c[11].y,C2x,c[3].y,c[10].y);\
    V_MAC_F32(c[10].x,C2x,c[3].x);        \
    V_MAC_F32(c[10].y,C2y,c[3].y);        \
    v_fma_f32(c[ 3].x,C4x,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C4y,c[1].y,c[ 1].x);\
    v_fma_f32(c[13].x,C2y,c[3].x,c[12].x);\
    v_fma_f32(c[13].y,C2x,c[3].y,c[12].y);\
    V_MAC_F32(c[12].x,C2x,c[3].x);        \
    V_MAC_F32(c[12].y,C2y,c[3].y);        \
    v_fma_f32(c[ 3].x,C3y,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C3x,c[1].y,c[ 1].x);\
    v_fma_f32(c[15].x,C1y,c[3].x,c[14].x);\
    v_fma_f32(c[15].y,C1x,c[3].y,c[14].y);\
    V_MAC_F32(c[14].x,C1x,c[3].x);        \
    V_MAC_F32(c[14].y,C1y,c[3].y);        \
    v_sub_f32(c[3].x,c[0].x,c[2].x);      \
    v_sub_f32(c[3].y,c[0].y,c[2].y);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(c[2].x,c[3].x,c[1].y);      \
    v_sub_f32(c[2].y,c[3].y,c[1].x);      \
    v_sub_f32(c[3].x,c[3].x,c[1].y);      \
    v_add_f32(c[3].y,c[3].y,c[1].x);      \
    v_add_f32(c[0].x,c[0].x,c[1].x);      \
    v_add_f32(c[0].y,c[0].y,c[1].y);      \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);  \
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);  \
}

#define IFFT16_C3(c){                     \
    v_sub_f32(c[4].x,c[0].x,c[2].y);      \
    v_add_f32(c[4].y,c[0].y,c[2].x);      \
    v_add_f32(c[6].x,c[0].x,c[2].y);      \
    v_sub_f32(c[6].y,c[0].y,c[2].x);      \
    v_add_f32(c[3].x,c[2].x,c[2].y);      \
    v_sub_f32(c[3].y,c[2].x,c[2].y);      \
    v_fma_f32(c[ 8].x,C0x,c[3].y,c[0].x); \
    v_fma_f32(c[ 8].y,C0x,c[3].x,c[0].y); \
    v_fma_f32(c[10].x,C0y,c[3].y,c[0].x); \
    v_fma_f32(c[10].y,C0y,c[3].x,c[0].y); \
    v_fma_f32(c[12].x,C0y,c[3].x,c[0].x); \
    v_fma_f32(c[12].y,C0x,c[3].y,c[0].y); \
    v_fma_f32(c[14].x,C0x,c[3].x,c[0].x); \
    v_fma_f32(c[14].y,C0y,c[3].y,c[0].y); \
    v_add_f32(c[ 3].x,c[1].x,c[1].y);     \
    v_sub_f32(c[ 3].y,c[1].x,c[1].y);     \
    v_fma_f32(c[ 5].x,C0y,c[3].y,c[4].x); \
    v_fma_f32(c[ 5].y,C0y,c[3].x,c[4].y); \
    V_MAC_F32(c[ 4].x,C0x,c[3].y);        \
    V_MAC_F32(c[ 4].y,C0x,c[3].x);        \
    v_fma_f32(c[ 7].x,C0x,c[3].x,c[6].x); \
    v_fma_f32(c[ 7].y,C0y,c[3].y,c[6].y); \
    V_MAC_F32(c[ 6].x,C0y,c[3].x);        \
    V_MAC_F32(c[ 6].y,C0x,c[3].y);        \
    v_fma_f32(c[ 3].x,C3y,c[1].x,c[1].y); \
    v_fma_f32(c[ 3].y,C3x,c[1].y,c[1].x); \
    v_fma_f32(c[ 9].x,C1x,c[3].x,c[8].x); \
    v_fma_f32(c[ 9].y,C1y,c[3].y,c[8].y); \
    V_MAC_F32(c[ 8].x,C1y,c[3].x);        \
    V_MAC_F32(c[ 8].y,C1x,c[3].y);        \
    v_fma_f32(c[ 3].x,C4x,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C4y,c[1].y,c[ 1].x);\
    v_fma_f32(c[11].x,C2x,c[3].x,c[10].x);\
    v_fma_f32(c[11].y,C2y,c[3].y,c[10].y);\
    V_MAC_F32(c[10].x,C2y,c[3].x);        \
    V_MAC_F32(c[10].y,C2x,c[3].y);        \
    v_fma_f32(c[ 3].x,C4y,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C4x,c[1].y,c[ 1].x);\
    v_fma_f32(c[13].x,C2x,c[3].x,c[12].x);\
    v_fma_f32(c[13].y,C2y,c[3].y,c[12].y);\
    V_MAC_F32(c[12].x,C2y,c[3].x);        \
    V_MAC_F32(c[12].y,C2x,c[3].y);        \
    v_fma_f32(c[ 3].x,C3x,c[1].x,c[ 1].y);\
    v_fma_f32(c[ 3].y,C3y,c[1].y,c[ 1].x);\
    v_fma_f32(c[15].x,C1x,c[3].x,c[14].x);\
    v_fma_f32(c[15].y,C1y,c[3].y,c[14].y);\
    V_MAC_F32(c[14].x,C1y,c[3].x);        \
    V_MAC_F32(c[14].y,C1x,c[3].y);        \
    v_sub_f32(c[3].x,c[0].x,c[2].x);      \
    v_sub_f32(c[3].y,c[0].y,c[2].y);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_sub_f32(c[2].x,c[3].x,c[1].y);      \
    v_add_f32(c[2].y,c[3].y,c[1].x);      \
    v_add_f32(c[3].x,c[3].x,c[1].y);      \
    v_sub_f32(c[3].y,c[3].y,c[1].x);      \
    v_add_f32(c[0].x,c[0].x,c[1].x);      \
    v_add_f32(c[0].y,c[0].y,c[1].y);      \
    v_fma_f32(c[1].x,nf2,c[1].x,c[0].x);  \
    v_fma_f32(c[1].y,nf2,c[1].y,c[0].y);  \
}

#define VFFT32(c,sst,sld){                    \
    uint2* d=&c[16];                          \
    FFT16(c);                                 \
    v_add_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_add_f32(d[0].y,c[ 8].y,c[15].y);        \
    v_add_f32(d[1].x,c[ 4].y,c[ 7].y);        \
    v_add_f32(d[1].y,c[12].y,c[11].y);        \
    v_add_f32(d[2].x,c[ 2].y,c[ 3].y);        \
    v_add_f32(d[2].y,c[10].y,c[13].y);        \
    v_add_f32(d[3].x,c[ 6].y,c[ 5].y);        \
    v_add_f32(d[3].y,c[14].y,c[ 9].y);        \
    v_mul_f32(d[0].y,k0x,d[0].y);             \
    v_mul_f32(d[1].x,k2x,d[1].x);             \
    v_mul_f32(d[1].y,k4x,d[1].y);             \
    v_mul_f32(d[2].x,k6x,d[2].x);             \
    v_mul_f32(d[2].y,k8x,d[2].y);             \
    v_mul_f32(d[3].x,kax,d[3].x);             \
    v_mul_f32(d[3].y,kcx,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].x,neg(d[0].y));\
    v_fma_f32(d[7].x,sk1,c[ 7].x,neg(d[1].x));\
    v_fma_f32(d[6].y,sk2,c[11].x,neg(d[1].y));\
    v_fma_f32(d[6].x,sk3,c[ 3].x,neg(d[2].x));\
    v_fma_f32(d[5].y,sk4,c[13].x,neg(d[2].y));\
    v_fma_f32(d[5].x,sk5,c[ 5].x,neg(d[3].x));\
    v_fma_f32(d[4].y,sk6,c[ 9].x,neg(d[3].y));\
    V_MAC_F32(d[7].y,k1x,c[ 8].x);            \
    V_MAC_F32(d[7].x,k3x,c[ 4].x);            \
    V_MAC_F32(d[6].y,k5x,c[12].x);            \
    V_MAC_F32(d[6].x,k7x,c[ 2].x);            \
    V_MAC_F32(d[5].y,k9x,c[10].x);            \
    V_MAC_F32(d[5].x,kbx,c[ 6].x);            \
    V_MAC_F32(d[4].y,kdx,c[14].x);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].x);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].x);            \
    V_MAC_F32(d[1].y,sk2,c[12].x);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].x);            \
    V_MAC_F32(d[2].y,sk4,c[10].x);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].x);            \
    V_MAC_F32(d[3].y,sk6,c[14].x);            \
    V_MAC_F32(d[0].y,k1x,c[15].x);            \
    V_MAC_F32(d[1].x,k3x,c[ 7].x);            \
    V_MAC_F32(d[1].y,k5x,c[11].x);            \
    V_MAC_F32(d[2].x,k7x,c[ 3].x);            \
    V_MAC_F32(d[2].y,k9x,c[13].x);            \
    V_MAC_F32(d[3].x,kbx,c[ 5].x);            \
    V_MAC_F32(d[3].y,kdx,c[ 9].x);            \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,c[1].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    v_sub_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_sub_f32(d[0].y,c[ 8].x,c[15].x);        \
    v_sub_f32(d[1].x,c[ 4].x,c[ 7].x);        \
    v_sub_f32(d[1].y,c[12].x,c[11].x);        \
    v_sub_f32(d[2].x,c[ 2].x,c[ 3].x);        \
    v_sub_f32(d[2].y,c[10].x,c[13].x);        \
    v_sub_f32(d[3].x,c[ 6].x,c[ 5].x);        \
    v_sub_f32(d[3].y,c[14].x,c[ 9].x);        \
    v_mul_f32(d[4].x,nfone,c[1].y);           \
    v_mul_f32(d[0].y,k0y,d[0].y);             \
    v_mul_f32(d[1].x,k2y,d[1].x);             \
    v_mul_f32(d[1].y,k4y,d[1].y);             \
    v_mul_f32(d[2].x,k6y,d[2].x);             \
    v_mul_f32(d[2].y,k8y,d[2].y);             \
    v_mul_f32(d[3].x,kay,d[3].x);             \
    v_mul_f32(d[3].y,kcy,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].y,d[0].y);     \
    v_fma_f32(d[7].x,sk1,c[ 7].y,d[1].x);     \
    v_fma_f32(d[6].y,sk2,c[11].y,d[1].y);     \
    v_fma_f32(d[6].x,sk3,c[ 3].y,d[2].x);     \
    v_fma_f32(d[5].y,sk4,c[13].y,d[2].y);     \
    v_fma_f32(d[5].x,sk5,c[ 5].y,d[3].x);     \
    v_fma_f32(d[4].y,sk6,c[ 9].y,d[3].y);     \
    s_sync(lgkmcnt(0));                       \
    lsld_b32x2(c[ 0].x,sld,0x00,0x02);        \
    lsld_b32x2(c[ 2].x,sld,0x04,0x06);        \
    lsld_b32x2(c[ 4].x,sld,0x08,0x0a);        \
    lsld_b32x2(c[ 6].x,sld,0x0c,0x0e);        \
    lsld_b32x2(c[ 8].x,sld,0x10,0x12);        \
    lsld_b32x2(c[10].x,sld,0x14,0x16);        \
    lsld_b32x2(c[12].x,sld,0x18,0x1a);        \
    lsld_b32x2(c[14].x,sld,0x1c,0x1e);        \
    V_MAC_F32(d[7].y,k1y,c[ 8].y);            \
    V_MAC_F32(d[7].x,k3y,c[ 4].y);            \
    V_MAC_F32(d[6].y,k5y,c[12].y);            \
    V_MAC_F32(d[6].x,k7y,c[ 2].y);            \
    V_MAC_F32(d[5].y,k9y,c[10].y);            \
    V_MAC_F32(d[5].x,kby,c[ 6].y);            \
    V_MAC_F32(d[4].y,kdy,c[14].y);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].y);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].y);            \
    V_MAC_F32(d[1].y,sk2,c[12].y);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].y);            \
    V_MAC_F32(d[2].y,sk4,c[10].y);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].y);            \
    V_MAC_F32(d[3].y,sk6,c[14].y);            \
    V_MAC_F32(d[0].y,k1y,c[15].y);            \
    V_MAC_F32(d[1].x,k3y,c[ 7].y);            \
    V_MAC_F32(d[1].y,k5y,c[11].y);            \
    V_MAC_F32(d[2].x,k7y,c[ 3].y);            \
    V_MAC_F32(d[2].y,k9y,c[13].y);            \
    V_MAC_F32(d[3].x,kby,c[ 5].y);            \
    V_MAC_F32(d[3].y,kdy,c[ 9].y);            \
    s_sync(lgkmcnt(0));                       \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,d[4].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    s_sync(lgkmcnt(0));                       \
    lsld_b32x2(c[ 0].y,sld,0x00,0x02);        \
    lsld_b32x2(c[ 2].y,sld,0x04,0x06);        \
    lsld_b32x2(c[ 4].y,sld,0x08,0x0a);        \
    lsld_b32x2(c[ 6].y,sld,0x0c,0x0e);        \
    lsld_b32x2(c[ 8].y,sld,0x10,0x12);        \
    lsld_b32x2(c[10].y,sld,0x14,0x16);        \
    lsld_b32x2(c[12].y,sld,0x18,0x1a);        \
    lsld_b32x2(c[14].y,sld,0x1c,0x1e);        \
    s_sync(lgkmcnt(0));                       \
}

#define VFFT32_C2(c,sst,sld){                 \
    uint2* d=&c[16];                          \
    FFT16_C2(c);                              \
    v_add_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_add_f32(d[0].y,c[ 8].y,c[15].y);        \
    v_add_f32(d[1].x,c[ 4].y,c[ 7].y);        \
    v_add_f32(d[1].y,c[12].y,c[11].y);        \
    v_add_f32(d[2].x,c[ 2].y,c[ 3].y);        \
    v_add_f32(d[2].y,c[10].y,c[13].y);        \
    v_add_f32(d[3].x,c[ 6].y,c[ 5].y);        \
    v_add_f32(d[3].y,c[14].y,c[ 9].y);        \
    v_mul_f32(d[0].y,k0x,d[0].y);             \
    v_mul_f32(d[1].x,k2x,d[1].x);             \
    v_mul_f32(d[1].y,k4x,d[1].y);             \
    v_mul_f32(d[2].x,k6x,d[2].x);             \
    v_mul_f32(d[2].y,k8x,d[2].y);             \
    v_mul_f32(d[3].x,kax,d[3].x);             \
    v_mul_f32(d[3].y,kcx,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].x,neg(d[0].y));\
    v_fma_f32(d[7].x,sk1,c[ 7].x,neg(d[1].x));\
    v_fma_f32(d[6].y,sk2,c[11].x,neg(d[1].y));\
    v_fma_f32(d[6].x,sk3,c[ 3].x,neg(d[2].x));\
    v_fma_f32(d[5].y,sk4,c[13].x,neg(d[2].y));\
    v_fma_f32(d[5].x,sk5,c[ 5].x,neg(d[3].x));\
    v_fma_f32(d[4].y,sk6,c[ 9].x,neg(d[3].y));\
    V_MAC_F32(d[7].y,k1x,c[ 8].x);            \
    V_MAC_F32(d[7].x,k3x,c[ 4].x);            \
    V_MAC_F32(d[6].y,k5x,c[12].x);            \
    V_MAC_F32(d[6].x,k7x,c[ 2].x);            \
    V_MAC_F32(d[5].y,k9x,c[10].x);            \
    V_MAC_F32(d[5].x,kbx,c[ 6].x);            \
    V_MAC_F32(d[4].y,kdx,c[14].x);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].x);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].x);            \
    V_MAC_F32(d[1].y,sk2,c[12].x);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].x);            \
    V_MAC_F32(d[2].y,sk4,c[10].x);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].x);            \
    V_MAC_F32(d[3].y,sk6,c[14].x);            \
    V_MAC_F32(d[0].y,k1x,c[15].x);            \
    V_MAC_F32(d[1].x,k3x,c[ 7].x);            \
    V_MAC_F32(d[1].y,k5x,c[11].x);            \
    V_MAC_F32(d[2].x,k7x,c[ 3].x);            \
    V_MAC_F32(d[2].y,k9x,c[13].x);            \
    V_MAC_F32(d[3].x,kbx,c[ 5].x);            \
    V_MAC_F32(d[3].y,kdx,c[ 9].x);            \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,c[1].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    v_sub_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_sub_f32(d[0].y,c[ 8].x,c[15].x);        \
    v_sub_f32(d[1].x,c[ 4].x,c[ 7].x);        \
    v_sub_f32(d[1].y,c[12].x,c[11].x);        \
    v_sub_f32(d[2].x,c[ 2].x,c[ 3].x);        \
    v_sub_f32(d[2].y,c[10].x,c[13].x);        \
    v_sub_f32(d[3].x,c[ 6].x,c[ 5].x);        \
    v_sub_f32(d[3].y,c[14].x,c[ 9].x);        \
    v_mul_f32(d[4].x,nfone,c[1].y);           \
    v_mul_f32(d[0].y,k0y,d[0].y);             \
    v_mul_f32(d[1].x,k2y,d[1].x);             \
    v_mul_f32(d[1].y,k4y,d[1].y);             \
    v_mul_f32(d[2].x,k6y,d[2].x);             \
    v_mul_f32(d[2].y,k8y,d[2].y);             \
    v_mul_f32(d[3].x,kay,d[3].x);             \
    v_mul_f32(d[3].y,kcy,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].y,d[0].y);     \
    v_fma_f32(d[7].x,sk1,c[ 7].y,d[1].x);     \
    v_fma_f32(d[6].y,sk2,c[11].y,d[1].y);     \
    v_fma_f32(d[6].x,sk3,c[ 3].y,d[2].x);     \
    v_fma_f32(d[5].y,sk4,c[13].y,d[2].y);     \
    v_fma_f32(d[5].x,sk5,c[ 5].y,d[3].x);     \
    v_fma_f32(d[4].y,sk6,c[ 9].y,d[3].y);     \
    V_MAC_F32(d[7].y,k1y,c[ 8].y);            \
    V_MAC_F32(d[7].x,k3y,c[ 4].y);            \
    V_MAC_F32(d[6].y,k5y,c[12].y);            \
    V_MAC_F32(d[6].x,k7y,c[ 2].y);            \
    V_MAC_F32(d[5].y,k9y,c[10].y);            \
    V_MAC_F32(d[5].x,kby,c[ 6].y);            \
    V_MAC_F32(d[4].y,kdy,c[14].y);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].y);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].y);            \
    V_MAC_F32(d[1].y,sk2,c[12].y);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].y);            \
    V_MAC_F32(d[2].y,sk4,c[10].y);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].y);            \
    V_MAC_F32(d[3].y,sk6,c[14].y);            \
    s_sync(lgkmcnt(0));                       \
    lsld_b32x2(c[0].x,sld,0,2);               \
    V_MAC_F32(d[0].y,k1y,c[15].y);            \
    V_MAC_F32(d[1].x,k3y,c[ 7].y);            \
    V_MAC_F32(d[1].y,k5y,c[11].y);            \
    V_MAC_F32(d[2].x,k7y,c[ 3].y);            \
    V_MAC_F32(d[2].y,k9y,c[13].y);            \
    V_MAC_F32(d[3].x,kby,c[ 5].y);            \
    V_MAC_F32(d[3].y,kdy,c[ 9].y);            \
    s_sync(lgkmcnt(0));                       \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,d[4].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    s_sync(lgkmcnt(0));                       \
    lsld_b32x2(c[0].y,sld,0,2);               \
    s_sync(lgkmcnt(0));                       \
}

#define VFFT32_C3(c,sst,sld){                 \
    uint2* d=&c[16];                          \
    FFT16_C3(c);                              \
    v_add_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_add_f32(d[0].y,c[ 8].y,c[15].y);        \
    v_add_f32(d[1].x,c[ 4].y,c[ 7].y);        \
    v_add_f32(d[1].y,c[12].y,c[11].y);        \
    v_add_f32(d[2].x,c[ 2].y,c[ 3].y);        \
    v_add_f32(d[2].y,c[10].y,c[13].y);        \
    v_add_f32(d[3].x,c[ 6].y,c[ 5].y);        \
    v_add_f32(d[3].y,c[14].y,c[ 9].y);        \
    v_mul_f32(d[0].y,k0x,d[0].y);             \
    v_mul_f32(d[1].x,k2x,d[1].x);             \
    v_mul_f32(d[1].y,k4x,d[1].y);             \
    v_mul_f32(d[2].x,k6x,d[2].x);             \
    v_mul_f32(d[2].y,k8x,d[2].y);             \
    v_mul_f32(d[3].x,kax,d[3].x);             \
    v_mul_f32(d[3].y,kcx,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].x,neg(d[0].y));\
    v_fma_f32(d[7].x,sk1,c[ 7].x,neg(d[1].x));\
    v_fma_f32(d[6].y,sk2,c[11].x,neg(d[1].y));\
    v_fma_f32(d[6].x,sk3,c[ 3].x,neg(d[2].x));\
    v_fma_f32(d[5].y,sk4,c[13].x,neg(d[2].y));\
    v_fma_f32(d[5].x,sk5,c[ 5].x,neg(d[3].x));\
    v_fma_f32(d[4].y,sk6,c[ 9].x,neg(d[3].y));\
    V_MAC_F32(d[7].y,k1x,c[ 8].x);            \
    V_MAC_F32(d[7].x,k3x,c[ 4].x);            \
    V_MAC_F32(d[6].y,k5x,c[12].x);            \
    V_MAC_F32(d[6].x,k7x,c[ 2].x);            \
    V_MAC_F32(d[5].y,k9x,c[10].x);            \
    V_MAC_F32(d[5].x,kbx,c[ 6].x);            \
    V_MAC_F32(d[4].y,kdx,c[14].x);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].x);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].x);            \
    V_MAC_F32(d[1].y,sk2,c[12].x);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].x);            \
    V_MAC_F32(d[2].y,sk4,c[10].x);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].x);            \
    V_MAC_F32(d[3].y,sk6,c[14].x);            \
    V_MAC_F32(d[0].y,k1x,c[15].x);            \
    V_MAC_F32(d[1].x,k3x,c[ 7].x);            \
    V_MAC_F32(d[1].y,k5x,c[11].x);            \
    V_MAC_F32(d[2].x,k7x,c[ 3].x);            \
    V_MAC_F32(d[2].y,k9x,c[13].x);            \
    V_MAC_F32(d[3].x,kbx,c[ 5].x);            \
    V_MAC_F32(d[3].y,kdx,c[ 9].x);            \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,c[1].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    v_sub_f32(d[0].x,c[ 0].x,c[ 0].y);        \
    v_sub_f32(d[0].y,c[ 8].x,c[15].x);        \
    v_sub_f32(d[1].x,c[ 4].x,c[ 7].x);        \
    v_sub_f32(d[1].y,c[12].x,c[11].x);        \
    v_sub_f32(d[2].x,c[ 2].x,c[ 3].x);        \
    v_sub_f32(d[2].y,c[10].x,c[13].x);        \
    v_sub_f32(d[3].x,c[ 6].x,c[ 5].x);        \
    v_sub_f32(d[3].y,c[14].x,c[ 9].x);        \
    v_mul_f32(d[4].x,nfone,c[1].y);           \
    v_mul_f32(d[0].y,k0y,d[0].y);             \
    v_mul_f32(d[1].x,k2y,d[1].x);             \
    v_mul_f32(d[1].y,k4y,d[1].y);             \
    v_mul_f32(d[2].x,k6y,d[2].x);             \
    v_mul_f32(d[2].y,k8y,d[2].y);             \
    v_mul_f32(d[3].x,kay,d[3].x);             \
    v_mul_f32(d[3].y,kcy,d[3].y);             \
    v_fma_f32(d[7].y,sk0,c[15].y,d[0].y);     \
    v_fma_f32(d[7].x,sk1,c[ 7].y,d[1].x);     \
    v_fma_f32(d[6].y,sk2,c[11].y,d[1].y);     \
    v_fma_f32(d[6].x,sk3,c[ 3].y,d[2].x);     \
    v_fma_f32(d[5].y,sk4,c[13].y,d[2].y);     \
    v_fma_f32(d[5].x,sk5,c[ 5].y,d[3].x);     \
    v_fma_f32(d[4].y,sk6,c[ 9].y,d[3].y);     \
    V_MAC_F32(d[7].y,k1y,c[ 8].y);            \
    V_MAC_F32(d[7].x,k3y,c[ 4].y);            \
    V_MAC_F32(d[6].y,k5y,c[12].y);            \
    V_MAC_F32(d[6].x,k7y,c[ 2].y);            \
    V_MAC_F32(d[5].y,k9y,c[10].y);            \
    V_MAC_F32(d[5].x,kby,c[ 6].y);            \
    V_MAC_F32(d[4].y,kdy,c[14].y);            \
    V_MAC_F32(d[0].y,sk0,c[ 8].y);            \
    V_MAC_F32(d[1].x,sk1,c[ 4].y);            \
    V_MAC_F32(d[1].y,sk2,c[12].y);            \
    V_MAC_F32(d[2].x,sk3,c[ 2].y);            \
    V_MAC_F32(d[2].y,sk4,c[10].y);            \
    V_MAC_F32(d[3].x,sk5,c[ 6].y);            \
    V_MAC_F32(d[3].y,sk6,c[14].y);            \
    s_sync(lgkmcnt(0));                       \
    lsld_b32(c[0].x,sld,0x00);                \
    lsld_b32(c[1].x,sld,0x08);                \
    lsld_b32(c[2].x,sld,0x10);                \
    V_MAC_F32(d[0].y,k1y,c[15].y);            \
    V_MAC_F32(d[1].x,k3y,c[ 7].y);            \
    V_MAC_F32(d[1].y,k5y,c[11].y);            \
    V_MAC_F32(d[2].x,k7y,c[ 3].y);            \
    V_MAC_F32(d[2].y,k9y,c[13].y);            \
    V_MAC_F32(d[3].x,kby,c[ 5].y);            \
    V_MAC_F32(d[3].y,kdy,c[ 9].y);            \
    s_sync(lgkmcnt(0));                       \
    lsst_b32x2(sst+0,0*34,d[0].x,1*34,d[0].y);\
    lsst_b32x2(sst+0,2*34,d[1].x,3*34,d[1].y);\
    lsst_b32x2(sst+0,4*34,d[2].x,5*34,d[2].y);\
    lsst_b32x2(sst+0,6*34,d[3].x,7*34,d[3].y);\
    lsst_b32x2(sst+1,0*34,d[4].x,1*34,d[4].y);\
    lsst_b32x2(sst+1,2*34,d[5].x,3*34,d[5].y);\
    lsst_b32x2(sst+1,4*34,d[6].x,5*34,d[6].y);\
    lsst_b32x2(sst+1,6*34,d[7].x,7*34,d[7].y);\
    s_sync(lgkmcnt(0));                       \
    lsld_b32(c[0].y,sld,0x00);                \
    lsld_b32(c[1].y,sld,0x08);                \
    lsld_b32(c[2].y,sld,0x10);                \
    s_sync(lgkmcnt(0));                       \
}

#define HFFT32(c,sst,sld,u,pshuf,stemp,M){     \
    FFT16##M(c)                                \
    uint2* d=&c[16];                           \
    v_cmp_u32(zero,u,ne);                      \
    s_andexec_b64(stemp,vcc);                  \
    v_exch_b32(c[1].x,c[1].y);                 \
    v_mul_f32(c[1].y,nfone,c[1].y);            \
    v_mul_f32(d[ 0].x,C0x,c[ 2].y);            \
    v_mul_f32(d[ 0].y,C0x,c[ 3].y);            \
    v_mul_f32(d[ 1].x,C1x,c[ 4].y);            \
    v_mul_f32(d[ 1].y,C2x,c[ 5].y);            \
    v_mul_f32(d[ 2].x,C2x,c[ 6].y);            \
    v_mul_f32(d[ 2].y,C1x,c[ 7].y);            \
    v_mul_f32(d[ 3].x,C6x,c[ 8].y);            \
    v_mul_f32(d[ 3].y,C5x,c[ 9].y);            \
    v_mul_f32(d[ 4].x,C7x,c[10].y);            \
    v_mul_f32(d[ 4].y,C8x,c[11].y);            \
    v_mul_f32(d[ 5].x,C8x,c[12].y);            \
    v_mul_f32(d[ 5].y,C7x,c[13].y);            \
    v_mul_f32(d[ 6].x,C5x,c[14].y);            \
    v_mul_f32(d[ 6].y,C6x,c[15].y);            \
    v_mul_f32(c[ 2].y,C0x,c[ 2].y);            \
    v_mul_f32(c[ 3].y,C0y,c[ 3].y);            \
    v_mul_f32(c[ 4].y,C2x,c[ 4].y);            \
    v_mul_f32(c[ 5].y,C1y,c[ 5].y);            \
    v_mul_f32(c[ 6].y,C1x,c[ 6].y);            \
    v_mul_f32(c[ 7].y,C2y,c[ 7].y);            \
    v_mul_f32(c[ 8].y,C5x,c[ 8].y);            \
    v_mul_f32(c[ 9].y,C6y,c[ 9].y);            \
    v_mul_f32(c[10].y,C8x,c[10].y);            \
    v_mul_f32(c[11].y,C7y,c[11].y);            \
    v_mul_f32(c[12].y,C7x,c[12].y);            \
    v_mul_f32(c[13].y,C8y,c[13].y);            \
    v_mul_f32(c[14].y,C6x,c[14].y);            \
    v_mul_f32(c[15].y,C5y,c[15].y);            \
    V_MAC_F32(c[ 2].y,C0y,c[ 2].x);            \
    V_MAC_F32(c[ 3].y,C0y,c[ 3].x);            \
    V_MAC_F32(c[ 4].y,C1y,c[ 4].x);            \
    V_MAC_F32(c[ 5].y,C2y,c[ 5].x);            \
    V_MAC_F32(c[ 6].y,C2y,c[ 6].x);            \
    V_MAC_F32(c[ 7].y,C1y,c[ 7].x);            \
    V_MAC_F32(c[ 8].y,C6y,c[ 8].x);            \
    V_MAC_F32(c[ 9].y,C5y,c[ 9].x);            \
    V_MAC_F32(c[10].y,C7y,c[10].x);            \
    V_MAC_F32(c[11].y,C8y,c[11].x);            \
    V_MAC_F32(c[12].y,C8y,c[12].x);            \
    V_MAC_F32(c[13].y,C7y,c[13].x);            \
    V_MAC_F32(c[14].y,C5y,c[14].x);            \
    V_MAC_F32(c[15].y,C6y,c[15].x);            \
    v_fma_f32(c[ 2].x,C0x,c[ 2].x,d[0].x);     \
    v_fma_f32(c[ 3].x,C0y,c[ 3].x,d[0].y);     \
    v_fma_f32(c[ 4].x,C2x,c[ 4].x,d[1].x);     \
    v_fma_f32(c[ 5].x,C1y,c[ 5].x,d[1].y);     \
    v_fma_f32(c[ 6].x,C1x,c[ 6].x,d[2].x);     \
    v_fma_f32(c[ 7].x,C2y,c[ 7].x,d[2].y);     \
    v_fma_f32(c[ 8].x,C5x,c[ 8].x,d[3].x);     \
    v_fma_f32(c[ 9].x,C6y,c[ 9].x,d[3].y);     \
    v_fma_f32(c[10].x,C8x,c[10].x,d[4].x);     \
    v_fma_f32(c[11].x,C7y,c[11].x,d[4].y);     \
    v_fma_f32(c[12].x,C7x,c[12].x,d[5].x);     \
    v_fma_f32(c[13].x,C8y,c[13].x,d[5].y);     \
    v_fma_f32(c[14].x,C6x,c[14].x,d[6].x);     \
    v_fma_f32(c[15].x,C5y,c[15].x,d[6].y);     \
    s_mov_b64(exec,stemp);                     \
    uint32_t sign=u;                           \
    v_shl_or_b32(sign,u,31,fone);              \
    dpp_shf_xor_b32(d[0].x,c[ 0].x,1);         \
    dpp_shf_xor_b32(d[0].y,c[ 8].x,1);         \
    dpp_shf_xor_b32(d[1].x,c[ 4].x,1);         \
    dpp_shf_xor_b32(d[1].y,c[12].x,1);         \
    dpp_shf_xor_b32(d[2].x,c[ 2].x,1);         \
    dpp_shf_xor_b32(d[2].y,c[10].x,1);         \
    dpp_shf_xor_b32(d[3].x,c[ 6].x,1);         \
    dpp_shf_xor_b32(d[3].y,c[14].x,1);         \
    dpp_shf_xor_b32(d[4].x,c[ 1].x,1);         \
    dpp_shf_xor_b32(d[4].y,c[ 9].x,1);         \
    dpp_shf_xor_b32(d[5].x,c[ 5].x,1);         \
    dpp_shf_xor_b32(d[5].y,c[13].x,1);         \
    dpp_shf_xor_b32(d[6].x,c[ 3].x,1);         \
    dpp_shf_xor_b32(d[6].y,c[11].x,1);         \
    dpp_shf_xor_b32(d[7].x,c[ 7].x,1);         \
    dpp_shf_xor_b32(d[7].y,c[15].x,1);         \
    V_MAC_F32(d[0].x,sign,c[ 0].x);            \
    V_MAC_F32(d[0].y,sign,c[ 8].x);            \
    V_MAC_F32(d[1].x,sign,c[ 4].x);            \
    V_MAC_F32(d[1].y,sign,c[12].x);            \
    V_MAC_F32(d[2].x,sign,c[ 2].x);            \
    V_MAC_F32(d[2].y,sign,c[10].x);            \
    V_MAC_F32(d[3].x,sign,c[ 6].x);            \
    V_MAC_F32(d[3].y,sign,c[14].x);            \
    V_MAC_F32(d[4].x,sign,c[ 1].x);            \
    V_MAC_F32(d[4].y,sign,c[ 9].x);            \
    V_MAC_F32(d[5].x,sign,c[ 5].x);            \
    V_MAC_F32(d[5].y,sign,c[13].x);            \
    V_MAC_F32(d[6].x,sign,c[ 3].x);            \
    V_MAC_F32(d[6].y,sign,c[11].x);            \
    V_MAC_F32(d[7].x,sign,c[ 7].x);            \
    V_MAC_F32(d[7].y,sign,c[15].x);            \
    lsst_b32x2(sst,0x0,d[0].x,0x1,d[0].y);     \
    lsst_b32x2(sst,0x2,d[1].x,0x3,d[1].y);     \
    lsst_b32x2(sst,0x4,d[2].x,0x5,d[2].y);     \
    lsst_b32x2(sst,0x6,d[3].x,0x7,d[3].y);     \
    lsst_b32x2(sst,0x8,d[4].x,0x9,d[4].y);     \
    lsst_b32x2(sst,0xa,d[5].x,0xb,d[5].y);     \
    lsst_b32x2(sst,0xc,d[6].x,0xd,d[6].y);     \
    lsst_b32x2(sst,0xe,d[7].x,0xf,d[7].y);     \
    dpp_shf_xor_b32(d[0].x,c[ 0].y,1);         \
    dpp_shf_xor_b32(d[0].y,c[ 8].y,1);         \
    dpp_shf_xor_b32(d[1].x,c[ 4].y,1);         \
    dpp_shf_xor_b32(d[1].y,c[12].y,1);         \
    dpp_shf_xor_b32(d[2].x,c[ 2].y,1);         \
    dpp_shf_xor_b32(d[2].y,c[10].y,1);         \
    dpp_shf_xor_b32(d[3].x,c[ 6].y,1);         \
    dpp_shf_xor_b32(d[3].y,c[14].y,1);         \
    dpp_shf_xor_b32(d[4].x,c[ 1].y,1);         \
    dpp_shf_xor_b32(d[4].y,c[ 9].y,1);         \
    dpp_shf_xor_b32(d[5].x,c[ 5].y,1);         \
    dpp_shf_xor_b32(d[5].y,c[13].y,1);         \
    dpp_shf_xor_b32(d[6].x,c[ 3].y,1);         \
    dpp_shf_xor_b32(d[6].y,c[11].y,1);         \
    dpp_shf_xor_b32(d[7].x,c[ 7].y,1);         \
    dpp_shf_xor_b32(d[7].y,c[15].y,1);         \
    s_sync(lgkmcnt(0));                        \
    lsld_b32x2(c[ 0].x,sld+0,0*34,1*34);       \
    lsld_b32x2(c[ 2].x,sld+0,2*34,3*34);       \
    lsld_b32x2(c[ 4].x,sld+0,4*34,5*34);       \
    lsld_b32x2(c[ 6].x,sld+0,6*34,7*34);       \
    lsld_b32x2(c[ 8].x,sld+1,0*34,1*34);       \
    lsld_b32x2(c[10].x,sld+1,2*34,3*34);       \
    lsld_b32x2(c[12].x,sld+1,4*34,5*34);       \
    lsld_b32x2(c[14].x,sld+1,6*34,7*34);       \
    V_MAC_F32(d[0].x,sign,c[ 0].y);            \
    V_MAC_F32(d[0].y,sign,c[ 8].y);            \
    V_MAC_F32(d[1].x,sign,c[ 4].y);            \
    V_MAC_F32(d[1].y,sign,c[12].y);            \
    V_MAC_F32(d[2].x,sign,c[ 2].y);            \
    V_MAC_F32(d[2].y,sign,c[10].y);            \
    V_MAC_F32(d[3].x,sign,c[ 6].y);            \
    V_MAC_F32(d[3].y,sign,c[14].y);            \
    V_MAC_F32(d[4].x,sign,c[ 1].y);            \
    V_MAC_F32(d[4].y,sign,c[ 9].y);            \
    V_MAC_F32(d[5].x,sign,c[ 5].y);            \
    V_MAC_F32(d[5].y,sign,c[13].y);            \
    V_MAC_F32(d[6].x,sign,c[ 3].y);            \
    V_MAC_F32(d[6].y,sign,c[11].y);            \
    V_MAC_F32(d[7].x,sign,c[ 7].y);            \
    V_MAC_F32(d[7].y,sign,c[15].y);            \
    s_sync(lgkmcnt(0));                        \
    lsst_b32x2(sst,0x0,d[0].x,0x1,d[0].y);     \
    lsst_b32x2(sst,0x2,d[1].x,0x3,d[1].y);     \
    lsst_b32x2(sst,0x4,d[2].x,0x5,d[2].y);     \
    lsst_b32x2(sst,0x6,d[3].x,0x7,d[3].y);     \
    lsst_b32x2(sst,0x8,d[4].x,0x9,d[4].y);     \
    lsst_b32x2(sst,0xa,d[5].x,0xb,d[5].y);     \
    lsst_b32x2(sst,0xc,d[6].x,0xd,d[6].y);     \
    lsst_b32x2(sst,0xe,d[7].x,0xf,d[7].y);     \
    s_sync(lgkmcnt(0));                        \
    lsld_b32x2(c[ 0].y,sld+0,0*34,1*34);       \
    lsld_b32x2(c[ 2].y,sld+0,2*34,3*34);       \
    lsld_b32x2(c[ 4].y,sld+0,4*34,5*34);       \
    lsld_b32x2(c[ 6].y,sld+0,6*34,7*34);       \
    lsld_b32x2(c[ 8].y,sld+1,0*34,1*34);       \
    lsld_b32x2(c[10].y,sld+1,2*34,3*34);       \
    lsld_b32x2(c[12].y,sld+1,4*34,5*34);       \
    lsld_b32x2(c[14].y,sld+1,6*34,7*34);       \
    s_sync(lgkmcnt(7));                        \
    v_mul_f32(c[0].x,fhalf,c[0].x);            \
    v_mul_f32(c[0].y,fhalf,c[0].y);            \
    ls_bperm_b32(v34,pshuf,0x0,c[0].x);        \
    ls_bperm_b32(v35,pshuf,0x0,c[0].y);        \
    s_sync(lgkmcnt(0));                        \
    v_sub_f32(c[16].y,v34,c[0].x);             \
    v_add_f32(c[16].x,v35,c[0].y);             \
    v_add_f32(c[0].x,c[0].x,v34);              \
    v_sub_f32(c[0].y,c[0].y,v35);              \
}

#define HIFFT32(c,spa,spb,spc,u,stemp){         \
    uint2* d=&c[16];                            \
    v_sub_f32(c[0].x,c[0].x,c[16].y);           \
    v_add_f32(c[0].y,c[0].y,c[16].x);           \
    FFT32x32_C2R_RRENAME(c);                    \
    lsst_b32x2(spa+0,0*34,c[ 0].x,1*34,c[ 1].x);\
    lsst_b32x2(spa+0,2*34,c[ 2].x,3*34,c[ 3].x);\
    lsst_b32x2(spa+0,4*34,c[ 4].x,5*34,c[ 5].x);\
    lsst_b32x2(spa+0,6*34,c[ 6].x,7*34,c[ 7].x);\
    lsst_b32x2(spa+1,0*34,c[ 8].x,1*34,c[ 9].x);\
    lsst_b32x2(spa+1,2*34,c[10].x,3*34,c[11].x);\
    lsst_b32x2(spa+1,4*34,c[12].x,5*34,c[13].x);\
    lsst_b32x2(spa+1,6*34,c[14].x,7*34,c[15].x);\
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[ 0].x,spb,0x00,0x02);          \
    lsld_b32x2(c[ 2].x,spb,0x04,0x06);          \
    lsld_b32x2(c[ 4].x,spb,0x08,0x0a);          \
    lsld_b32x2(c[ 6].x,spb,0x0c,0x0e);          \
    lsld_b32x2(c[ 8].x,spb,0x10,0x12);          \
    lsld_b32x2(c[10].x,spb,0x14,0x16);          \
    lsld_b32x2(c[12].x,spb,0x18,0x1a);          \
    lsld_b32x2(c[14].x,spb,0x1c,0x1e);          \
    s_sync(lgkmcnt(0));                         \
    lsst_b32x2(spa+0,0*34,c[ 0].y,1*34,c[ 1].y);\
    lsst_b32x2(spa+0,2*34,c[ 2].y,3*34,c[ 3].y);\
    lsst_b32x2(spa+0,4*34,c[ 4].y,5*34,c[ 5].y);\
    lsst_b32x2(spa+0,6*34,c[ 6].y,7*34,c[ 7].y);\
    lsst_b32x2(spa+1,0*34,c[ 8].y,1*34,c[ 9].y);\
    lsst_b32x2(spa+1,2*34,c[10].y,3*34,c[11].y);\
    lsst_b32x2(spa+1,4*34,c[12].y,5*34,c[13].y);\
    lsst_b32x2(spa+1,6*34,c[14].y,7*34,c[15].y);\
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[ 0].y,spb,0x00,0x02);          \
    lsld_b32x2(c[ 8].y,spb,0x10,0x12);          \
    lsld_b32x2(c[ 2].y,spb,0x04,0x06);          \
    lsld_b32x2(c[10].y,spb,0x14,0x16);          \
    lsld_b32x2(c[ 4].y,spb,0x08,0x0a);          \
    lsld_b32x2(c[12].y,spb,0x18,0x1a);          \
    lsld_b32x2(c[ 6].y,spb,0x0c,0x0e);          \
    lsld_b32x2(c[14].y,spb,0x1c,0x1e);          \
    IHFFT16(c)                                  \
    v_cmp_u32(zero,u,ne);                       \
    s_andexec_b64(stemp,vcc);                   \
    v_exch_b32(c[1].x,c[1].y);                  \
    v_mul_f32(c[1].x,nfone,c[1].x);             \
    v_mul_f32(c[1].y,nfone,c[1].y);             \
    v_mul_f32(d[ 0].x,C0y,c[ 2].y);             \
    v_mul_f32(d[ 0].y,C0y,c[ 3].y);             \
    v_mul_f32(d[ 1].x,C1y,c[ 4].y);             \
    v_mul_f32(d[ 1].y,C2y,c[ 5].y);             \
    v_mul_f32(d[ 2].x,C2y,c[ 6].y);             \
    v_mul_f32(d[ 2].y,C1y,c[ 7].y);             \
    v_mul_f32(d[ 3].x,C6y,c[ 8].y);             \
    v_mul_f32(d[ 3].y,C5y,c[ 9].y);             \
    v_mul_f32(d[ 4].x,C7y,c[10].y);             \
    v_mul_f32(d[ 4].y,C8y,c[11].y);             \
    v_mul_f32(d[ 5].x,C8y,c[12].y);             \
    v_mul_f32(d[ 5].y,C7y,c[13].y);             \
    v_mul_f32(d[ 6].x,C5y,c[14].y);             \
    v_mul_f32(d[ 6].y,C6y,c[15].y);             \
    v_mul_f32(c[ 2].y,C0y,c[ 2].y);             \
    v_mul_f32(c[ 3].y,C0x,c[ 3].y);             \
    v_mul_f32(c[ 4].y,C2y,c[ 4].y);             \
    v_mul_f32(c[ 5].y,C1x,c[ 5].y);             \
    v_mul_f32(c[ 6].y,C1y,c[ 6].y);             \
    v_mul_f32(c[ 7].y,C2x,c[ 7].y);             \
    v_mul_f32(c[ 8].y,C5y,c[ 8].y);             \
    v_mul_f32(c[ 9].y,C6x,c[ 9].y);             \
    v_mul_f32(c[10].y,C8y,c[10].y);             \
    v_mul_f32(c[11].y,C7x,c[11].y);             \
    v_mul_f32(c[12].y,C7y,c[12].y);             \
    v_mul_f32(c[13].y,C8x,c[13].y);             \
    v_mul_f32(c[14].y,C6y,c[14].y);             \
    v_mul_f32(c[15].y,C5x,c[15].y);             \
    V_MAC_F32(c[ 2].y,C0y,c[ 2].x);             \
    V_MAC_F32(c[ 3].y,C0y,c[ 3].x);             \
    V_MAC_F32(c[ 4].y,C1y,c[ 4].x);             \
    V_MAC_F32(c[ 5].y,C2y,c[ 5].x);             \
    V_MAC_F32(c[ 6].y,C2y,c[ 6].x);             \
    V_MAC_F32(c[ 7].y,C1y,c[ 7].x);             \
    V_MAC_F32(c[ 8].y,C6y,c[ 8].x);             \
    V_MAC_F32(c[ 9].y,C5y,c[ 9].x);             \
    V_MAC_F32(c[10].y,C7y,c[10].x);             \
    V_MAC_F32(c[11].y,C8y,c[11].x);             \
    V_MAC_F32(c[12].y,C8y,c[12].x);             \
    V_MAC_F32(c[13].y,C7y,c[13].x);             \
    V_MAC_F32(c[14].y,C5y,c[14].x);             \
    V_MAC_F32(c[15].y,C6y,c[15].x);             \
    v_fma_f32(c[ 2].x,C0x,c[ 2].x,d[0].x);      \
    v_fma_f32(c[ 3].x,C0y,c[ 3].x,d[0].y);      \
    v_fma_f32(c[ 4].x,C2x,c[ 4].x,d[1].x);      \
    v_fma_f32(c[ 5].x,C1y,c[ 5].x,d[1].y);      \
    v_fma_f32(c[ 6].x,C1x,c[ 6].x,d[2].x);      \
    v_fma_f32(c[ 7].x,C2y,c[ 7].x,d[2].y);      \
    v_fma_f32(c[ 8].x,C5x,c[ 8].x,d[3].x);      \
    v_fma_f32(c[ 9].x,C6y,c[ 9].x,d[3].y);      \
    v_fma_f32(c[10].x,C8x,c[10].x,d[4].x);      \
    v_fma_f32(c[11].x,C7y,c[11].x,d[4].y);      \
    v_fma_f32(c[12].x,C7x,c[12].x,d[5].x);      \
    v_fma_f32(c[13].x,C8y,c[13].x,d[5].y);      \
    v_fma_f32(c[14].x,C6x,c[14].x,d[6].x);      \
    v_fma_f32(c[15].x,C5y,c[15].x,d[6].y);      \
    s_not_b64(exec,vcc);                        \
    v_mul_f32(c[ 1].y,nfone,c[ 1].y);           \
    v_mul_f32(c[ 2].y,nfone,c[ 2].y);           \
    v_mul_f32(c[ 3].y,nfone,c[ 3].y);           \
    v_mul_f32(c[ 4].y,nfone,c[ 4].y);           \
    v_mul_f32(c[ 5].y,nfone,c[ 5].y);           \
    v_mul_f32(c[ 6].y,nfone,c[ 6].y);           \
    v_mul_f32(c[ 7].y,nfone,c[ 7].y);           \
    v_mul_f32(c[ 8].y,nfone,c[ 8].y);           \
    v_mul_f32(c[ 9].y,nfone,c[ 9].y);           \
    v_mul_f32(c[10].y,nfone,c[10].y);           \
    v_mul_f32(c[11].y,nfone,c[11].y);           \
    v_mul_f32(c[12].y,nfone,c[12].y);           \
    v_mul_f32(c[13].y,nfone,c[13].y);           \
    v_mul_f32(c[14].y,nfone,c[14].y);           \
    v_mul_f32(c[15].y,nfone,c[15].y);           \
    s_mov_b64(exec,stemp);                      \
    uint32_t sign=u;                            \
    v_shl_or_b32(sign,u,31,fone);               \
    dpp_shf_xor_b32(d[0].x,c[ 0].x,1);          \
    dpp_shf_xor_b32(d[0].y,c[ 8].x,1);          \
    dpp_shf_xor_b32(d[1].x,c[ 4].x,1);          \
    dpp_shf_xor_b32(d[1].y,c[12].x,1);          \
    dpp_shf_xor_b32(d[2].x,c[ 2].x,1);          \
    dpp_shf_xor_b32(d[2].y,c[10].x,1);          \
    dpp_shf_xor_b32(d[3].x,c[ 6].x,1);          \
    dpp_shf_xor_b32(d[3].y,c[14].x,1);          \
    dpp_shf_xor_b32(d[4].x,c[ 1].x,1);          \
    dpp_shf_xor_b32(d[4].y,c[ 9].x,1);          \
    dpp_shf_xor_b32(d[5].x,c[ 5].x,1);          \
    dpp_shf_xor_b32(d[5].y,c[13].x,1);          \
    dpp_shf_xor_b32(d[6].x,c[ 3].x,1);          \
    dpp_shf_xor_b32(d[6].y,c[11].x,1);          \
    dpp_shf_xor_b32(d[7].x,c[ 7].x,1);          \
    dpp_shf_xor_b32(d[7].y,c[15].x,1);          \
    V_MAC_F32(d[0].x,sign,c[ 0].x);             \
    V_MAC_F32(d[0].y,sign,c[ 8].x);             \
    V_MAC_F32(d[1].x,sign,c[ 4].x);             \
    V_MAC_F32(d[1].y,sign,c[12].x);             \
    V_MAC_F32(d[2].x,sign,c[ 2].x);             \
    V_MAC_F32(d[2].y,sign,c[10].x);             \
    V_MAC_F32(d[3].x,sign,c[ 6].x);             \
    V_MAC_F32(d[3].y,sign,c[14].x);             \
    V_MAC_F32(d[4].x,sign,c[ 1].x);             \
    V_MAC_F32(d[4].y,sign,c[ 9].x);             \
    V_MAC_F32(d[5].x,sign,c[ 5].x);             \
    V_MAC_F32(d[5].y,sign,c[13].x);             \
    V_MAC_F32(d[6].x,sign,c[ 3].x);             \
    V_MAC_F32(d[6].y,sign,c[11].x);             \
    V_MAC_F32(d[7].x,sign,c[ 7].x);             \
    V_MAC_F32(d[7].y,sign,c[15].x);             \
    lsst_b32x2(spc,0x0,d[0].x,0x1,d[0].y);      \
    lsst_b32x2(spc,0x2,d[1].x,0x3,d[1].y);      \
    lsst_b32x2(spc,0x4,d[2].x,0x5,d[2].y);      \
    lsst_b32x2(spc,0x6,d[3].x,0x7,d[3].y);      \
    lsst_b32x2(spc,0x8,d[4].x,0x9,d[4].y);      \
    lsst_b32x2(spc,0xa,d[5].x,0xb,d[5].y);      \
    lsst_b32x2(spc,0xc,d[6].x,0xd,d[6].y);      \
    lsst_b32x2(spc,0xe,d[7].x,0xf,d[7].y);      \
    v_add_u32(spa+1,ic(32),spa+1);              \
    dpp_shf_xor_b32(d[0].x,c[ 0].y,1);          \
    dpp_shf_xor_b32(d[0].y,c[ 8].y,1);          \
    dpp_shf_xor_b32(d[1].x,c[ 4].y,1);          \
    dpp_shf_xor_b32(d[1].y,c[12].y,1);          \
    dpp_shf_xor_b32(d[2].x,c[ 2].y,1);          \
    dpp_shf_xor_b32(d[2].y,c[10].y,1);          \
    dpp_shf_xor_b32(d[3].x,c[ 6].y,1);          \
    dpp_shf_xor_b32(d[3].y,c[14].y,1);          \
    dpp_shf_xor_b32(d[4].x,c[ 1].y,1);          \
    dpp_shf_xor_b32(d[4].y,c[ 9].y,1);          \
    dpp_shf_xor_b32(d[5].x,c[ 5].y,1);          \
    dpp_shf_xor_b32(d[5].y,c[13].y,1);          \
    dpp_shf_xor_b32(d[6].x,c[ 3].y,1);          \
    dpp_shf_xor_b32(d[6].y,c[11].y,1);          \
    dpp_shf_xor_b32(d[7].x,c[ 7].y,1);          \
    dpp_shf_xor_b32(d[7].y,c[15].y,1);          \
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[ 0].x,spa+0,0*35,1*35);        \
    lsld_b32x2(c[ 2].x,spa+0,2*35,3*35);        \
    lsld_b32x2(c[ 4].x,spa+0,4*35,5*35);        \
    lsld_b32x2(c[ 6].x,spa+0,6*35,7*35);        \
    lsld_b32x2(c[ 8].x,spa+1,0*35,1*35);        \
    lsld_b32x2(c[10].x,spa+1,2*35,3*35);        \
    lsld_b32x2(c[12].x,spa+1,4*35,5*35);        \
    lsld_b32x2(c[14].x,spa+1,6*35,7*35);        \
    V_MAC_F32(d[0].x,sign,c[ 0].y);             \
    V_MAC_F32(d[0].y,sign,c[ 8].y);             \
    V_MAC_F32(d[1].x,sign,c[ 4].y);             \
    V_MAC_F32(d[1].y,sign,c[12].y);             \
    V_MAC_F32(d[2].x,sign,c[ 2].y);             \
    V_MAC_F32(d[2].y,sign,c[10].y);             \
    V_MAC_F32(d[3].x,sign,c[ 6].y);             \
    V_MAC_F32(d[3].y,sign,c[14].y);             \
    V_MAC_F32(d[4].x,sign,c[ 1].y);             \
    V_MAC_F32(d[4].y,sign,c[ 9].y);             \
    V_MAC_F32(d[5].x,sign,c[ 5].y);             \
    V_MAC_F32(d[5].y,sign,c[13].y);             \
    V_MAC_F32(d[6].x,sign,c[ 3].y);             \
    V_MAC_F32(d[6].y,sign,c[11].y);             \
    V_MAC_F32(d[7].x,sign,c[ 7].y);             \
    V_MAC_F32(d[7].y,sign,c[15].y);             \
    s_sync(lgkmcnt(0));                         \
    lsst_b32x2(spc,0x0,d[0].x,0x1,d[0].y);      \
    lsst_b32x2(spc,0x2,d[1].x,0x3,d[1].y);      \
    lsst_b32x2(spc,0x4,d[2].x,0x5,d[2].y);      \
    lsst_b32x2(spc,0x6,d[3].x,0x7,d[3].y);      \
    lsst_b32x2(spc,0x8,d[4].x,0x9,d[4].y);      \
    lsst_b32x2(spc,0xa,d[5].x,0xb,d[5].y);      \
    lsst_b32x2(spc,0xc,d[6].x,0xd,d[6].y);      \
    lsst_b32x2(spc,0xe,d[7].x,0xf,d[7].y);      \
    s_sync(lgkmcnt(0));                         \
    lsld_b32x2(c[ 0].y,spa+0,0*35,1*35);        \
    lsld_b32x2(c[14].y,spa+1,6*35,7*35);        \
    lsld_b32x2(c[ 2].y,spa+0,2*35,3*35);        \
    lsld_b32x2(c[12].y,spa+1,4*35,5*35);        \
    lsld_b32x2(c[ 4].y,spa+0,4*35,5*35);        \
    lsld_b32x2(c[10].y,spa+1,2*35,3*35);        \
    lsld_b32x2(c[ 6].y,spa+0,6*35,7*35);        \
    lsld_b32x2(c[ 8].y,spa+1,0*35,1*35);        \
}

#define VIFFT32(c,x,stemp){          \
    uint2* d=&c[16];                 \
    v_and_b32(v32,ic(15),x);         \
    v_cmp_u32(zero,v32,ne);          \
    v_cmov_b32(v33,nfone,fone,vcc);  \
    s_sync(lgkmcnt(6));              \
    v_mul_f32(v32,v33,c[0].y);       \
    v_add_f32(c[0].y,c[0].x,v32);    \
    v_sub_f32(c[0].x,c[0].x,v32);    \
    v_add_f32(d[0].x,c[1].x,c[15].x);\
    v_sub_f32(d[0].y,c[1].y,c[15].y);\
    v_add_f32(d[1].x,c[1].y,c[15].y);\
    v_sub_f32(d[1].y,c[1].x,c[15].x);\
    v_mul_f32(d[2].x,C5x,d[1].x);    \
    v_mul_f32(d[2].y,C5x,d[1].y);    \
    V_MAC_F32(d[2].x,C6x,d[1].y);    \
    V_MAC_F32(d[2].y,C6y,d[1].x);    \
    v_sub_f32(c[ 1].x,d[0].x,d[2].x);\
    v_add_f32(c[ 1].y,d[0].y,d[2].y);\
    v_add_f32(c[15].x,d[2].x,d[0].x);\
    v_sub_f32(c[15].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(5));              \
    v_add_f32(d[0].x,c[2].x,c[14].x);\
    v_sub_f32(d[0].y,c[2].y,c[14].y);\
    v_add_f32(d[1].x,c[2].y,c[14].y);\
    v_sub_f32(d[1].y,c[2].x,c[14].x);\
    v_mul_f32(d[2].x,C2x,d[1].x);    \
    v_mul_f32(d[2].y,C2x,d[1].y);    \
    V_MAC_F32(d[2].x,C1x,d[1].y);    \
    V_MAC_F32(d[2].y,C1y,d[1].x);    \
    v_sub_f32(c[ 2].x,d[0].x,d[2].x);\
    v_add_f32(c[ 2].y,d[0].y,d[2].y);\
    v_add_f32(c[14].x,d[2].x,d[0].x);\
    v_sub_f32(c[14].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(4));              \
    v_add_f32(d[0].x,c[3].x,c[13].x);\
    v_sub_f32(d[0].y,c[3].y,c[13].y);\
    v_add_f32(d[1].x,c[3].y,c[13].y);\
    v_sub_f32(d[1].y,c[3].x,c[13].x);\
    v_mul_f32(d[2].x,C7x,d[1].x);    \
    v_mul_f32(d[2].y,C7x,d[1].y);    \
    V_MAC_F32(d[2].x,C8x,d[1].y);    \
    V_MAC_F32(d[2].y,C8y,d[1].x);    \
    v_sub_f32(c[ 3].x,d[0].x,d[2].x);\
    v_add_f32(c[ 3].y,d[0].y,d[2].y);\
    v_add_f32(c[13].x,d[2].x,d[0].x);\
    v_sub_f32(c[13].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(3));              \
    v_add_f32(d[0].x,c[4].x,c[12].x);\
    v_sub_f32(d[0].y,c[4].y,c[12].y);\
    v_add_f32(d[1].x,c[4].y,c[12].y);\
    v_sub_f32(d[1].y,c[4].x,c[12].x);\
    v_mul_f32(d[2].x,C0x,d[1].x);    \
    v_mul_f32(d[2].y,C0x,d[1].y);    \
    V_MAC_F32(d[2].x,C0x,d[1].y);    \
    V_MAC_F32(d[2].y,C0y,d[1].x);    \
    v_sub_f32(c[ 4].x,d[0].x,d[2].x);\
    v_add_f32(c[ 4].y,d[0].y,d[2].y);\
    v_add_f32(c[12].x,d[2].x,d[0].x);\
    v_sub_f32(c[12].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(2));              \
    v_add_f32(d[0].x,c[5].x,c[11].x);\
    v_sub_f32(d[0].y,c[5].y,c[11].y);\
    v_add_f32(d[1].x,c[5].y,c[11].y);\
    v_sub_f32(d[1].y,c[5].x,c[11].x);\
    v_mul_f32(d[2].x,C8x,d[1].x);    \
    v_mul_f32(d[2].y,C8x,d[1].y);    \
    V_MAC_F32(d[2].x,C7x,d[1].y);    \
    V_MAC_F32(d[2].y,C7y,d[1].x);    \
    v_sub_f32(c[ 5].x,d[0].x,d[2].x);\
    v_add_f32(c[ 5].y,d[0].y,d[2].y);\
    v_add_f32(c[11].x,d[2].x,d[0].x);\
    v_sub_f32(c[11].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(1));              \
    v_add_f32(d[0].x,c[6].x,c[10].x);\
    v_sub_f32(d[0].y,c[6].y,c[10].y);\
    v_add_f32(d[1].x,c[6].y,c[10].y);\
    v_sub_f32(d[1].y,c[6].x,c[10].x);\
    v_mul_f32(d[2].x,C1x,d[1].x);    \
    v_mul_f32(d[2].y,C1x,d[1].y);    \
    V_MAC_F32(d[2].x,C2x,d[1].y);    \
    V_MAC_F32(d[2].y,C2y,d[1].x);    \
    v_sub_f32(c[ 6].x,d[0].x,d[2].x);\
    v_add_f32(c[ 6].y,d[0].y,d[2].y);\
    v_add_f32(c[10].x,d[2].x,d[0].x);\
    v_sub_f32(c[10].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(0));              \
    v_add_f32(d[0].x,c[7].x,c[9].x); \
    v_sub_f32(d[0].y,c[7].y,c[9].y); \
    v_add_f32(d[1].x,c[7].y,c[9].y); \
    v_sub_f32(d[1].y,c[7].x,c[9].x); \
    v_mul_f32(d[2].x,C6x,d[1].x);    \
    v_mul_f32(d[2].y,C6x,d[1].y);    \
    v_mul_f32(c[8].x, f2,c[8].x);    \
    v_mul_f32(c[8].y,nf2,c[8].y);    \
    V_MAC_F32(d[2].x,C5x,d[1].y);    \
    V_MAC_F32(d[2].y,C5y,d[1].x);    \
    v_sub_f32(c[7].x,d[0].x,d[2].x); \
    v_add_f32(c[7].y,d[0].y,d[2].y); \
    v_add_f32(c[9].x,d[2].x,d[0].x); \
    v_sub_f32(c[9].y,d[2].y,d[0].y); \
    IFFT16(c)                        \
    s_andn1exec_b64(stemp,vcc);      \
    v_exch_b32(c[ 0].y,c[15].y);     \
    v_exch_b32(c[ 8].x,c[15].x);     \
    v_exch_b32(c[ 8].y,c[ 7].y);     \
    v_exch_b32(c[ 4].x,c[ 7].x);     \
    v_exch_b32(c[ 4].y,c[11].y);     \
    v_exch_b32(c[12].x,c[11].x);     \
    v_exch_b32(c[12].y,c[ 3].y);     \
    v_exch_b32(c[ 2].x,c[ 3].x);     \
    v_exch_b32(c[ 2].y,c[13].y);     \
    v_exch_b32(c[10].x,c[13].x);     \
    v_exch_b32(c[10].y,c[ 5].y);     \
    v_exch_b32(c[ 6].x,c[ 5].x);     \
    v_exch_b32(c[ 6].y,c[ 9].y);     \
    v_exch_b32(c[14].x,c[ 9].x);     \
    v_exch_b32(c[14].y,c[ 1].y);     \
    s_mov_b64(exec,stemp);           \
}

#define IFFT16_s3x3(c){                   \
    uint2* d=&c[16];                      \
    /*==============stage0==============*/\
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);     \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);     \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);     \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);     \
    v_sub_f32(d[2].x,c[2].x,c[10].x);     \
    v_sub_f32(d[2].y,c[2].y,c[10].y);     \
    v_sub_f32(d[3].x,c[3].x,c[11].x);     \
    v_sub_f32(d[3].y,c[3].y,c[11].y);     \
    v_sub_f32(d[4].x,c[4].x,c[12].x);     \
    v_sub_f32(d[4].y,c[4].y,c[12].y);     \
    v_sub_f32(d[5].x,c[5].x,c[13].x);     \
    v_sub_f32(d[5].y,c[5].y,c[13].y);     \
    v_sub_f32(d[6].x,c[6].x,c[14].x);     \
    v_sub_f32(d[6].y,c[6].y,c[14].y);     \
    v_sub_f32(d[7].x,c[7].x,c[15].x);     \
    v_sub_f32(d[7].y,c[7].y,c[15].y);     \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);     \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);     \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);     \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);     \
    v_add_f32(c[2].x,c[2].x,c[10].x);     \
    v_add_f32(c[2].y,c[2].y,c[10].y);     \
    v_add_f32(c[3].x,c[3].x,c[11].x);     \
    v_add_f32(c[3].y,c[3].y,c[11].y);     \
    v_add_f32(c[4].x,c[4].x,c[12].x);     \
    v_add_f32(c[4].y,c[4].y,c[12].y);     \
    v_add_f32(c[5].x,c[5].x,c[13].x);     \
    v_add_f32(c[5].y,c[5].y,c[13].y);     \
    v_add_f32(c[6].x,c[6].x,c[14].x);     \
    v_add_f32(c[6].y,c[6].y,c[14].y);     \
    v_add_f32(c[7].x,c[7].x,c[15].x);     \
    v_add_f32(c[7].y,c[7].y,c[15].y);     \
    /*==============stage1==============*/\
    v_sub_f32(c[ 8].x,d[0].x,d[4].y);     \
    v_add_f32(c[15].x,d[0].x,d[4].y);     \
    v_sub_f32(c[15].y,d[0].y,d[4].x);     \
    v_sub_f32(c[ 9].x,d[1].x,d[5].y);     \
    v_add_f32(c[ 9].y,d[1].y,d[5].x);     \
    v_add_f32(c[14].x,d[1].x,d[5].y);     \
    v_sub_f32(c[14].y,d[1].y,d[5].x);     \
    v_sub_f32(c[10].x,d[2].x,d[6].y);     \
    v_add_f32(c[10].y,d[2].y,d[6].x);     \
    v_add_f32(c[12].x,d[2].x,d[6].y);     \
    v_sub_f32(c[12].y,d[2].y,d[6].x);     \
    v_sub_f32(c[11].x,d[3].x,d[7].y);     \
    v_add_f32(c[11].y,d[3].y,d[7].x);     \
    v_add_f32(c[13].x,d[3].x,d[7].y);     \
    v_sub_f32(c[13].y,d[3].y,d[7].x);     \
    v_add_f32(c[ 0].x,c[0].x,c[4].x);     \
    v_add_f32(c[ 0].y,c[0].y,c[4].y);     \
    v_add_f32(c[ 1].x,c[1].x,c[5].x);     \
    v_add_f32(c[ 1].y,c[1].y,c[5].y);     \
    v_add_f32(c[ 2].x,c[2].x,c[6].x);     \
    v_add_f32(c[ 2].y,c[2].y,c[6].y);     \
    v_add_f32(c[ 3].x,c[3].x,c[7].x);     \
    v_add_f32(c[ 3].y,c[3].y,c[7].y);     \
	/*==============stage2==============*/\
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(d[6].x,c[ 1].x,c[ 3].x);    \
    v_add_f32(d[6].y,c[ 1].y,c[ 3].y);    \
    v_sub_f32(d[2].x,c[10].x,c[10].y);    \
    v_sub_f32(d[3].x,c[11].x,c[11].y);    \
    v_add_f32(d[3].y,c[11].x,c[11].y);    \
    v_add_f32(d[4].x,c[12].y,c[12].x);    \
    v_sub_f32(d[4].y,c[12].y,c[12].x);    \
    v_add_f32(d[5].x,c[13].y,c[13].x);    \
    v_sub_f32(d[5].y,c[13].y,c[13].x);    \
    V_MAC_F32(c[15].x,C0x,d[4].x);        \
    V_MAC_F32(c[15].y,C0x,d[4].y);        \
    V_MAC_F32(c[14].x,C0x,d[5].x);        \
    V_MAC_F32(c[14].y,C0x,d[5].y);        \
    V_MAC_F32(c[ 8].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);        \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);        \
    /*==============stage3==============*/\
    v_fma_f32(d[7].x,C3x,c[14].x,c[14].y);\
    v_add_f32(c[0].x,c[0].x,d[6].x);      \
    v_add_f32(c[0].y,c[0].y,d[6].y);      \
    V_MAC_F32(c[14].x,C3y,c[14].y);       \
    V_MAC_F32(c[ 9].y,C3y,c[ 9].x);       \
    V_MAC_F32(c[15].x,C1x,d[ 7].x);       \
    V_MAC_F32(c[15].y,C1y,c[14].x);       \
    V_MAC_F32(c[ 8].x,C1y,c[ 9].y);       \
}

#define VIFFT32_s3x3(c,x,stemp){     \
    uint2* d=&c[16];                 \
    v_and_b32(v32,ic(15),x);         \
    v_cmp_u32(zero,v32,ne);          \
    v_cmov_b32(v33,nfone,fone,vcc);  \
    s_sync(lgkmcnt(6));              \
    v_mul_f32(v32,v33,c[0].y);       \
    v_add_f32(c[0].y,c[0].x,v32);    \
    v_sub_f32(c[0].x,c[0].x,v32);    \
    v_add_f32(d[0].x,c[1].x,c[15].x);\
    v_sub_f32(d[0].y,c[1].y,c[15].y);\
    v_add_f32(d[1].x,c[1].y,c[15].y);\
    v_sub_f32(d[1].y,c[1].x,c[15].x);\
    v_mul_f32(d[2].x,C5x,d[1].x);    \
    v_mul_f32(d[2].y,C5x,d[1].y);    \
    V_MAC_F32(d[2].x,C6x,d[1].y);    \
    V_MAC_F32(d[2].y,C6y,d[1].x);    \
    v_sub_f32(c[ 1].x,d[0].x,d[2].x);\
    v_add_f32(c[ 1].y,d[0].y,d[2].y);\
    v_add_f32(c[15].x,d[2].x,d[0].x);\
    v_sub_f32(c[15].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(5));              \
    v_add_f32(d[0].x,c[2].x,c[14].x);\
    v_sub_f32(d[0].y,c[2].y,c[14].y);\
    v_add_f32(d[1].x,c[2].y,c[14].y);\
    v_sub_f32(d[1].y,c[2].x,c[14].x);\
    v_mul_f32(d[2].x,C2x,d[1].x);    \
    v_mul_f32(d[2].y,C2x,d[1].y);    \
    V_MAC_F32(d[2].x,C1x,d[1].y);    \
    V_MAC_F32(d[2].y,C1y,d[1].x);    \
    v_sub_f32(c[ 2].x,d[0].x,d[2].x);\
    v_add_f32(c[ 2].y,d[0].y,d[2].y);\
    v_add_f32(c[14].x,d[2].x,d[0].x);\
    v_sub_f32(c[14].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(4));              \
    v_add_f32(d[0].x,c[3].x,c[13].x);\
    v_sub_f32(d[0].y,c[3].y,c[13].y);\
    v_add_f32(d[1].x,c[3].y,c[13].y);\
    v_sub_f32(d[1].y,c[3].x,c[13].x);\
    v_mul_f32(d[2].x,C7x,d[1].x);    \
    v_mul_f32(d[2].y,C7x,d[1].y);    \
    V_MAC_F32(d[2].x,C8x,d[1].y);    \
    V_MAC_F32(d[2].y,C8y,d[1].x);    \
    v_sub_f32(c[ 3].x,d[0].x,d[2].x);\
    v_add_f32(c[ 3].y,d[0].y,d[2].y);\
    v_add_f32(c[13].x,d[2].x,d[0].x);\
    v_sub_f32(c[13].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(3));              \
    v_add_f32(d[0].x,c[4].x,c[12].x);\
    v_sub_f32(d[0].y,c[4].y,c[12].y);\
    v_add_f32(d[1].x,c[4].y,c[12].y);\
    v_sub_f32(d[1].y,c[4].x,c[12].x);\
    v_mul_f32(d[2].x,C0x,d[1].x);    \
    v_mul_f32(d[2].y,C0x,d[1].y);    \
    V_MAC_F32(d[2].x,C0x,d[1].y);    \
    V_MAC_F32(d[2].y,C0y,d[1].x);    \
    v_sub_f32(c[ 4].x,d[0].x,d[2].x);\
    v_add_f32(c[ 4].y,d[0].y,d[2].y);\
    v_add_f32(c[12].x,d[2].x,d[0].x);\
    v_sub_f32(c[12].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(2));              \
    v_add_f32(d[0].x,c[5].x,c[11].x);\
    v_sub_f32(d[0].y,c[5].y,c[11].y);\
    v_add_f32(d[1].x,c[5].y,c[11].y);\
    v_sub_f32(d[1].y,c[5].x,c[11].x);\
    v_mul_f32(d[2].x,C8x,d[1].x);    \
    v_mul_f32(d[2].y,C8x,d[1].y);    \
    V_MAC_F32(d[2].x,C7x,d[1].y);    \
    V_MAC_F32(d[2].y,C7y,d[1].x);    \
    v_sub_f32(c[ 5].x,d[0].x,d[2].x);\
    v_add_f32(c[ 5].y,d[0].y,d[2].y);\
    v_add_f32(c[11].x,d[2].x,d[0].x);\
    v_sub_f32(c[11].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(1));              \
    v_add_f32(d[0].x,c[6].x,c[10].x);\
    v_sub_f32(d[0].y,c[6].y,c[10].y);\
    v_add_f32(d[1].x,c[6].y,c[10].y);\
    v_sub_f32(d[1].y,c[6].x,c[10].x);\
    v_mul_f32(d[2].x,C1x,d[1].x);    \
    v_mul_f32(d[2].y,C1x,d[1].y);    \
    V_MAC_F32(d[2].x,C2x,d[1].y);    \
    V_MAC_F32(d[2].y,C2y,d[1].x);    \
    v_sub_f32(c[ 6].x,d[0].x,d[2].x);\
    v_add_f32(c[ 6].y,d[0].y,d[2].y);\
    v_add_f32(c[10].x,d[2].x,d[0].x);\
    v_sub_f32(c[10].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(0));              \
    v_add_f32(d[0].x,c[7].x,c[9].x); \
    v_sub_f32(d[0].y,c[7].y,c[9].y); \
    v_add_f32(d[1].x,c[7].y,c[9].y); \
    v_sub_f32(d[1].y,c[7].x,c[9].x); \
    v_mul_f32(d[2].x,C6x,d[1].x);    \
    v_mul_f32(d[2].y,C6x,d[1].y);    \
    v_mul_f32(c[8].x, f2,c[8].x);    \
    v_mul_f32(c[8].y,nf2,c[8].y);    \
    V_MAC_F32(d[2].x,C5x,d[1].y);    \
    V_MAC_F32(d[2].y,C5y,d[1].x);    \
    v_sub_f32(c[7].x,d[0].x,d[2].x); \
    v_add_f32(c[7].y,d[0].y,d[2].y); \
    v_add_f32(c[9].x,d[2].x,d[0].x); \
    v_sub_f32(c[9].y,d[2].y,d[0].y); \
    IFFT16_s3x3(c)                   \
    s_andn1exec_b64(stemp,vcc);      \
    v_exch_b32(c[0].y,c[15].y);      \
    v_exch_b32(c[8].x,c[15].x);      \
    s_mov_b64(exec,stemp);           \
}

#define IFFT16_s5x5(c){                    \
    uint2* d=&c[16];                       \
    /*==============stage0===============*/\
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);      \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);      \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);      \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);      \
    v_sub_f32(d[2].x,c[2].x,c[10].x);      \
    v_sub_f32(d[2].y,c[2].y,c[10].y);      \
    v_sub_f32(d[3].x,c[3].x,c[11].x);      \
    v_sub_f32(d[3].y,c[3].y,c[11].y);      \
    v_sub_f32(d[4].x,c[4].x,c[12].x);      \
    v_sub_f32(d[4].y,c[4].y,c[12].y);      \
    v_sub_f32(d[5].x,c[5].x,c[13].x);      \
    v_sub_f32(d[5].y,c[5].y,c[13].y);      \
    v_sub_f32(d[6].x,c[6].x,c[14].x);      \
    v_sub_f32(d[6].y,c[6].y,c[14].y);      \
    v_sub_f32(d[7].x,c[7].x,c[15].x);      \
    v_sub_f32(d[7].y,c[7].y,c[15].y);      \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);      \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);      \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);      \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);      \
    v_add_f32(c[2].x,c[2].x,c[10].x);      \
    v_add_f32(c[2].y,c[2].y,c[10].y);      \
    v_add_f32(c[3].x,c[3].x,c[11].x);      \
    v_add_f32(c[3].y,c[3].y,c[11].y);      \
    v_add_f32(c[4].x,c[4].x,c[12].x);      \
    v_add_f32(c[4].y,c[4].y,c[12].y);      \
    v_add_f32(c[5].x,c[5].x,c[13].x);      \
    v_add_f32(c[5].y,c[5].y,c[13].y);      \
    v_add_f32(c[6].x,c[6].x,c[14].x);      \
    v_add_f32(c[6].y,c[6].y,c[14].y);      \
    v_add_f32(c[7].x,c[7].x,c[15].x);      \
    v_add_f32(c[7].y,c[7].y,c[15].y);      \
    /*==============stage1===============*/\
    v_sub_f32(c[ 8].x,d[0].x,d[4].y);      \
    v_add_f32(c[ 8].y,d[0].y,d[4].x);      \
    v_add_f32(c[15].x,d[0].x,d[4].y);      \
    v_sub_f32(c[15].y,d[0].y,d[4].x);      \
    v_sub_f32(c[ 9].x,d[1].x,d[5].y);      \
    v_add_f32(c[ 9].y,d[1].y,d[5].x);      \
    v_add_f32(c[14].x,d[1].x,d[5].y);      \
    v_sub_f32(c[14].y,d[1].y,d[5].x);      \
    v_sub_f32(c[10].x,d[2].x,d[6].y);      \
    v_add_f32(c[10].y,d[2].y,d[6].x);      \
    v_add_f32(c[12].x,d[2].x,d[6].y);      \
    v_sub_f32(c[12].y,d[2].y,d[6].x);      \
    v_sub_f32(c[11].x,d[3].x,d[7].y);      \
    v_add_f32(c[11].y,d[3].y,d[7].x);      \
    v_add_f32(c[13].x,d[3].x,d[7].y);      \
    v_sub_f32(c[13].y,d[3].y,d[7].x);      \
    v_sub_f32(d[0].x,c[0].x,c[4].x);       \
    v_sub_f32(d[0].y,c[0].y,c[4].y);       \
    v_sub_f32(d[1].x,c[1].x,c[5].x);       \
    v_sub_f32(d[1].y,c[1].y,c[5].y);       \
    v_sub_f32(d[2].x,c[2].x,c[6].x);       \
    v_sub_f32(d[2].y,c[2].y,c[6].y);       \
    v_sub_f32(d[3].x,c[3].x,c[7].x);       \
    v_sub_f32(d[3].y,c[3].y,c[7].y);       \
    v_add_f32(c[0].x,c[0].x,c[4].x);       \
    v_add_f32(c[0].y,c[0].y,c[4].y);       \
    v_add_f32(c[1].x,c[1].x,c[5].x);       \
    v_add_f32(c[1].y,c[1].y,c[5].y);       \
    v_add_f32(c[2].x,c[2].x,c[6].x);       \
    v_add_f32(c[2].y,c[2].y,c[6].y);       \
    v_add_f32(c[3].x,c[3].x,c[7].x);       \
    v_add_f32(c[3].y,c[3].y,c[7].y);       \
    /*==============stage2===============*/\
    v_sub_f32(c[4].x,d[ 0].x,d[ 2].y);     \
    v_add_f32(c[7].x,d[ 0].x,d[ 2].y);     \
    v_sub_f32(c[7].y,d[ 0].y,d[ 2].x);     \
    v_sub_f32(c[5].x,d[ 1].x,d[ 3].y);     \
    v_add_f32(c[5].y,d[ 1].y,d[ 3].x);     \
    v_add_f32(c[6].x,d[ 1].x,d[ 3].y);     \
    v_sub_f32(c[6].y,d[ 1].y,d[ 3].x);     \
    v_add_f32(c[0].x,c[ 0].x,c[ 2].x);     \
    v_add_f32(c[0].y,c[ 0].y,c[ 2].y);     \
    v_add_f32(d[6].x,c[ 1].x,c[ 3].x);     \
    v_add_f32(d[6].y,c[ 1].y,c[ 3].y);     \
    v_sub_f32(d[2].x,c[10].x,c[10].y);     \
    v_add_f32(d[2].y,c[10].x,c[10].y);     \
    v_sub_f32(d[3].x,c[11].x,c[11].y);     \
    v_add_f32(d[3].y,c[11].x,c[11].y);     \
    v_add_f32(d[4].x,c[12].y,c[12].x);     \
    v_sub_f32(d[4].y,c[12].y,c[12].x);     \
    v_add_f32(d[5].x,c[13].y,c[13].x);     \
    v_sub_f32(d[5].y,c[13].y,c[13].x);     \
    V_MAC_F32(c[15].x,C0x,d[4].x);         \
    V_MAC_F32(c[15].y,C0x,d[4].y);         \
    V_MAC_F32(c[14].x,C0x,d[5].x);         \
    V_MAC_F32(c[14].y,C0x,d[5].y);         \
    V_MAC_F32(c[ 8].x,C0x,d[2].x);         \
    V_MAC_F32(c[ 8].y,C0x,d[2].y);         \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);         \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);         \
    /*==============stage3===============*/\
    v_add_f32(c[0].x,c[0].x,d[6].x);       \
    v_add_f32(c[0].y,c[0].y,d[6].y);       \
    v_sub_f32(d[2].x,c[5].x,c[5].y);       \
    v_add_f32(d[2].y,c[5].x,c[5].y);       \
    v_add_f32(d[3].x,c[6].y,c[6].x);       \
    v_sub_f32(d[3].y,c[6].y,c[6].x);       \
    v_fma_f32(d[ 4].x,C3y,c[ 9].x,c[ 9].y);\
    v_fma_f32(d[ 7].x,C3x,c[14].x,c[14].y);\
    V_MAC_F32(c[ 9].x,C3x,c[ 9].y);        \
    V_MAC_F32(c[14].x,C3y,c[14].y);        \
    V_MAC_F32(c[ 7].x,C0x,d[ 3].x);        \
    V_MAC_F32(c[ 7].y,C0x,d[ 3].y);        \
    V_MAC_F32(c[15].x,C1x,d[ 7].x);        \
    V_MAC_F32(c[15].y,C1y,c[14].x);        \
    V_MAC_F32(c[ 4].x,C0x,d[ 2].x);        \
    V_MAC_F32(c[ 8].x,C1y,d[ 4].x);        \
    V_MAC_F32(c[ 8].y,C1x,c[ 9].x);        \
}

#define VIFFT32_s5x5(c,x,stemp){     \
    uint2* d=&c[16];                 \
    v_and_b32(v32,ic(15),x);         \
    v_cmp_u32(zero,v32,ne);          \
    v_cmov_b32(v33,nfone,fone,vcc);  \
    s_sync(lgkmcnt(6));              \
    v_mul_f32(v32,v33,c[0].y);       \
    v_add_f32(c[0].y,c[0].x,v32);    \
    v_sub_f32(c[0].x,c[0].x,v32);    \
    v_add_f32(d[0].x,c[1].x,c[15].x);\
    v_sub_f32(d[0].y,c[1].y,c[15].y);\
    v_add_f32(d[1].x,c[1].y,c[15].y);\
    v_sub_f32(d[1].y,c[1].x,c[15].x);\
    v_mul_f32(d[2].x,C5x,d[1].x);    \
    v_mul_f32(d[2].y,C5x,d[1].y);    \
    V_MAC_F32(d[2].x,C6x,d[1].y);    \
    V_MAC_F32(d[2].y,C6y,d[1].x);    \
    v_sub_f32(c[ 1].x,d[0].x,d[2].x);\
    v_add_f32(c[ 1].y,d[0].y,d[2].y);\
    v_add_f32(c[15].x,d[2].x,d[0].x);\
    v_sub_f32(c[15].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(5));              \
    v_add_f32(d[0].x,c[2].x,c[14].x);\
    v_sub_f32(d[0].y,c[2].y,c[14].y);\
    v_add_f32(d[1].x,c[2].y,c[14].y);\
    v_sub_f32(d[1].y,c[2].x,c[14].x);\
    v_mul_f32(d[2].x,C2x,d[1].x);    \
    v_mul_f32(d[2].y,C2x,d[1].y);    \
    V_MAC_F32(d[2].x,C1x,d[1].y);    \
    V_MAC_F32(d[2].y,C1y,d[1].x);    \
    v_sub_f32(c[ 2].x,d[0].x,d[2].x);\
    v_add_f32(c[ 2].y,d[0].y,d[2].y);\
    v_add_f32(c[14].x,d[2].x,d[0].x);\
    v_sub_f32(c[14].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(4));              \
    v_add_f32(d[0].x,c[3].x,c[13].x);\
    v_sub_f32(d[0].y,c[3].y,c[13].y);\
    v_add_f32(d[1].x,c[3].y,c[13].y);\
    v_sub_f32(d[1].y,c[3].x,c[13].x);\
    v_mul_f32(d[2].x,C7x,d[1].x);    \
    v_mul_f32(d[2].y,C7x,d[1].y);    \
    V_MAC_F32(d[2].x,C8x,d[1].y);    \
    V_MAC_F32(d[2].y,C8y,d[1].x);    \
    v_sub_f32(c[ 3].x,d[0].x,d[2].x);\
    v_add_f32(c[ 3].y,d[0].y,d[2].y);\
    v_add_f32(c[13].x,d[2].x,d[0].x);\
    v_sub_f32(c[13].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(3));              \
    v_add_f32(d[0].x,c[4].x,c[12].x);\
    v_sub_f32(d[0].y,c[4].y,c[12].y);\
    v_add_f32(d[1].x,c[4].y,c[12].y);\
    v_sub_f32(d[1].y,c[4].x,c[12].x);\
    v_mul_f32(d[2].x,C0x,d[1].x);    \
    v_mul_f32(d[2].y,C0x,d[1].y);    \
    V_MAC_F32(d[2].x,C0x,d[1].y);    \
    V_MAC_F32(d[2].y,C0y,d[1].x);    \
    v_sub_f32(c[ 4].x,d[0].x,d[2].x);\
    v_add_f32(c[ 4].y,d[0].y,d[2].y);\
    v_add_f32(c[12].x,d[2].x,d[0].x);\
    v_sub_f32(c[12].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(2));              \
    v_add_f32(d[0].x,c[5].x,c[11].x);\
    v_sub_f32(d[0].y,c[5].y,c[11].y);\
    v_add_f32(d[1].x,c[5].y,c[11].y);\
    v_sub_f32(d[1].y,c[5].x,c[11].x);\
    v_mul_f32(d[2].x,C8x,d[1].x);    \
    v_mul_f32(d[2].y,C8x,d[1].y);    \
    V_MAC_F32(d[2].x,C7x,d[1].y);    \
    V_MAC_F32(d[2].y,C7y,d[1].x);    \
    v_sub_f32(c[ 5].x,d[0].x,d[2].x);\
    v_add_f32(c[ 5].y,d[0].y,d[2].y);\
    v_add_f32(c[11].x,d[2].x,d[0].x);\
    v_sub_f32(c[11].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(1));              \
    v_add_f32(d[0].x,c[6].x,c[10].x);\
    v_sub_f32(d[0].y,c[6].y,c[10].y);\
    v_add_f32(d[1].x,c[6].y,c[10].y);\
    v_sub_f32(d[1].y,c[6].x,c[10].x);\
    v_mul_f32(d[2].x,C1x,d[1].x);    \
    v_mul_f32(d[2].y,C1x,d[1].y);    \
    V_MAC_F32(d[2].x,C2x,d[1].y);    \
    V_MAC_F32(d[2].y,C2y,d[1].x);    \
    v_sub_f32(c[ 6].x,d[0].x,d[2].x);\
    v_add_f32(c[ 6].y,d[0].y,d[2].y);\
    v_add_f32(c[10].x,d[2].x,d[0].x);\
    v_sub_f32(c[10].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(0));              \
    v_add_f32(d[0].x,c[7].x,c[9].x); \
    v_sub_f32(d[0].y,c[7].y,c[9].y); \
    v_add_f32(d[1].x,c[7].y,c[9].y); \
    v_sub_f32(d[1].y,c[7].x,c[9].x); \
    v_mul_f32(d[2].x,C6x,d[1].x);    \
    v_mul_f32(d[2].y,C6x,d[1].y);    \
    v_mul_f32(c[8].x, f2,c[8].x);    \
    v_mul_f32(c[8].y,nf2,c[8].y);    \
    V_MAC_F32(d[2].x,C5x,d[1].y);    \
    V_MAC_F32(d[2].y,C5y,d[1].x);    \
    v_sub_f32(c[7].x,d[0].x,d[2].x); \
    v_add_f32(c[7].y,d[0].y,d[2].y); \
    v_add_f32(c[9].x,d[2].x,d[0].x); \
    v_sub_f32(c[9].y,d[2].y,d[0].y); \
    IFFT16_s5x5(c)                   \
    s_andn1exec_b64(stemp,vcc);      \
    v_exch_b32(c[0].y,c[15].y);      \
    v_exch_b32(c[8].x,c[15].x);      \
    v_exch_b32(c[8].y,c[ 7].y);      \
    v_exch_b32(c[4].x,c[ 7].x);      \
    s_mov_b64(exec,stemp);           \
}

#define IFFT16_s7x7(c){                   \
    uint2* d=&c[16];                      \
    /*==============stage0==============*/\
    v_sub_f32(d[0].x,c[0].x,c[ 8].x);     \
    v_sub_f32(d[0].y,c[0].y,c[ 8].y);     \
    v_sub_f32(d[1].x,c[1].x,c[ 9].x);     \
    v_sub_f32(d[1].y,c[1].y,c[ 9].y);     \
    v_sub_f32(d[2].x,c[2].x,c[10].x);     \
    v_sub_f32(d[2].y,c[2].y,c[10].y);     \
    v_sub_f32(d[3].x,c[3].x,c[11].x);     \
    v_sub_f32(d[3].y,c[3].y,c[11].y);     \
    v_sub_f32(d[4].x,c[4].x,c[12].x);     \
    v_sub_f32(d[4].y,c[4].y,c[12].y);     \
    v_sub_f32(d[5].x,c[5].x,c[13].x);     \
    v_sub_f32(d[5].y,c[5].y,c[13].y);     \
    v_sub_f32(d[6].x,c[6].x,c[14].x);     \
    v_sub_f32(d[6].y,c[6].y,c[14].y);     \
    v_sub_f32(d[7].x,c[7].x,c[15].x);     \
    v_sub_f32(d[7].y,c[7].y,c[15].y);     \
    v_add_f32(c[0].x,c[0].x,c[ 8].x);     \
    v_add_f32(c[0].y,c[0].y,c[ 8].y);     \
    v_add_f32(c[1].x,c[1].x,c[ 9].x);     \
    v_add_f32(c[1].y,c[1].y,c[ 9].y);     \
    v_add_f32(c[2].x,c[2].x,c[10].x);     \
    v_add_f32(c[2].y,c[2].y,c[10].y);     \
    v_add_f32(c[3].x,c[3].x,c[11].x);     \
    v_add_f32(c[3].y,c[3].y,c[11].y);     \
    v_add_f32(c[4].x,c[4].x,c[12].x);     \
    v_add_f32(c[4].y,c[4].y,c[12].y);     \
    v_add_f32(c[5].x,c[5].x,c[13].x);     \
    v_add_f32(c[5].y,c[5].y,c[13].y);     \
    v_add_f32(c[6].x,c[6].x,c[14].x);     \
    v_add_f32(c[6].y,c[6].y,c[14].y);     \
    v_add_f32(c[7].x,c[7].x,c[15].x);     \
    v_add_f32(c[7].y,c[7].y,c[15].y);     \
    /*==============stage1==============*/\
    v_sub_f32(c[ 8].x,d[0].x,d[4].y);     \
    v_add_f32(c[ 8].y,d[0].y,d[4].x);     \
    v_add_f32(c[12].x,d[0].x,d[4].y);     \
    v_sub_f32(c[12].y,d[0].y,d[4].x);     \
    v_sub_f32(c[ 9].x,d[1].x,d[5].y);     \
    v_add_f32(c[ 9].y,d[1].y,d[5].x);     \
    v_add_f32(c[13].x,d[1].x,d[5].y);     \
    v_sub_f32(c[13].y,d[1].y,d[5].x);     \
    v_sub_f32(c[10].x,d[2].x,d[6].y);     \
    v_add_f32(c[10].y,d[2].y,d[6].x);     \
    v_add_f32(c[14].x,d[2].x,d[6].y);     \
    v_sub_f32(c[14].y,d[2].y,d[6].x);     \
    v_sub_f32(c[11].x,d[3].x,d[7].y);     \
    v_add_f32(c[11].y,d[3].y,d[7].x);     \
    v_add_f32(c[15].x,d[3].x,d[7].y);     \
    v_sub_f32(c[15].y,d[3].y,d[7].x);     \
    v_sub_f32(d[0].x,c[0].x,c[4].x);      \
    v_sub_f32(d[0].y,c[0].y,c[4].y);      \
    v_sub_f32(d[1].x,c[1].x,c[5].x);      \
    v_sub_f32(d[1].y,c[1].y,c[5].y);      \
    v_sub_f32(d[2].x,c[2].x,c[6].x);      \
    v_sub_f32(d[2].y,c[2].y,c[6].y);      \
    v_sub_f32(d[3].x,c[3].x,c[7].x);      \
    v_sub_f32(d[3].y,c[3].y,c[7].y);      \
    v_add_f32(c[0].x,c[0].x,c[4].x);      \
    v_add_f32(c[0].y,c[0].y,c[4].y);      \
    v_add_f32(c[1].x,c[1].x,c[5].x);      \
    v_add_f32(c[1].y,c[1].y,c[5].y);      \
    v_add_f32(c[2].x,c[2].x,c[6].x);      \
    v_add_f32(c[2].y,c[2].y,c[6].y);      \
    v_add_f32(c[3].x,c[3].x,c[7].x);      \
    v_add_f32(c[3].y,c[3].y,c[7].y);      \
    /*==============stage2==============*/\
    v_sub_f32(c[4].x,d[0].x,d[2].y);      \
    v_add_f32(c[4].y,d[0].y,d[2].x);      \
    v_add_f32(c[6].x,d[0].x,d[2].y);      \
    v_sub_f32(c[6].y,d[0].y,d[2].x);      \
    v_sub_f32(c[5].x,d[1].x,d[3].y);      \
    v_add_f32(c[5].y,d[1].y,d[3].x);      \
    v_add_f32(c[7].x,d[1].x,d[3].y);      \
    v_sub_f32(c[7].y,d[1].y,d[3].x);      \
    v_add_f32(c[0].x,c[0].x,c[2].x);      \
    v_add_f32(c[0].y,c[0].y,c[2].y);      \
    v_add_f32(d[6].x,c[ 1].x,c[ 3].x);    \
    v_add_f32(d[6].y,c[ 1].y,c[ 3].y);    \
    v_sub_f32(d[2].x,c[10].x,c[10].y);    \
    v_add_f32(d[2].y,c[10].x,c[10].y);    \
    v_sub_f32(d[3].x,c[11].x,c[11].y);    \
    v_add_f32(d[3].y,c[11].x,c[11].y);    \
    v_add_f32(d[4].x,c[14].y,c[14].x);    \
    v_sub_f32(d[4].y,c[14].y,c[14].x);    \
    v_add_f32(d[5].x,c[15].y,c[15].x);    \
    v_sub_f32(d[5].y,c[15].y,c[15].x);    \
    v_fma_f32(c[10].x,C0y,d[2].x,c[ 8].x);\
    v_fma_f32(c[10].y,C0y,d[2].y,c[ 8].y);\
    v_fma_f32(c[11].x,C0y,d[3].x,c[ 9].x);\
    v_fma_f32(c[11].y,C0y,d[3].y,c[ 9].y);\
    v_fma_f32(c[14].x,C0x,d[4].x,c[12].x);\
    v_fma_f32(c[14].y,C0x,d[4].y,c[12].y);\
    v_fma_f32(c[15].x,C0x,d[5].x,c[13].x);\
    v_fma_f32(c[15].y,C0x,d[5].y,c[13].y);\
    V_MAC_F32(c[ 8].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 8].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 9].x,C0x,d[3].x);        \
    V_MAC_F32(c[ 9].y,C0x,d[3].y);        \
    V_MAC_F32(c[12].x,C0y,d[4].x);        \
    V_MAC_F32(c[13].x,C0y,d[5].x);        \
    V_MAC_F32(c[13].y,C0y,d[5].y);        \
    /*==============stage3==============*/\
    v_add_f32(c[0].x,c[0].x,d[6].x);      \
    v_add_f32(c[0].y,c[0].y,d[6].y);      \
    v_sub_f32(d[2].x,c[5].x,c[5].y);      \
    v_add_f32(d[2].y,c[5].x,c[5].y);      \
    v_add_f32(d[3].x,c[7].y,c[7].x);      \
    v_sub_f32(d[3].y,c[7].y,c[7].x);      \
    v_fma_f32(d[4].x,C3y,c[ 9].x,c[ 9].y);\
    v_fma_f32(d[4].y,C3x,c[ 9].y,c[ 9].x);\
    v_fma_f32(d[5].x,C4x,c[11].x,c[11].y);\
    v_fma_f32(d[5].y,C4y,c[11].y,c[11].x);\
    v_fma_f32(d[6].x,C4y,c[13].x,c[13].y);\
    v_fma_f32(d[7].x,C3x,c[15].x,c[15].y);\
    v_fma_f32(d[7].y,C3y,c[15].y,c[15].x);\
    v_fma_f32(c[ 7].x,C0x,d[3].x,c[ 6].x);\
    v_fma_f32(c[ 7].y,C0x,d[3].y,c[ 6].y);\
    v_fma_f32(c[11].x,C2x,d[5].x,c[10].x);\
    v_fma_f32(c[11].y,C2y,d[5].y,c[10].y);\
    v_fma_f32(c[15].x,C1x,d[7].x,c[14].x);\
    v_fma_f32(c[15].y,C1y,d[7].y,c[14].y);\
    V_MAC_F32(c[ 4].x,C0x,d[2].x);        \
    V_MAC_F32(c[ 4].y,C0x,d[2].y);        \
    V_MAC_F32(c[ 8].x,C1y,d[4].x);        \
    V_MAC_F32(c[ 8].y,C1x,d[4].y);        \
    V_MAC_F32(c[12].x,C2y,d[6].x);        \
}

#define VIFFT32_s7x7(c,x,stemp){     \
    uint2* d=&c[16];                 \
    v_and_b32(v32,ic(15),x);         \
    v_cmp_u32(zero,v32,ne);          \
    v_cmov_b32(v33,nfone,fone,vcc);  \
    s_sync(lgkmcnt(6));              \
    v_mul_f32(v32,v33,c[0].y);       \
    v_add_f32(c[0].y,c[0].x,v32);    \
    v_sub_f32(c[0].x,c[0].x,v32);    \
    v_add_f32(d[0].x,c[1].x,c[15].x);\
    v_sub_f32(d[0].y,c[1].y,c[15].y);\
    v_add_f32(d[1].x,c[1].y,c[15].y);\
    v_sub_f32(d[1].y,c[1].x,c[15].x);\
    v_mul_f32(d[2].x,C5x,d[1].x);    \
    v_mul_f32(d[2].y,C5x,d[1].y);    \
    V_MAC_F32(d[2].x,C6x,d[1].y);    \
    V_MAC_F32(d[2].y,C6y,d[1].x);    \
    v_sub_f32(c[ 1].x,d[0].x,d[2].x);\
    v_add_f32(c[ 1].y,d[0].y,d[2].y);\
    v_add_f32(c[15].x,d[2].x,d[0].x);\
    v_sub_f32(c[15].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(5));              \
    v_add_f32(d[0].x,c[2].x,c[14].x);\
    v_sub_f32(d[0].y,c[2].y,c[14].y);\
    v_add_f32(d[1].x,c[2].y,c[14].y);\
    v_sub_f32(d[1].y,c[2].x,c[14].x);\
    v_mul_f32(d[2].x,C2x,d[1].x);    \
    v_mul_f32(d[2].y,C2x,d[1].y);    \
    V_MAC_F32(d[2].x,C1x,d[1].y);    \
    V_MAC_F32(d[2].y,C1y,d[1].x);    \
    v_sub_f32(c[ 2].x,d[0].x,d[2].x);\
    v_add_f32(c[ 2].y,d[0].y,d[2].y);\
    v_add_f32(c[14].x,d[2].x,d[0].x);\
    v_sub_f32(c[14].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(4));              \
    v_add_f32(d[0].x,c[3].x,c[13].x);\
    v_sub_f32(d[0].y,c[3].y,c[13].y);\
    v_add_f32(d[1].x,c[3].y,c[13].y);\
    v_sub_f32(d[1].y,c[3].x,c[13].x);\
    v_mul_f32(d[2].x,C7x,d[1].x);    \
    v_mul_f32(d[2].y,C7x,d[1].y);    \
    V_MAC_F32(d[2].x,C8x,d[1].y);    \
    V_MAC_F32(d[2].y,C8y,d[1].x);    \
    v_sub_f32(c[ 3].x,d[0].x,d[2].x);\
    v_add_f32(c[ 3].y,d[0].y,d[2].y);\
    v_add_f32(c[13].x,d[2].x,d[0].x);\
    v_sub_f32(c[13].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(3));              \
    v_add_f32(d[0].x,c[4].x,c[12].x);\
    v_sub_f32(d[0].y,c[4].y,c[12].y);\
    v_add_f32(d[1].x,c[4].y,c[12].y);\
    v_sub_f32(d[1].y,c[4].x,c[12].x);\
    v_mul_f32(d[2].x,C0x,d[1].x);    \
    v_mul_f32(d[2].y,C0x,d[1].y);    \
    V_MAC_F32(d[2].x,C0x,d[1].y);    \
    V_MAC_F32(d[2].y,C0y,d[1].x);    \
    v_sub_f32(c[ 4].x,d[0].x,d[2].x);\
    v_add_f32(c[ 4].y,d[0].y,d[2].y);\
    v_add_f32(c[12].x,d[2].x,d[0].x);\
    v_sub_f32(c[12].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(2));              \
    v_add_f32(d[0].x,c[5].x,c[11].x);\
    v_sub_f32(d[0].y,c[5].y,c[11].y);\
    v_add_f32(d[1].x,c[5].y,c[11].y);\
    v_sub_f32(d[1].y,c[5].x,c[11].x);\
    v_mul_f32(d[2].x,C8x,d[1].x);    \
    v_mul_f32(d[2].y,C8x,d[1].y);    \
    V_MAC_F32(d[2].x,C7x,d[1].y);    \
    V_MAC_F32(d[2].y,C7y,d[1].x);    \
    v_sub_f32(c[ 5].x,d[0].x,d[2].x);\
    v_add_f32(c[ 5].y,d[0].y,d[2].y);\
    v_add_f32(c[11].x,d[2].x,d[0].x);\
    v_sub_f32(c[11].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(1));              \
    v_add_f32(d[0].x,c[6].x,c[10].x);\
    v_sub_f32(d[0].y,c[6].y,c[10].y);\
    v_add_f32(d[1].x,c[6].y,c[10].y);\
    v_sub_f32(d[1].y,c[6].x,c[10].x);\
    v_mul_f32(d[2].x,C1x,d[1].x);    \
    v_mul_f32(d[2].y,C1x,d[1].y);    \
    V_MAC_F32(d[2].x,C2x,d[1].y);    \
    V_MAC_F32(d[2].y,C2y,d[1].x);    \
    v_sub_f32(c[ 6].x,d[0].x,d[2].x);\
    v_add_f32(c[ 6].y,d[0].y,d[2].y);\
    v_add_f32(c[10].x,d[2].x,d[0].x);\
    v_sub_f32(c[10].y,d[2].y,d[0].y);\
    s_sync(lgkmcnt(0));              \
    v_add_f32(d[0].x,c[7].x,c[9].x); \
    v_sub_f32(d[0].y,c[7].y,c[9].y); \
    v_add_f32(d[1].x,c[7].y,c[9].y); \
    v_sub_f32(d[1].y,c[7].x,c[9].x); \
    v_mul_f32(d[2].x,C6x,d[1].x);    \
    v_mul_f32(d[2].y,C6x,d[1].y);    \
    v_mul_f32(c[8].x, f2,c[8].x);    \
    v_mul_f32(c[8].y,nf2,c[8].y);    \
    V_MAC_F32(d[2].x,C5x,d[1].y);    \
    V_MAC_F32(d[2].y,C5y,d[1].x);    \
    v_sub_f32(c[7].x,d[0].x,d[2].x); \
    v_add_f32(c[7].y,d[0].y,d[2].y); \
    v_add_f32(c[9].x,d[2].x,d[0].x); \
    v_sub_f32(c[9].y,d[2].y,d[0].y); \
    IFFT16_s7x7(c)                   \
    s_andn1exec_b64(stemp,vcc);      \
    v_exch_b32(c[ 0].y,c[15].y);     \
    v_exch_b32(c[ 8].x,c[15].x);     \
    v_exch_b32(c[ 8].y,c[ 7].y);     \
    v_exch_b32(c[ 4].x,c[ 7].x);     \
    v_exch_b32(c[ 4].y,c[11].y);     \
    v_exch_b32(c[12].x,c[11].x);     \
    s_mov_b64(exec,stemp);           \
}

#define FFT32x32_R2C_LDR(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny){\
    VZERO32(__c[0].x);                            \
    s_mov_b64(s8,exec);                           \
    v_cmp_u32(s10,__nx,__x,gt);                   \
    v_cmp_u32(__ncells,__icell,gt);               \
    s_and_b64(exec,vcc,s10);                      \
    ldg_b32(__c[0].x,__base,__vo,0);              \
    if(__ny>1){ s_shl_b32(__nx,__nx,2); }         \
    for( uint32_t i=1; i<32; ++i ){               \
        if(__ny>i){                               \
            S_ADD_U64_U32(__base,__base,__nx);    \
            ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        }                                         \
    }                                             \
    s_mov_b64(exec,s8);                           \
}

#define FFT32x32_R2C_LDR_FLIP(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny){\
    VZERO32(__c[0].x);                            \
    s_mov_b64(s8,exec);                           \
    v_cmp_u32(s10,__nx,__x,gt);                   \
    v_cmp_u32(__ncells,__icell,gt);               \
    s_and_b64(exec,vcc,s10);                      \
    ldg_b32(__c[0].x,__base,__vo,0);              \
    if(__ny>1){ s_shl_b32(__nx,__nx,2); }         \
    for( int i=1; i<32; ++i ){                    \
        if(__ny>i){                               \
            S_SUB_U64_U32(__base,__base,__nx);    \
            ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        }                                         \
    }                                             \
    s_mov_b64(exec,s8);                           \
}

#define FFT32x32_R2C_LDR_PAD(__c,__base,__vo,__x,__icell,__ncells,__nx,__ny,__pad_y){\
    VZERO32(__c[0].x);                          \
    s_mov_b64(s8,exec);                         \
    v_cmp_i32(s12,__x,zero,ge);                 \
    v_cmp_i32(s14,__x,__nx,lt);                 \
    v_cmp_u32(__ncells,__icell,gt);             \
    s_and_b64(s12,s12,s14);                     \
    s_and_b64(exec,vcc,s12);                    \
    ldg_b32(CPTR(__c)[__pad_y],__base,__vo,0x0);\
    if(__pad_y<31){ s_shl_b32(__nx,__nx,2); }   \
    for( int i=__pad_y+1; i<32; ++i ){          \
        s_cmpk_u32(__ny,i-__pad_y,gt);          \
        s_cbra_scc0(0);                         \
        S_ADD_U64_U32(__base,__base,__nx);      \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);  \
    }                                           \
__lable__(0);                                   \
    s_mov_b64(exec,s8);                         \
}

#define FFT32x32_R2C_LDR_SPLIT(__c,__base,__vo,__x,__icell,__ncells,__nx){\
    VZERO32(__c[0].x);                      \
    s_mov_b64(s8,exec);                     \
    v_cmp_u32(s10,__nx,__x,gt);             \
    v_cmp_u32(__ncells,__icell,gt);         \
    s_and_b64(exec,vcc,s10);                \
    ldg_b32(__c[0].x,__base,__vo,0);        \
    s_shl_b32(__nx,__nx,2);                 \
    for( int i=1; i<32; ++i ){              \
        S_ADD_U64_U32(__base,__base,__nx);  \
        ldg_b32(CPTR(__c)[i],__base,__vo,0);\
    }                                       \
    s_mov_b64(exec,s8);                     \
}

#define FFT32x32_R2C_LDR_SPLIT_EX(__c,__base,__vo,__x,__y,__icell,__ncells,__nx){\
    VZERO32(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__nx,__x,gt);               \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<32; ++i ){                \
        v_cmpx_u32(ic(i),__y,lt);             \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_LDR_SPLIT_PAD(__c,__base,__vo,__x,__y,__icell,__ncells,__nx,__ny){\
    VZERO32(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_i32(s10,__x,zero,ge);               \
    v_cmp_i32(s12,__nx,__x,gt);               \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(s10,s10,s12);                   \
    s_and_b64(s10,s10,vcc);                   \
    s_shl_b32(__nx,__nx,2);                   \
    s_mov_b64(exec,s10);                      \
    for( int i=0; i<32; ++i ){                \
        v_cmp_i32(s12,__y,zero,ge);           \
        v_cmp_i32(__ny,__y,gt);               \
        s_and_b64(exec,vcc,s12);              \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        if(i<31){                             \
            v_add_u32(__vo,__nx,__vo);        \
            s_mov_b64(exec,s10);              \
            v_add_i32(__y,ic(1),__y);         \
        }                                     \
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_LDR_SPLIT_NOV(__c,__base,__vo,__x,__vax,__vay,__icell,__ncells,__nx){\
    VZERO32(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__vax,__x,gt);              \
    v_cmp_u32(__ncells,__icell,gt);           \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<32; ++i ){                \
        S_ADD_U64_U32(__base,__base,__nx);    \
        v_cmpx_u32(ic(i),__vay,lt);           \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_XLDR_EX(__c,__base,__vo,__x,__y,__chn,__nc,__nx){\
    VZERO32(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__nx,__x,gt);               \
    v_cmp_u32(__nc,__chn,gt);                 \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<32; ++i ){                \
        s_cmpk_u32(__y,i,gt);                 \
        s_cbra_scc0(0);                       \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
__lable__(0);                                 \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_XLDR_PAD(__c,__base,__vo,__x,__y,__chn,__nc,__nx,__ny){\
    VZERO32(__c[0].x);                        \
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
    s_cbra_scc0(31);                          \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    S_ADD_U64_U32(__base,__base,__nx);        \
    for( int i=1; i<32; ++i ){                \
    __lable__(i-1);                           \
        s_addk_i32(__y,1);                    \
        s_cmpk_i32(__y,0,ge);                 \
        s_cbra_scc0(i-1);                     \
        s_cmp_i32(__y,__ny,lt);               \
        s_cbra_scc0(31);                      \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
        if(i<31){                             \
            S_ADD_U64_U32(__base,__base,__nx);\
        }                                     \
    }                                         \
__lable__(31);                                \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_XLDR_NOV(__c,__base,__vo,__x,__vax,__vay,__chn,__nc,__nx){\
    VZERO32(__c[0].x);                        \
    s_mov_b64(s8,exec);                       \
    v_cmp_u32(s10,__vax,__x,gt);              \
    v_cmp_u32(__nc,__chn,gt);                 \
    s_and_b64(exec,vcc,s10);                  \
    ldg_b32(__c[0].x,__base,__vo,0x0);        \
    s_shl_b32(__nx,__nx,2);                   \
    for( int i=1; i<32; ++i ){                \
        s_cmpk_u32(__vay,i,gt);               \
        s_cbra_scc0(0);                       \
        S_ADD_U64_U32(__base,__base,__nx);    \
        ldg_b32(CPTR(__c)[i],__base,__vo,0x0);\
    }                                         \
__lable__(0);                                 \
    s_mov_b64(exec,s8);                       \
}

#define FFT32x32_R2C_PERMST(__base,__vo,__o,__c,__sst,__sld,__mask){\
    s_sync(lgkmcnt(0)); s_barrier();       \
    STS_B32x17(__sst,32,__c,.x);           \
    S_ADD_U64(__base+0x02,__base+0x00,__o);\
    S_ADD_U64(__base+0x04,__base+0x02,__o);\
    S_ADD_U64(__base+0x06,__base+0x04,__o);\
    S_ADD_U64(__base+0x08,__base+0x06,__o);\
    s_sync(lgkmcnt(0)); s_barrier();       \
    LDS_B32x17(__c,__sld,32,.x);           \
    S_ADD_U64(__base+0x0a,__base+0x08,__o);\
    S_ADD_U64(__base+0x0c,__base+0x0a,__o);\
    S_ADD_U64(__base+0x0e,__base+0x0c,__o);\
    S_ADD_U64(__base+0x10,__base+0x0e,__o);\
    s_sync(lgkmcnt(0)); s_barrier();       \
    STS_B32x17(__sst,32,__c,.y);           \
    S_ADD_U64(__base+0x12,__base+0x10,__o);\
    S_ADD_U64(__base+0x14,__base+0x12,__o);\
    S_ADD_U64(__base+0x16,__base+0x14,__o);\
    S_ADD_U64(__base+0x18,__base+0x16,__o);\
    s_sync(lgkmcnt(0)); s_barrier();       \
    LDS_B32x17(__c,__sld,32,.y);           \
    S_ADD_U64(__base+0x1a,__base+0x18,__o);\
    S_ADD_U64(__base+0x1c,__base+0x1a,__o);\
    S_ADD_U64(__base+0x1e,__base+0x1c,__o);\
    S_ADD_U64(__base+0x20,__base+0x1e,__o);\
    s_mov_b64(exec,__mask);                \
    s_sync(lgkmcnt(0));                    \
    v_exch_b32(__c[ 0].y,__c[ 1].x);       \
    v_exch_b32(__c[ 2].y,__c[ 3].x);       \
    v_exch_b32(__c[ 4].y,__c[ 5].x);       \
    v_exch_b32(__c[ 6].y,__c[ 7].x);       \
    v_exch_b32(__c[ 8].y,__c[ 9].x);       \
    v_exch_b32(__c[10].y,__c[11].x);       \
    v_exch_b32(__c[12].y,__c[13].x);       \
    v_exch_b32(__c[14].y,__c[15].x);       \
    stg_b64(__base+0x00,__vo,0,v0 );       \
    stg_b64(__base+0x02,__vo,0,v16);       \
    stg_b64(__base+0x04,__vo,0,v2 );       \
    stg_b64(__base+0x06,__vo,0,v18);       \
    stg_b64(__base+0x08,__vo,0,v4 );       \
    stg_b64(__base+0x0a,__vo,0,v20);       \
    stg_b64(__base+0x0c,__vo,0,v6 );       \
    stg_b64(__base+0x0e,__vo,0,v22);       \
    stg_b64(__base+0x10,__vo,0,v8 );       \
    stg_b64(__base+0x12,__vo,0,v24);       \
    stg_b64(__base+0x14,__vo,0,v10);       \
    stg_b64(__base+0x16,__vo,0,v26);       \
    stg_b64(__base+0x18,__vo,0,v12);       \
    stg_b64(__base+0x1a,__vo,0,v28);       \
    stg_b64(__base+0x1c,__vo,0,v14);       \
    stg_b64(__base+0x1e,__vo,0,v30);       \
    stg_b64(__base+0x20,__vo,0,v32);       \
    s_endp();                              \
}

#define FFT32x32_C2R_LDPERM(__c,__base,__vo,__p0,__p1,__p2,__x,__y,__p,__q,__u,__bks,stemp){\
    uint32_t __sst=__vo+1;                                      \
    uint32_t __sld=__vo+2;                                      \
    ldg_b64(__c[0].x,__base,__vo,0x0);                          \
    s_shl_b32(__bks,__bks,8);                                   \
    for( int i=1; i<17; ++i ){                                  \
        S_ADD_U64_U32(__base,__base,__bks);                     \
        ldg_b64(__c[i].x,__base,__vo,0x0);                      \
    }                                                           \
    s_movk_i32(stemp,547);                                      \
    v_mad_u24(__sst,stemp,__p,__q);                             \
    v_mad_u24(__sld,stemp,__y,__x);                             \
    v_shl_b32(__sst,__sst,2);                                   \
    v_shl_b32(__sld,__sld,2);                                   \
    FFT32x32_C2R_CALC_LDS_PTRS(__p0,__p1,__p2,__x,__y,__u,__vo);\
    FFT32x32_SET_RF();                                          \
    s_sync(vmcnt(0));                                           \
    STS_B32x17(__sst,32,__c,.x)                                 \
    s_sync(lgkmcnt(0)); s_barrier();                            \
    LDS_B32x17(__c,__sld,32,.x)                                 \
    s_sync(lgkmcnt(0)); s_barrier();                            \
    STS_B32x17(__sst,32,__c,.y)                                 \
    s_sync(lgkmcnt(0)); s_barrier();                            \
    LDS_B32x17(__c,__sld,32,.y)                                 \
    s_sync(lgkmcnt(0)); s_barrier();                            \
}

#define FFT32x32_C2R_ST(__base,__vo,__c,__flipx,__icell,__ncells,__nx,__ny){\
    v_cmp_u32(s2,__flipx,__nx,lt);                      \
    v_cmp_u32(__ncells,__icell,gt);                     \
    s_and_b64(exec,vcc,s2);                             \
    stg_b32(__base,__vo,0x0,__c[0].x);                  \
    if(__ny>1){                                         \
        s_shl_b32(s2,__nx,2);                           \
        S_ADD_U64_U32(__base,__base,s2);                \
        stg_b32(__base,__vo,0x0,__c[0].y);              \
    }                                                   \
    for( int i=1; i<16; ++i ){                          \
        if(__ny>(i*2+0)){                               \
            S_ADD_U64_U32(__base,__base,s2);            \
            stg_b32(__base,__vo,0x0,__c[ga_brev4[i]].x);\
        }                                               \
        if(__ny>(i*2+1)){                               \
            S_ADD_U64_U32(__base,__base,s2);            \
            stg_b32(__base,__vo,0x0,__c[ga_brev4[i]].y);\
        }                                               \
    }                                                   \
    s_endp();                                           \
}

#define FFT32x32_C2R_ST_SPLICE(__base,__vo,__c,__flipx,__icell,__ncells,__vax,__vay,__nx){\
    v_cmp_u32(s2,__icell,__ncells,lt);              \
    v_cmp_u32(__flipx,__vax,lt);                    \
	s_shl_b32(__nx,__nx,2);                         \
    s_and_b64(exec,vcc,s2);                         \
    stg_b32(__base,__vo,0x0,__c[ga_brev4[0]].x);    \
    S_ADD_U64_U32(__base,__base,__nx);              \
    v_cmpx_u32(ic(1),__vay,lt);                     \
    stg_b32(__base,__vo,0x0,__c[ga_brev4[0]].y);    \
    for( int i=1; i<16; ++i ){                      \
        S_ADD_U64_U32(__base,__base,__nx);          \
        v_cmpx_u32(ic(i*2+0),__vay,lt);             \
        stg_b32(__base,__vo,0x0,__c[ga_brev4[i]].x);\
        S_ADD_U64_U32(__base,__base,__nx);          \
        v_cmpx_u32(ic(i*2+1),__vay,lt);             \
        stg_b32(__base,__vo,0x0,__c[ga_brev4[i]].y);\
    }                                               \
    s_endp();                                       \
}

#endif