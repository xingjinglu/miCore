#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft32x32.h"

/*args : d_r, ldx, ldy, d_c, ldc, bks, ncells, nx*/

void gfxcoder::sfft5x5_c2r_perm( uint32_t mask )
{
    uint2 c[24];
    for( int i=0; i<48; ++i ){ CPTR(c)[i]=v0+i; }
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
    const uint32_t C3x   =s12;
    const uint32_t C3y   =s13;
    const uint32_t C4x   =s14;
    const uint32_t C4y   =s15;
    const uint32_t C5x   =s16;
    const uint32_t C5y   =s17;
    const uint32_t C6x   =s18;
    const uint32_t C6y   =s19;
    const uint32_t C7x   =s20;
    const uint32_t C7y   =s21;
    const uint32_t C8x   =s22;
    const uint32_t C8y   =s23;
    const uint32_t rbase =s0 ;
    const uint32_t ldx   =s2 ;
    const uint32_t ldy   =s3 ;
    const uint32_t ncells=s4 ;
    const uint32_t nx    =s5 ;

    const uint32_t p    =v34;
    const uint32_t q    =v35;
    const uint32_t cvo  =v36;
    const uint32_t x    =v48;
    const uint32_t y    =v49;
    const uint32_t u    =v50;
    const uint32_t flipx=v51;
    const uint32_t spa  =v52;
    const uint32_t spb  =v54;
    const uint32_t spc  =v55;
    const uint32_t rvo  =v32;
    const uint32_t icell=v33;

    metadata_start();
	{
        metadata_set_lds_size(0x4600);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(40);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(28);
        metadata_set_vgprcnt(56);
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
    v_and_b32(x,ic(31),v0);
    v_and_b32(p,ic(7),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,5);
    v_shr_b32(q,v0,3);
    v_sub_u32(v38,ic(32),x);
    s_shl_b32(s8,gidy,3);
    s_shl_b32(s9,gidx,6);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=by*ldc+(bx<<3)+q*bks+p
    //===========================================================
    v_mul_lo_u32(v37,bks,q);
    v_and_b32(flipx,ic(31),v38);
    s_mul_i32(s10,s8,ldc);
    s_add_u32(s11,s9,s10);
    S_ADD_U64_U32(cbase,cbase,s11);
    v_add_shl_u32(cvo,v37,p,3);
    FFT32x32_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,p,q,u,bks,s8);
    HIFFT32(c,spa,spb,spc,u,s4);
    VIFFT32(c,x,s4);
    //===========================================================
    //r+=by*ldy+icell*ldx+flipx
    //===========================================================
    v_shl_or_b32(icell,gidx,3,y);
    s_shl_b32(s8,gidy,2);
    s_lda_b64(s4,argptr,0x20);
    s_lda_b128(s0,argptr,0x0);
    if(mask&0x100){ for( int i=0; i<32; ++i ){ v_max_f32(CPTR(c)[i],zero,CPTR(c)[i]); } }
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v34,ldx,icell);
    S_MUL_U64_U32(s6,s8,ldy);
    S_ADD_U64(rbase,rbase,s6);
    v_add_shl_u32(rvo,v34,flipx,2);
    FFT32x32_C2R_ST(rbase,rvo,c,flipx,icell,ncells,nx,ny);
}