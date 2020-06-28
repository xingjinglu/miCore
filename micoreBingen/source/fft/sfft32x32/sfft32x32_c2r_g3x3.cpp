#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft32x32.h"

/*args : d_r, ldr, pnc, d_c, ldc, bks*/

void gfxcoder::sfft5x5_c2r_g3x3()
{
    uint2 c[24];
    for( int i=0; i<48; ++i ){ CPTR(c)[i]=v0+i; }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t rbase =s4 ;
    const uint32_t ldr   =s6 ;
    const uint32_t pnc   =s7 ;
    const uint32_t cbase =s8 ;
    const uint32_t ldc   =s10;
    const uint32_t bks   =s11;
    const uint32_t C0x   =s8 ;
    const uint32_t C0y   =s9 ;
    const uint32_t C1x   =s10;
    const uint32_t C1y   =s11;
    const uint32_t C2x   =s12;
    const uint32_t C2y   =s13;
    const uint32_t C3x   =s14;
    const uint32_t C3y   =s15;
    const uint32_t C4x   =s16;
    const uint32_t C4y   =s17;
    const uint32_t C5x   =s18;
    const uint32_t C5y   =s19;
    const uint32_t C6x   =s20;
    const uint32_t C6y   =s21;
    const uint32_t C7x   =s22;
    const uint32_t C7y   =s23;
    const uint32_t C8x   =s24;
    const uint32_t C8y   =s25;
 
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
    const uint32_t tid  =v56;

    metadata_start();
	{
        metadata_set_lds_size(0x4600);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(32);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(30);
        metadata_set_vgprcnt(57);
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

    s_lda_b256(s4,argptr,0x0);
    v_and_b32(x,ic(31),v0);
    v_and_b32(p,ic(7),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,5);
    v_shr_b32(q,v0,3);
    v_mov_b32(tid,v0);
    v_sub_u32(v38,ic(32),x);
    s_shl_b32(s12,gidy,3);
    s_shl_b32(s13,gidx,6);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=by*ldc+(bx<<3)+q*bks+p
    //===========================================================
    v_mul_lo_u32(v37,bks,q);
    v_and_b32(flipx,ic(31),v38);
    s_mul_i32(s14,s12,ldc);
    s_add_u32(s15,s13,s14);
    S_ADD_U64_U32(cbase,cbase,s15);
    v_add_shl_u32(cvo,v37,p,3);
    FFT32x32_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,p,q,u,bks,s12);
    HIFFT32(c,spa,spb,spc,u,s0);
    VIFFT32_s3x3(c,x,s0);
    //===========================================================
    //d_r+=by*ldr+gidx*72
    //nb=(pnc+7)>>3
    //m=pnc*9-gidx*72
    //n=gidx<nb-1?72:m
    //if(flipx<3){ smem[y*9+flipx]=c[i] } sync
    //if(tid<n){ d_r[tid]=smem[tid] }
    //===========================================================
    s_add_u32(s10,pnc,ic(7));
    s_movk_i32(s8,72);
    s_mul_i32(pnc,pnc,ic(9));
    s_mul_i32(s12,gidx,s8);
    s_shr_b32(s11,s10,3);
    s_shl_b32(gidy,gidy,2);
    s_sub_u32(s10,s11,ic(1));
    s_sub_u32(s9,pnc,s12);
    s_cmp_u32(gidx,s10,ge);
    s_cmov_b32(s8,s9);
    v_mad_u24(v33,ic(9),y,flipx);
    v_shl_b32(v32,v33,2);
    v_cmp_u32(ic(3),flipx,gt);
    s_barrier();
    s_andexec_b64(s0,vcc);
    lsst_b32(v32,0x00,c[0].x);
    lsst_b32(v32,0x0c,c[0].y);
    lsst_b32(v32,0x18,c[8].x);
    s_mul_i32(s2,ldr,gidy);
    s_mov_b64(exec,s0);
    s_shl2_add_u32(s3,s12,s2);
    S_ADD_U64_U32(rbase,rbase,s3);
    v_shl_b32(v1,tid,2);
    s_sync(lgkmcnt(0));
    s_barrier();
    v_cmpx_u32(s8,tid,gt);
    lsld_b32(v0,v1,0x0);
    s_sync(lgkmcnt(0));
    stg_b32(rbase,v1,0x0,v0);
    s_endp();
}