#ifndef __mcode_h__
#define __mcode_h__

#if __gfxip__==gfx900
#define V_MAC_F32(c,a,b) v_mac_f32(c,a,b)
#else
#define V_MAC_F32(c,a,b) v_fmac_f32(c,a,b)
#endif

#if __gfxip__<gfx908
#define V_DP2_F32_F16(c,a,b) v_dp2_f32_f16(c,a,b,c)
#else
#define V_DP2_F32_F16(c,a,b) v_dp2_f32_f16(c,a,b)
#endif

#define S_ADD_U64(c,a,b){   \
    s_add_u32(c,a,b);       \
    s_addc_u32(c+1,a+1,b+1);\
}
    
#define S_ADD_U64_U32(c,a,b){\
    s_add_u32(c,a,b);        \
    s_addc_u32(c+1,a+1,zero);\
}

#define S_SUB_U64(c,a,b){   \
    s_sub_u32(c,a,b);       \
    s_subc_u32(c+1,a+1,b+1);\
}

#define S_SUB_U64_U32(c,a,b){\
    s_sub_u32(c,a,b);        \
    s_subc_u32(c+1,a+1,zero);\
}
    
#define S_MUL_U64_U32(c,a,b){\
    s_mul_i32(c,a,b);        \
    s_mul_hi_u32(c+1,a,b);   \
}

#define S_MDM_U32(dm,a,b,mp){\
    S_MUL_U64_U32(dm,a,mp);  \
    s_shr_b64(dm,dm,mp+1);   \
    s_mul_i32(dm+1,b,dm);    \
    s_sub_u32(dm+1,a,dm+1);  \
}

#define V_ADD_U64(c,a,b){      \
    v_add_co_u32(c,a,b);       \
    v_addc_co_u32(c+1,a+1,b+1);\
}

#define V_ADD_U64_U32(c,a,b){   \
    v_add_co_u32(c,a,b);        \
    v_addc_co_u32(c+1,zero,a+1);\
}

#define V_MUL_U64_U24(c,a,b){\
    v_mul_u24(c,a,b);        \
    v_mul_hi_u24(c+1,a,b);   \
}

#define V_MUL_U64_U32(c,a,b){\
    v_mul_lo_u32(c,a,b);     \
    v_mul_hi_u32(c+1,a,b);   \
}

#define V_MDM_U32(dm,a,b,mp){\
    V_MUL_U64_U32(dm,mp,a);  \
    v_shr_b64(dm,dm,mp+1);   \
    v_mul_lo_u32(dm+1,b,dm); \
    v_sub_u32(dm+1,a,dm+1);  \
}

#define V_MDMX_U32(dm,a,b,m,s){\
    V_MUL_U64_U32(dm,m,a);     \
    v_shr_b64(dm,dm,s);        \
    v_mul_lo_u32(dm+1,b,dm);   \
    v_sub_u32(dm+1,a,dm+1);    \
}

#define LDSZERO64(saved,bar){\
    v_cmp_u32(zero,v0,eq);   \
    v_mov_b32(v0,zero);      \
    v_mov_b32(v1,zero);      \
    v_mov_b32(v2,zero);      \
    v_mov_b32(v3,zero);      \
    s_andexec_b64(saved,vcc);\
    lsst_b128(v0,0,v0);      \
    s_mov_b64(exec,saved);   \
    s_sync(lgkmcnt(0));      \
    if(bar){ s_barrier(); }  \
    lsld_b128(v4 ,v0,0);     \
    lsld_b128(v8 ,v0,0);     \
    lsld_b128(v12,v0,0);     \
    lsld_b128(v16,v0,0);     \
    lsld_b128(v20,v0,0);     \
    lsld_b128(v24,v0,0);     \
    lsld_b128(v28,v0,0);     \
    lsld_b128(v32,v0,0);     \
    lsld_b128(v36,v0,0);     \
    lsld_b128(v40,v0,0);     \
    lsld_b128(v44,v0,0);     \
    lsld_b128(v48,v0,0);     \
    lsld_b128(v52,v0,0);     \
    lsld_b128(v56,v0,0);     \
    lsld_b128(v60,v0,0);     \
}

#define VDM_U32(quo,rem,a,b,vt,st){        \
    v_cvt_f32_u32(rem,b);                  \
    v_rcp_f32(rem,rem);                    \
    v_mulk_f32(rem,0x4f800000,rem);        \
    v_cvt_u32_f32(rem,rem);                \
    v_readlane0_b32(st+4,rem);             \
    s_mul_i32(st+0,b,st+4);                \
    s_mul_hi_u32(st+1,b,st+4);             \
    s_sub_u32(st+2,zero,st+0);             \
    s_cmpk_u32(st+1,0,ne);                 \
    s_csel_b32(st+0,st+0,st+2);            \
    s_mul_hi_u32(st+0,st+0,st+4);          \
    s_sub_u32(st+2,st+4,st+0);             \
    s_add_u32(st+4,st+4,st+0);             \
    s_cmpk_u32(st+1,0,ne);                 \
    s_csel_b32(st+4,st+2,st+4);            \
    v_mul_hi_u32(rem,st+4,a);              \
    v_mul_lo_u32(quo,b,rem);               \
    v_sub_u32(vt,a,quo);                   \
    v_cmp_u32(st+0,a,quo,ge);              \
    v_cmp_u32(st+2,vt,b,ge);               \
    s_and_b64(st+2,st+2,st+0);             \
    v_addc_co_u32(rem,vcc,rem,ic( 0),st+2);\
    v_addc_co_u32(rem,vcc,rem,ic(-1),st+0);\
    v_cmp_i32(vcc,b,zero,ne);              \
    v_cmov_b32(quo,ic(-1),rem);            \
    v_mul_lo_u32(vt,b,quo);                \
    v_sub_u32(rem,a,vt);                   \
}

