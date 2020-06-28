#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft16x16.h"

void gfxcoder::sfft4x4_r2c_qerm_s3x3()
{
    uint2 c[12];
    for( int i=0; i<8; ++i ){ c[i].x=v0+i; c[i].y=v8+i; }
    for( int i=0; i<8; ++i ){ CPTR(c)[16+i]=v16+i; }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t rbase =s4 ;
    const uint32_t ncells=s6 ;
    const uint32_t ldr   =s7 ;
    const uint32_t C0x   =s7 ;
    const uint32_t C0y   =s8 ;
    const uint32_t C1x   =s9 ;
    const uint32_t C1y   =s10;
    const uint32_t C2x   =s11;
    const uint32_t C2y   =s12;
    const uint32_t sk0   =s13;
    const uint32_t sk1   =s14;
    const uint32_t sk2   =s15;
    const uint32_t k0x   =s16;
    const uint32_t k0y   =s17;
    const uint32_t k1x   =s18;
    const uint32_t k1y   =s19;
    const uint32_t k2x   =s20;
    const uint32_t k2y   =s21;
    const uint32_t k3x   =s22;
    const uint32_t k3y   =s23;
    const uint32_t k4x   =s24;
    const uint32_t k4y   =s25;
    const uint32_t k5x   =s26;
    const uint32_t k5y   =s27;
    const uint32_t cbase =s0 ;
    const uint32_t ldc   =s2 ;
    const uint32_t bks   =s3 ;

    const uint32_t icell=v3 ;
    const uint32_t v    =v4 ;
    const uint32_t x    =v24;
    const uint32_t y    =v25;
    const uint32_t u    =v26;
    const uint32_t xsst =v27;
    const uint32_t xsld =v28;
    const uint32_t ysst =v29;
    const uint32_t ysld =v27;
    const uint32_t osst =v30;
    const uint32_t osld =v31;
    const uint32_t cvo  =v18;

    metadata_start();
	{
        metadata_set_lds_size(0x2440);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(32);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(32);
        metadata_set_vgprcnt(32);
    }
    metadata_end();

    kernel.start_descr();
    {
        kernel.enable_kernarg_segment();
        kernel.set_fp32_mode_round(amdgpu_fp_mode_rn);
        kernel.set_fp32_mode_denorm(amdgpu_fp_denorm_fsd);
        kernel.set_fp16_fp64_mode_round(amdgpu_fp_mode_rn);
        kernel.set_fp16_fp64_mode_denorm(amdgpu_fp_denorm_fn);
        kernel.enable_dx10_clamp();
        kernel.enable_ieee_mode();
        kernel.set_user_sgprcnt(2);
        kernel.enable_sgpr_group_id_x();
        kernel.enable_sgpr_group_id_y();
        kernel.enable_vgpr_iterm_id_1d();
    }
    kernel.end_descr();

    s_lda_b128(s4,argptr,0x10);
    v_and_b32(x,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,4);
    v_shr_b32(v,x,1);
    v_sub_u32(v5,ic(2),x);
    v_shl_or_b32(icell,gidx,4,y);
    v_mad_u24(v6,ic(9),icell,v5);
    v_shl_b32(v2,v6,2);
    s_shl_b32(s10,gidy,2);
    s_sync(lgkmcnt(0));
    //==================================================================
    S_MUL_U64_U32(s8,ldr,s10);
    S_ADD_U64(rbase,rbase,s8);
    v_cmp_u32(s10,icell,ncells,lt);
    v_cmp_u32(ic(3),x,gt);
    v_mov_b32(c[0].x,zero);
    v_mov_b32(c[0].y,zero);
    v_mov_b32(c[1].x,zero);
    s_mov_b64(s8,exec);
    s_and_b64(exec,vcc,s10);
    ldg_b32(c[0].x,rbase,v2,0x18);
    ldg_b32(c[0].y,rbase,v2,0x0c);
    ldg_b32(c[1].x,rbase,v2,0x00);
    s_mov_b64(exec,s8);
    v_mov_b32(c[1].y,zero);
    //==================================================================
    FFT16x16_R2C_CALC_LDS_PTRS(xsst,xsld,ysst,osst,osld,x,y,u,v,s7);
    FFT16x16_SET_RF();
    FFT16x16_SET_SCOEF();
    s_sync(vmcnt(0));
    VFFT16_C2(c,xsst,xsld);
    HFFT16(c,ysst,ysld,u,s4,_C2);
    //==================================================================
    v_shl_or_b32(v20,gidx,4,x);
    s_shl_b32(s4,gidx,7);
    s_shl_b32(s5,gidy,3);
    s_lda_b128(cbase,argptr,0x0);
    s_movk_i32(s9,0);
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v19,bks,y);
    s_mul_i32(s7,ldc,s5);
    s_mov_b32(s8,bks);
    s_add_u32(s2,s7,s4);
    s_shl_b64(s18,s8,7);
    S_ADD_U64_U32(cbase,cbase,s2);
    v_add_shl_u32(cvo,v19,x,3);
    v_cmp_u32(ncells,v20,gt);
    FFT16x16_R2C_PERMST(cbase,cvo,s18,c,osst,osld,vcc);
}