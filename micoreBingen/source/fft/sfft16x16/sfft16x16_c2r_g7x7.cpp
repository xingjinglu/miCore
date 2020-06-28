#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft16x16.h"

void gfxcoder::sfft4x4_c2r_g7x7()
{
    uint2 c[12];
    for( int i=0; i<24; ++i ){ CPTR(c)[i]=v0+i; }

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

    const uint32_t cvo  =v18;
    const uint32_t x    =v24;
    const uint32_t y    =v25;
    const uint32_t u    =v26;
    const uint32_t flipx=v27;
    const uint32_t spa  =v28;
    const uint32_t spb  =v29;
    const uint32_t spc  =v30;
    const uint32_t tid  =v31;

    metadata_start();
	{
        metadata_set_lds_size(0x2440);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(32);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(20);
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

    s_lda_b256(s4,argptr,0x0);
    v_and_b32(x,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,4);
    v_mov_b32(tid,v0);
    v_sub_u32(v20,ic(16),x);
    v_shl_or_b32(v21,gidx,4,x);
    s_shl_b32(s12,gidy,3);
    s_shl_b32(s13,gidx,7);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=by*ldc+(bx<<4)+y*bks+x
    //===========================================================
    v_mul_lo_u32(v19,bks,y);
    s_mul_i32(s14,s12,ldc);
    s_add_u32(s15,s13,s14);
    S_ADD_U64_U32(cbase,cbase,s15);
    v_and_b32(flipx,ic(15),v20);
    v_add_shl_u32(cvo,v19,x,3);
    v_cmp_u32(pnc,v21,gt);
    FFT16x16_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,u,bks,vcc,s12);
    HIFFT16(c,spa,spb,spc,u,s14);
    VIFFT16(c,x,s14);
    //===========================================================
    //d_r+=by*ldr+gidx*784
    //nb=(pnc+15)>>4
    //m=pnc*49-gidx*784
    //n=n<nb-1?784:m
    //if(flipx<7){ smem[y*49+flipx]=c[i] } sync
    //if((0*256+tid)<n){ d_r[0*256+tid]=smem[0*256+tid] }
    //if((1*256+tid)<n){ d_r[1*256+tid]=smem[1*256+tid] }
    //if((2*256+tid)<n){ d_r[2*256+tid]=smem[2*256+tid] }
    //if((3*256+tid)<n){ d_r[3*256+tid]=smem[3*256+tid] }
    //===========================================================
    s_add_u32(s10,pnc,ic(15));
    s_movk_i32(s8,784);
    s_mul_i32(pnc,pnc,ic(49));
    s_mul_i32(s12,gidx,s8);
    s_shr_b32(s11,s10,4);
    s_shl_b32(gidy,gidy,2);
    s_sub_u32(s10,s11,ic(1));
    s_sub_u32(s9,pnc,s12);
    s_cmp_u32(gidx,s10,ge);
    s_cmov_b32(s8,s9);
    v_mad_u24(v17,ic(49),y,flipx);
    v_shl_b32(v16,v17,2);
    v_cmp_u32(ic(7),flipx,gt);
    s_barrier();
    s_andexec_b64(s0,vcc);
    lsst_b32(v16,0x00,c[0].x);
    lsst_b32(v16,0x1c,c[0].y);
    lsst_b32(v16,0x38,c[4].x);
    lsst_b32(v16,0x54,c[4].y);
    lsst_b32(v16,0x70,c[2].x);
    lsst_b32(v16,0x8c,c[2].y);
    lsst_b32(v16,0xa8,c[6].x);
    s_mul_i32(s2,ldr,gidy);
    s_mov_b64(exec,s0);
    s_shl2_add_u32(s3,s12,s2);
    S_ADD_U64_U32(rbase,rbase,s3);
    v_addk_u32(v5,256,tid);
    v_addk_u32(v6,512,tid);
    v_addk_u32(v7,768,tid);
    v_shl_b32(v4,tid,2);
    v_cmp_u32(s0,v5,s8,lt);
    v_cmp_u32(s2,v6,s8,lt);
    v_cmp_u32(s6,v7,s8,lt);
    s_sync(lgkmcnt(0));
    s_barrier();
    lsld_b32(v0,v4,0x000);
    lsld_b32(v1,v4,0x400);
    lsld_b32(v2,v4,0x800);
    lsld_b32(v3,v4,0xc00);
    v_cmpx_u32(s8,tid,gt);
    s_sync(lgkmcnt(3));
    stg_b32(rbase,v4,0x000,v0);
    s_mov_b64(exec,s0);
    s_sync(lgkmcnt(2));
    stg_b32(rbase,v4,0x400,v1);
    s_mov_b64(exec,s2);
    s_sync(lgkmcnt(1));
    stg_b32(rbase,v4,0x800,v2);
    s_mov_b64(exec,s6);
    s_sync(lgkmcnt(0));
    stg_b32(rbase,v4,0xc00,v3);
    s_endp();
}