#define VDMX_U32(quo,rem,a,b,vt,st){       \
    s_cmpk_u32(b,1,gt);                    \
    s_cbranch_scc0(37);                    \
    v_cvt_f32_u32(rem,b);                  \
    v_rcp_f32(rem,rem);                    \
    v_mulk_f32(rem,0x4f800000,rem);        \
    v_cvt_u32_f32(rem,rem);                \
    v_readlane0_b32(st+4,rem);             \
    s_mul_i32(st+0,b,st+4);                \
    s_mul_hi_u32(st+1,b,st+4);             \
    s_sub_u32(st+2,zero,st+0);             \
    s_cmpk_u32(st+1,0,ne);                 \
    s_csel_b32(st+0,st+0,st+2);            \
    s_mul_hi_u32(st+0,st+0,st+4);          \
    s_sub_u32(st+2,st+4,st+0);             \
    s_add_u32(st+4,st+4,st+0);             \
    s_cmpk_u32(st+1,0,ne);                 \
    s_csel_b32(st+4,st+2,st+4);            \
    v_mul_hi_u32(rem,st+4,a);              \
    v_mul_lo_u32(quo,b,rem);               \
    v_sub_u32(vt,a,quo);                   \
    v_cmp_u32(st+0,a,quo,ge);              \
    v_cmp_u32(st+2,vt,b,ge);               \
    s_and_b64(st+2,st+2,st+0);             \
    v_addc_co_u32(rem,vcc,rem,ic( 0),st+2);\
    v_addc_co_u32(rem,vcc,rem,ic(-1),st+0);\
    v_cmp_i32(vcc,b,zero,ne);              \
    v_cmov_b32(quo,ic(-1),rem);            \
    v_mul_lo_u32(vt,b,quo);                \
    v_sub_u32(rem,a,vt);                   \
    s_branch(2);                           \
    v_mov_b32(quo,a);                      \
    v_mov_b32(rem,zero);                   \
}

#define UFCO_COMPUTE_START_ADDR_AC(ao,co,m,n,k,idx,dimx,mag,vt,st,rdx){\
    if(rdx>0){                            \
        s_shr_b32(st+1,dimx,rdx);         \
        s_shr_b32(st+2,m,rdx);            \
    }                                     \
    s_sub_u32(st,rdx>0?st+1:dimx,ic(1));  \
    v_cmp_u32(rdx>0?st+1:dimx,idx,gt);    \
    v_mov_b32(vt+3,st);                   \
    v_cmov_b32(vt+2,vt+3,idx);            \
    V_MDM_U32(vt,vt+2,(rdx>0?st+2:m),mag);\
    s_mul_i32(st+0,k,rdx>0?st+2:m);       \
    s_mul_i32(st+1,n,rdx>0?st+2:m);       \
    v_mul_lo_u32(vt+2,st+0,vt);           \
    v_mul_lo_u32(vt+3,st+1,vt);           \
    v_add_shl_u32(ao,vt+1,vt+2,2+rdx);    \
    v_add_shl_u32(co,vt+1,vt+3,2+rdx);    \
}

#define UFCO_COMPUTE_START_ADDR_A(dst,m,k,idx,dimx,mag,vt,st,rdx){\
    s_shr_b32(st,dimx,rdx);            \
    s_shr_b32(st+1,m,rdx);             \
    s_sub_u32(st+2,st,ic(1));          \
    v_cmp_u32(st,idx,gt);              \
    v_mov_b32(vt+2,st+2);              \
    v_cmov_b32(vt+2,vt+2,idx);         \
    V_MDM_U32(vt,vt+2,st+1,mag);       \
    s_mul_i32(st,st+1,k);              \
    v_mul_lo_u32(vt+2,st,vt);          \
    v_add_shl_u32(dst,vt+1,vt+2,2+rdx);\
}

#define UFCO_COMPUTE_START_ADDR_C(dst,m,n,idx,mag,vt,st,rdx){\
    if(rdx>0){ s_shr_b32(st,m,rdx); }  \
    V_MDM_U32(vt,idx,(rdx>0?st:m),mag);\
    s_mul_i32(st,rdx>0?st:m,n);        \
    v_mul_lo_u32(vt,st,vt);            \
    v_add_shl_u32(dst,vt,vt+1,2+rdx);  \
}

