#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft16x16.h"

void gfxcoder::sfft4x4_c2r_perm( uint32_t mask )
{
    uint2 c[12];
    for( int i=0; i<24; ++i ){ CPTR(c)[i]=v0+i; }
    int ny=(mask&0xff)+1;

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t cbase =s4 ;
    const uint32_t ldc   =s6 ;
    const uint32_t bks   =s7 ;
    const uint32_t C0x   =s6 ;
    const uint32_t C0y   =s7 ;
    const uint32_t C1x   =s8 ;
    const uint32_t C1y   =s9 ;
    const uint32_t C2x   =s10;
    const uint32_t C2y   =s11;
    const uint32_t ncells=s12;
    const uint32_t rbase =s0 ;
    const uint32_t ldx   =s2 ;
    const uint32_t ldy   =s3 ;
    const uint32_t nx    =s4 ;

    const uint32_t cvo  =v18;
    const uint32_t x    =v24;
    const uint32_t y    =v25;
    const uint32_t u    =v26;
    const uint32_t flipx=v27;
    const uint32_t spa  =v28;
    const uint32_t spb  =v29;
    const uint32_t spc  =v30;
    const uint32_t rvo  =v16;
    const uint32_t icell=v17;

    metadata_start();
	{
        metadata_set_lds_size(0x2440);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(40);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(17);
        metadata_set_vgprcnt(31);
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
    s_lda_b32(ncells,argptr,0x20);
    v_and_b32(x,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,4);
    v_sub_u32(v20,ic(16),x);
    v_shl_or_b32(v21,gidx,4,x);
    s_shl_b32(s9,gidy,3);
    s_shl_b32(s10,gidx,7);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=by*ldc+(bx<<4)+y*bks+x
    //===========================================================
    v_mul_lo_u32(v19,bks,y);
    v_and_b32(flipx,ic(15),v20);
    s_mul_i32(s11,s9,ldc);
    s_add_u32(s10,s10,s11);
    S_ADD_U64_U32(cbase,cbase,s10);
    v_add_shl_u32(cvo,v19,x,3);
    v_cmp_u32(ncells,v21,gt);
    FFT16x16_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,u,bks,vcc,s8);
    HIFFT16(c,spa,spb,spc,u,s4);
    VIFFT16(c,x,s4);
    //===========================================================
    //by*ldy+icell*ldx+flipx
    //===========================================================
    v_shl_or_b32(icell,gidx,4,y);
    s_shl_b32(s5,gidy,2);
    s_lda_b32(nx,argptr,0x24);
    s_lda_b128(s0,argptr,0x0);
    if(mask&0x100){ for( int i=0; i<16; ++i ){ v_max_f32(CPTR(c)[i],zero,CPTR(c)[i]); } }
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v18,ldx,icell);
    S_MUL_U64_U32(s6,s5,ldy);
    S_ADD_U64(rbase,rbase,s6);
    v_add_shl_u32(rvo,v18,flipx,2);
    FFT16x16_C2R_ST(rbase,rvo,c,flipx,icell,ncells,nx,ny);
}