#include"../../include/gfxcoder.h"

void gfxcoder::sgemm6x5()
{
    uint32_t c[4][8], a[2][8], b[2][4];
    for( uint32_t i=0; i<32; ++i ){ ((uint32_t*)&c[0][0])[i]=v0+i; }
    for( uint32_t i=0; i<4; ++i ){
        a[0][i]=v32+i; a[0][4+i]=v36+i; b[0][i]=v40+i;
        a[1][i]=v44+i; a[1][4+i]=v48+i; b[1][i]=v52+i;
    }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t gidz  =s23;
    const uint32_t abase =s4 ;
    const uint32_t bbase =s6 ;
    const uint32_t abks  =s8 ;
    const uint32_t bbks  =s9 ;
    const uint32_t lda   =s10;
    const uint32_t ldb   =s11;
    const uint32_t m     =s12;
    const uint32_t n     =s13;
    const uint32_t k     =s8 ;
    const uint32_t elda  =s2 ;
    const uint32_t eldb  =s3 ;
    const uint32_t dbtr  =s9 ;
    const uint32_t cbase =s0 ;
    const uint32_t ldc   =s2 ;
    const uint32_t cbks  =s3 ;
    const uint32_t col   =s16;
    const uint32_t alpha =s17;

    const uint32_t apld=v56;
    const uint32_t bpld=v64;
    const uint32_t ao  =v68;
    const uint32_t bo  =v70;
    const uint32_t asld=v71;
    const uint32_t bsld=v72;
    const uint32_t sst =v73;
    const uint32_t csst=v74;
    const uint32_t csld=v75;
    const uint32_t tidx=v76;
    const uint32_t co  =v32;

    metadata_start();
    {
        metadata_set_lds_size(0x1800);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(64);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(29);
        metadata_set_vgprcnt(77);
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

    s_shl_b32(gidz,s4,2);
    s_lda_b256(s4,argptr,0x0);
    v_and_b32(v1,ic(15),v0);
    v_and_b32(v3,ic(7),v0);
    v_shr_b32(v2,v0,4);
    v_shr_b32(v4,v0,3);
    v_shl_or_b32(v5,gidx,4,v1);
    v_shl_or_b32(v6,gidy,3,v3);
    v_shl_or_b32(tidx,gidx,6,v0);
    s_sync(lgkmcnt(0));

    //abase+=gidz*abks, ao=v2*lda+(v5<<4)
    //bbase+=gidz*bbks, bo=v4*ldb+(v6<<3)
    s_lda_b64(s12,argptr,0x20);
    S_MUL_U64_U32(s14,gidz,abks);
    S_MUL_U64_U32(s16,gidz,bbks);
    S_ADD_U64(abase,abase,s14);
    S_ADD_U64(bbase,bbase,s16);
    v_mul_lo_u32(v7,lda,v2);
    v_mul_lo_u32(v8,ldb,v4);
    s_sync(lgkmcnt(0));
    s_lda_b32(k,argptr,0x28);
    s_add_u32(s14,m,ic(3));
    s_add_u32(s15,n,ic(1));
    s_shr_b32(s16,s14,2);
    s_shr_b32(s17,s15,1);
    v_cmp_u32(s16,v5,gt);
    v_cmov_b32(v5,zero,v5);
    v_cmp_u32(s17,v6,gt);
    v_cmov_b32(v6,zero,v6);
    v_shl_b32(v5,v5,4);
    v_shl_b32(v6,v6,4);
    v_shl_add_u32(ao,v7,2,v5);
    v_shl_add_u32(bo,v8,2,v6);
    v_shl_add_u32(ao+1,lda,4,ao);
    ldg_b128(bpld+0,bbase,bo+0,0);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);

    //col=gidy<<5
    //sst=v0<<4
    //asld=v3<<4
    //bsld=v4<<4
    //csst=(v4<<8)|(v3<<4)
    //csld=v0<<2
    s_shl_b32(col,gidy,5);
    v_shl_b32(sst,v0,4);
    v_shl_b32(asld,v3,4);
    v_shl_b32(bsld,v4,4);
    v_shl_b32(csld,v0,2);
    v_shl_or_b32(csst,v4,8,asld);

    for( int i=0; i<32; ++i ){ v_mov_b32(((uint32_t*)&c[0][0])[i],zero); }
    s_sync(vmcnt(1)&lgkmcnt(0));
    lsst_b128(sst,0x0000,bpld);
    lsst_b128(sst,0x0400,apld);
    s_sub_u32(k,k,ic(8));
    s_shl_b32(eldb,ldb,5);
    s_shl_b32(elda,lda,5);
    s_movk_i32(dbtr,0xc00);
    s_cmpk_u32(k,0,eq);
    s_cmovk_i32(eldb,0);
    s_cmovk_i32(elda,0);
    S_ADD_U64_U32(bbase,bbase,eldb);
    S_ADD_U64_U32(abase,abase,elda);
    if((kernel.icode&1)==0){ s_nop(); }
    s_sync(vmcnt(0)&lgkmcnt(0));
    lsld_b128(b[0][0],bsld,0x0000);
    lsld_b128(a[0][0],asld,0x0400);
    lsld_b128(a[0][4],asld,0x0480);
    lsst_b128(sst,0x0800,apld+4);

__lable__(0);
    lsld_b128(b[1][0],bsld,0x0080);
    lsld_b128(a[1][0],asld,0x0500);
    lsld_b128(a[1][4],asld,0x0580);
    v_xor_b32(sst,dbtr,sst);
    s_sync(lgkmcnt(4));
    ldg_b128(bpld+0,bbase,bo+0,0);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_cmpk_u32(k,8,eq);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_cmovk_i32(eldb,0);
    lsld_b128(b[0][0],bsld,0x0100);
    lsld_b128(a[0][0],asld,0x0600);
    lsld_b128(a[0][4],asld,0x0680);
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
    lsld_b128(b[1][0],bsld,0x0180);
    lsld_b128(a[1][0],asld,0x0700);
    lsld_b128(a[1][4],asld,0x0780);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_add_u32(bbase,bbase,eldb);
    lsld_b128(b[0][0],bsld,0x0200);
    lsld_b128(a[0][0],asld,0x0800);
    lsld_b128(a[0][4],asld,0x0880);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(bbase+1,bbase+1,zero);
    lsld_b128(b[1][0],bsld,0x0280);
    lsld_b128(a[1][0],asld,0x0900);
    lsld_b128(a[1][4],asld,0x0980);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_add_u32(abase,abase,elda);
    lsld_b128(b[0][0],bsld,0x0300);
    lsld_b128(a[0][0],asld,0x0a00);
    lsld_b128(a[0][4],asld,0x0a80);
    s_sync(lgkmcnt(3));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(abase+1,abase+1,zero);
    lsld_b128(b[1][0],bsld,0x0380);
    lsld_b128(a[1][0],asld,0x0b00);
    lsld_b128(a[1][4],asld,0x0b80);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_T(&c[3][0],&a[0][0],b[0][3]);
    v_xor_b32(asld,dbtr,asld);
    v_xor_b32(bsld,dbtr,bsld);
    s_sync(vmcnt(0)&lgkmcnt(3));
    lsst_b128(sst,0x0000,bpld);
    lsst_b128(sst,0x0400,apld);
    V_OP4_R(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    s_sub_u32(k,k,ic(8));
    s_sync(lgkmcnt(0));
    lsld_b128(b[0][0],bsld,0x0000);
    lsld_b128(a[0][0],asld,0x0400);
    lsld_b128(a[0][4],asld,0x0480);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_sync(vmcnt(0));
    lsst_b128(sst,0x0800,apld+4);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_T(&c[3][4],&a[1][4],b[1][3]);
    s_cbra_scc0(0);

    s_lda_b32(alpha,argptr,0x2c);
    s_lda_b128(s0,argptr,0x30);
    v_shl_b32(co,tidx,2);
    v_cmp_u32(m,tidx,gt);
    s_mov_b64(s18,exec);
    s_mov_b64(s20,vcc);
    s_mov_b32(s22,n);
    s_shl_b32(s8,col,2);
    s_sync(lgkmcnt(0));

    for( int i=0; i<4; ++i )
    {
        if(i>0){
        __lable__(i);
            s_add_u32(col,col,ic(1));
            s_mov_b64(exec,s18);
        }
        lsst_b128(csst,0x00,c[i][0]);
        lsst_b128(csst,0x80,c[i][4]);
        if(i==0){
            S_MUL_U64_U32(s4,gidz,cbks);
            S_MUL_U64_U32(s6,s8,ldc);
            s_shl_b32(s23,ldc,4);
            s_shl_b32(s24,ldc,2);
            S_ADD_U64(cbase,cbase,s4);
            S_ADD_U64(cbase,cbase,s6);
            S_ADD_U64_U32(s2 ,s0 ,s23);
            S_ADD_U64_U32(s4 ,s2 ,s23);
            S_ADD_U64_U32(s6 ,s4 ,s23);
            S_ADD_U64_U32(s8 ,s6 ,s23);
            S_ADD_U64_U32(s10,s8 ,s23);
            S_ADD_U64_U32(s12,s10,s23);
            S_ADD_U64_U32(s14,s12,s23);
        } else {
            S_ADD_U64_U32(s0 ,s0 ,s24);
            S_ADD_U64_U32(s2 ,s2 ,s24);
            S_ADD_U64_U32(s4 ,s4 ,s24);
            S_ADD_U64_U32(s6 ,s6 ,s24);
            S_ADD_U64_U32(s8 ,s8 ,s24);
            S_ADD_U64_U32(s10,s10,s24);
            S_ADD_U64_U32(s12,s12,s24);
            S_ADD_U64_U32(s14,s14,s24);
        }
        s_sync(lgkmcnt(0));
        s_mov_b64(exec,s20);
        lsldx_b32x2(v0,csld,0,1);
        lsldx_b32x2(v2,csld,2,3);
        lsldx_b32x2(v4,csld,4,5);
        lsldx_b32x2(v6,csld,6,7);

        s_cmp_u32(col,s22,lt);
        s_cbra_scc0(4);
        s_sync(lgkmcnt(3));
        v_mul_f32(v0,alpha,v0);
        stg_b32(s0,co,0,v0);

        s_add_u32(s23,col,ic(4));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v1,alpha,v1);
        stg_b32(s2,co,0,v1);

        s_add_u32(s23,col,ic(8));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(2));
        v_mul_f32(v2,alpha,v2);
        stg_b32(s4,co,0,v2);

        s_add_u32(s23,col,ic(12));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v3,alpha,v3);
        stg_b32(s6,co,0,v3);

        s_add_u32(s23,col,ic(16));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(1));
        v_mul_f32(v4,alpha,v4);
        stg_b32(s8,co,0,v4);

        s_add_u32(s23,col,ic(20));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v5,alpha,v5);
        stg_b32(s10,co,0,v5);

        s_add_u32(s23,col,ic(24));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        s_sync(lgkmcnt(0));
        v_mul_f32(v6,alpha,v6);
        stg_b32(s12,co,0,v6);

        s_add_u32(s23,col,ic(28));
        s_cmp_u32(s23,s22,lt);
        s_cbra_scc0(i+1);
        v_mul_f32(v7,alpha,v7);
        stg_b32(s14,co,0,v7);
    }
__lable__(4);
    s_endp();
}