#define MMA_32x32x1_F32_F32(c,a,b)  mma_32x32x1_f32_f32(c,a,b,c)
#define MMA_32x32x2_F32_F32(c,a,b)  mma_32x32x2_f32_f32(c,a,b,c)
#define MMA_32x32x4_F32_F16(c,a,b)  mma_32x32x4_f32_f16(c,a,b,c)
#define MMA_32x32x8_F32_F16(c,a,b)  mma_32x32x8_f32_f16(c,a,b,c)
#define MMA_32x32x2_F32_BF16(c,a,b) mma_32x32x2_f32_bf16(c,a,b,c)
#define MMA_32x32x4_F32_BF16(c,a,b) mma_32x32x4_f32_bf16(c,a,b,c)
#define MMA_16x16x1_F32_F32(c,a,b)  mma_16x16x1_f32_f32(c,a,b,c)
#define MMA_16x16x4_F32_F32(c,a,b)  mma_16x16x4_f32_f32(c,a,b,c)
#define MMA_16x16x4_F32_F16(c,a,b)  mma_16x16x4_f32_f16(c,a,b,c)
#define MMA_16x16x16_F32_F16(c,a,b) mma_16x16x16_f32_f1(c,a,b,c)
#define MMA_16x16x2_F32_BF16(c,a,b) mma_16x16x2_f32_bf16(c,a,b,c)
#define MMA_16x16x8_F32_BF16(c,a,b) mma_16x16x8_f32_bf16(c,a,b,c)
#define MMA_4x4x1_F32_F32(c,a,b)    mma_4x4x1_f32_f32(c,a,b,c)
#define MMA_4x4x4_F32_F16(c,a,b)    mma_4x4x4_f32_f16(c,a,b,c)
#define MMA_4x4x2_F32_BF16(c,a,b)   mma_4x4x2_f32_bf16(c,a,b,c)

#define V_OP4_R(c,a,b){        \
    V_MAC_F32((c)[0],(a)[0],b);\
    s_setprio(1);              \
    V_MAC_F32((c)[1],(a)[1],b);\
    V_MAC_F32((c)[2],(a)[2],b);\
    V_MAC_F32((c)[3],(a)[3],b);\
}

#define V_OP4_S(c,a,b){        \
    V_MAC_F32((c)[0],(a)[0],b);\
    V_MAC_F32((c)[1],(a)[1],b);\
    V_MAC_F32((c)[2],(a)[2],b);\
    V_MAC_F32((c)[3],(a)[3],b);\
}

#define V_OP4_T(c,a,b){        \
    V_MAC_F32((c)[0],(a)[0],b);\
    V_MAC_F32((c)[1],(a)[1],b);\
    V_MAC_F32((c)[2],(a)[2],b);\
    V_MAC_F32((c)[3],(a)[3],b);\
    s_setprio(0);              \
}

#define V_XOP4_R(c,a,b){                  \
    v_fma_f32_f16((c)[0],(a)[0],b,(c)[0]);\
    s_setprio(1);                         \
    v_fma_f32_f16((c)[1],(a)[1],b,(c)[1]);\
    v_fma_f32_f16((c)[2],(a)[2],b,(c)[2]);\
    v_fma_f32_f16((c)[3],(a)[3],b,(c)[3]);\
}

#define V_XOP4_S(c,a,b){                  \
    v_fma_f32_f16((c)[0],(a)[0],b,(c)[0]);\
    v_fma_f32_f16((c)[1],(a)[1],b,(c)[1]);\
    v_fma_f32_f16((c)[2],(a)[2],b,(c)[2]);\
    v_fma_f32_f16((c)[3],(a)[3],b,(c)[3]);\
}

#define V_XOP4_T(c,a,b){                  \
    v_fma_f32_f16((c)[0],(a)[0],b,(c)[0]);\
    v_fma_f32_f16((c)[1],(a)[1],b,(c)[1]);\
    v_fma_f32_f16((c)[2],(a)[2],b,(c)[2]);\
    v_fma_f32_f16((c)[3],(a)[3],b,(c)[3]);\
    s_setprio(0);                         \
}

#define V_XDP2x4_R(c,a,b){         \
    V_DP2_F32_F16((c)[0],(a)[0],b);\
    s_setprio(1);                  \
    V_DP2_F32_F16((c)[1],(a)[1],b);\
    V_DP2_F32_F16((c)[2],(a)[2],b);\
    V_DP2_F32_F16((c)[3],(a)[3],b);\
}

#define V_XDP2x4_S(c,a,b){         \
    V_DP2_F32_F16((c)[0],(a)[0],b);\
    V_DP2_F32_F16((c)[1],(a)[1],b);\
    V_DP2_F32_F16((c)[2],(a)[2],b);\
    V_DP2_F32_F16((c)[3],(a)[3],b);\
}

#define V_XDP2x4_T(c,a,b){         \
    V_DP2_F32_F16((c)[0],(a)[0],b);\
    V_DP2_F32_F16((c)[1],(a)[1],b);\
    V_DP2_F32_F16((c)[2],(a)[2],b);\
    V_DP2_F32_F16((c)[3],(a)[3],b);\
    s_setprio(0);                  \
}

#endif
