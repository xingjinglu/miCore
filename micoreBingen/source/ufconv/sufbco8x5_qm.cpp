#include"../../include/gfxcoder.h"

void gfxcoder::sufbco8x5_qm()
{
    uint32_t c[4][8], a[2][8], b[2][4];
    for( uint32_t i=0; i<32; ++i ){ ((uint32_t*)&c[0][0])[i]=v0+i; }
    for( uint32_t i=0; i<4; ++i ){
        a[0][i]=v32+i; a[0][4+i]=v36+i; b[0][i]=v40+i;
        a[1][i]=v44+i; a[1][4+i]=v48+i; b[1][i]=v52+i;
    }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s3 ;
    const uint32_t gidy  =s2 ;
    const uint32_t group =s22;
    const uint32_t abase =s4 ;
    const uint32_t bbase =s6 ;
    const uint32_t ng    =s8 ;
    const uint32_t m     =s9 ;
    const uint32_t n     =s10;
    const uint32_t k     =s11;
    const uint32_t amag  =s12;
    const uint32_t cmag  =s14;
    const uint32_t dimx  =s21;
    const uint32_t col   =s28;
    const uint32_t elda  =s2 ;
    const uint32_t eldb  =s3 ;
    const uint32_t dbtr  =s8 ;
    const uint32_t cbase =s0 ;
    const uint32_t alpha =s2 ;

    const uint32_t apld=v56;
    const uint32_t bpld=v64;
    const uint32_t ao  =v65;
    const uint32_t bo  =v67;
    const uint32_t co  =v68;
    const uint32_t asld=v69;
    const uint32_t bsld=v70;
    const uint32_t asst=v71;
    const uint32_t bsst=v72;
    const uint32_t csst=v73;
    const uint32_t csld=v74;
    const uint32_t tidx=v75;

    metadata_start();
    {
        metadata_set_lds_size(0x5400);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(64);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(33);
        metadata_set_vgprcnt(76);
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
        kernel.enable_sgpr_group_id_z();
        kernel.enable_vgpr_iterm_id_1d();
    }
    kernel.end_descr();

    s_mov_b32(group,s4);
    s_shl_b32(col,gidy,5);
    s_lda_b256(s4,argptr,0x00);
    s_lda_b128(s12,argptr,0x20);
    s_lda_b32(dimx,argptr,0x3c);
    v_and_b32(v1,ic(63),v0);
    v_and_b32(v3,ic(31),v0);
    v_shl_or_b32(tidx,gidx,8,v0);
    v_shl_or_b32(v5,gidx,6,v1);
    v_or_b32(v6,col,v3);
    v_shr_b32(v2,v0,6);
    v_shr_b32(v4,v0,5);
    s_shl_b32(s2,group,2);
    s_sync(lgkmcnt(0));

    s_mul_i32(s16,k,ng);
    s_mul_i32(s17,n,ng);
    UFCO_COMPUTE_START_ADDR_A(ao,m,s16,v5,dimx,amag,v7,s18,2);
    s_mul_i32(s3,s2,k);
    S_MUL_U64_U32(s12,n,s2);
    S_MUL_U64_U32(s18,m,s3);
    S_ADD_U64(bbase,bbase,s12);
    S_ADD_U64(abase,abase,s18);
    v_cmp_u32(n,v6,gt);
    v_cmov_b32(v6,zero,v6);
    v_mul_lo_u32(v7,s17,v4);
    v_mul_lo_u32(v8,m,v2);
    v_add_shl_u32(bo,v6,v7,2);
    v_shl_add_u32(ao,v8,2,ao);
    v_shl_add_u32(ao+1,m,4,ao);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    ldg_b32 (bpld+0,bbase,bo+0,0);
    v_readlane0_b32(s12,v2);
    UFCO_COMPUTE_START_ADDR_C(co,m,s17,tidx,cmag,v2,s18,0);

    //asld=(wave<<8)|(v3<<4)
    //bsld=v4<<4
    //asst=v0<<4
    //bsst=v0<<2
    //csst=(wave<<11)|(v4<<8)|(v3<<4)
    //csld=(wave<<11)|(v1<<2)
    s_shl_b32(s2,s12,11);
    s_shl_b32(s3,s12,8);
    v_and_b32(v3,ic(7),v1);
    v_shr_b32(v4,v1,3);
    v_shl_b32(v5,v3,4);
    v_shl_b32(bsld,v4,4);
    v_shl_b32(asst,v0,4);
    v_shl_b32(bsst,v0,2);
    v_shl_or_b32(v6,v4,8,v5);
    v_shl_or_b32(csld,v1,2,s2);
    v_or_b32(asld,s3,v5);
    v_or_b32(csst,s2,v6);

    for( int i=0; i<32; ++i ){ v_mov_b32(((uint32_t*)&c[0][0])[i],zero); }
    s_sync(vmcnt(0));
    lsst_b128(asst,0x0000,apld+0);
    lsst_b128(asst,0x1000,apld+4);
    lsst_b32(bsst,0x2000,bpld);
    s_sub_u32(k,k,ic(8));
    s_shl_b32(elda,m,5);
    s_shl_b32(eldb,s17,5);
    s_movk_i32(dbtr,0x3000);
    s_cmpk_u32(k,0,eq);
    s_cmovk_i32(elda,0);
    s_cmovk_i32(eldb,0);
    s_sync(lgkmcnt(0));
    s_barrier();
    if(kernel.icode&1){ s_nop(); }
    S_ADD_U64_U32(abase,abase,elda);
    lsld_b128(a[0][0],asld,0x0000);
    lsld_b128(a[0][4],asld,0x0080);
    lsld_b128(b[0][0],bsld,0x2000);

__lable__(0);
    lsld_b128(a[1][0],asld,0x0400);
    lsld_b128(a[1][4],asld,0x0480);
    lsld_b128(b[1][0],bsld,0x2080);
    v_xor_b32(asst,dbtr,asst);
    s_sync(lgkmcnt(3));
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    S_ADD_U64_U32(bbase,bbase,eldb);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    lsld_b128(a[0][0],asld,0x0800);
    lsld_b128(a[0][4],asld,0x0880);
    lsld_b128(b[0][0],bsld,0x2100);
    v_xor_b32(bsst,dbtr,bsst);
    s_sync(lgkmcnt(3));
    ldg_b32(bpld,bbase,bo,0);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    lsld_b128(a[1][0],asld,0x0c00);
    lsld_b128(a[1][4],asld,0x0c80);
    lsld_b128(b[1][0],bsld,0x2180);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_cmpk_u32(k,8,eq);
    lsld_b128(a[0][0],asld,0x1000);
    lsld_b128(a[0][4],asld,0x1080);
    lsld_b128(b[0][0],bsld,0x2200);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    s_cmovk_i32(elda,0);
    lsld_b128(a[1][0],asld,0x1400);
    lsld_b128(a[1][4],asld,0x1480);
    lsld_b128(b[1][0],bsld,0x2280);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_cmovk_i32(eldb,0);
    lsld_b128(a[0][0],asld,0x1800);
    lsld_b128(b[0][0],bsld,0x2300);
    lsld_b128(a[0][4],asld,0x1880);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    s_add_u32(abase,abase,elda);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_addc_u32(abase+1,abase+1,zero);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    s_sub_u32(k,k,ic(8));
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    lsld_b128(a[1][0],asld,0x1c00);
    lsld_b128(a[1][4],asld,0x1c80);
    lsld_b128(b[1][0],bsld,0x2380);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    v_xor_b32(asld,dbtr,asld);
    v_xor_b32(bsld,dbtr,bsld);
    s_sync(vmcnt(0)&lgkmcnt(3));
    lsst_b128(asst,0x0000,apld+0);
    lsst_b128(asst,0x1000,apld+4);
    lsst_b32(bsst,0x2000,bpld);
    V_OP4_R(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_sync(lgkmcnt(0));
    s_barrier();
    lsld_b128(a[0][0],asld,0x0000);
    lsld_b128(a[0][4],asld,0x0080);
    lsld_b128(b[0][0],bsld,0x2000);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    s_cbra_scc0(0);

    s_lda_b32(alpha,argptr,0x38);
    s_lda_b64(cbase,argptr,0x30);
    s_mul_i32(s6,n,group);
    s_add_u32(s7,s6,col);
    s_shl_b32(s8,m,2);
    s_shl_b32(s9,m,4);
    S_MUL_U64_U32(s4,s7,s8);
    s_sync(lgkmcnt(0));
    v_cmp_u32(dimx,tidx,gt);
    S_ADD_U64(s12,cbase,s4);
    s_mov_b64(s4,vcc);
    s_mov_b64(s6,exec);

    for( int i=0; i<4; ++i )
    {
        if(i>0){
        __lable__(i);
            s_add_u32(col,col,ic(1));
            s_mov_b64(exec,s6);
        }
        lsst_b128(csst,0x00,c[i][0]);
        lsst_b128(csst,0x80,c[i][4]);
        if(i==0){
            S_ADD_U64_U32(s14,s12,s9);
            S_ADD_U64_U32(s16,s14,s9);
            S_ADD_U64_U32(s18,s16,s9);
            S_ADD_U64_U32(s20,s18,s9);
            S_ADD_U64_U32(s22,s20,s9);
            S_ADD_U64_U32(s24,s22,s9);
            S_ADD_U64_U32(s26,s24,s9);
        } else {
            S_ADD_U64_U32(s12,s12,s8);
            S_ADD_U64_U32(s14,s14,s8);
            S_ADD_U64_U32(s16,s16,s8);
            S_ADD_U64_U32(s18,s18,s8);
            S_ADD_U64_U32(s20,s20,s8);
            S_ADD_U64_U32(s22,s22,s8);
            S_ADD_U64_U32(s24,s24,s8);
            S_ADD_U64_U32(s26,s26,s8);
        }
        s_sync(lgkmcnt(0));
        s_mov_b64(exec,s4);
        lsldx_b32x2(v0,csld,0,1);
        lsldx_b32x2(v2,csld,2,3);
        lsldx_b32x2(v4,csld,4,5);
        lsldx_b32x2(v6,csld,6,7);

        s_cmp_u32(col,n,lt);
        s_cbra_scc0(4);
        s_sync(lgkmcnt(3));
        v_mul_f32(v0,alpha,v0);
        stg_b32(s12,co,0,v0);

        s_add_u32(s3,col,ic(4));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v1,alpha,v1);
        stg_b32(s14,co,0,v1);

        s_add_u32(s3,col,ic(8));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(2));
        v_mul_f32(v2,alpha,v2);
        stg_b32(s16,co,0,v2);

        s_add_u32(s3,col,ic(12));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v3,alpha,v3);
        stg_b32(s18,co,0,v3);

        s_add_u32(s3,col,ic(16));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(1));
        v_mul_f32(v4,alpha,v4);
        stg_b32(s20,co,0,v4);

        s_add_u32(s3,col,ic(20));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v5,alpha,v5);
        stg_b32(s22,co,0,v5);

        s_add_u32(s3,col,ic(24));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(0));
        v_mul_f32(v6,alpha,v6);
        stg_b32(s24,co,0,v6);

        s_add_u32(s3,col,ic(28));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v7,alpha,v7);
        stg_b32(s26,co,0,v7);
    }
__lable__(4);
    s_endp();
}