#include"../../include/gfxcoder.h"

void gfxcoder::sbco8x6()
{
    uint32_t c[8][8], a[2][8], b[2][8];
    for( uint32_t i=0; i<64; ++i ){ ((uint32_t*)&c[0][0])[i]=v0+i; }
    for( uint32_t i=0; i<4; ++i ){
        a[0][i]=v64+i; a[0][4+i]=v72+i;
        b[0][i]=v68+i; b[0][4+i]=v76+i;
        a[1][i]=v80+i; a[1][4+i]=v88+i;
        b[1][i]=v84+i; b[1][4+i]=v92+i;
    }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t gidz  =s38;
    const uint32_t relo  =s2 ;
    const uint32_t abase =s4 ;
    const uint32_t bbase =s6 ;
    const uint32_t amap  =s4 ;
    const uint32_t ldb   =s8 ;
    const uint32_t eldb  =s8 ;
    const uint32_t n     =s9 ;
    const uint32_t k     =s10;
    const uint32_t ags   =s11;
    const uint32_t col   =s11;
    const uint32_t o     =s12;
    const uint32_t so    =s36;
    const uint32_t dbtr  =s37;
    const uint32_t cbase =s0 ;
    const uint32_t alpha =s2 ;
    const uint32_t m     =s3 ;
    const uint32_t ldc   =s10;

    const uint32_t apld=v96 ;
    const uint32_t bpld=v104;
    const uint32_t ao  =v106;
    const uint32_t co  =v107;
    const uint32_t bo  =v108;
    const uint32_t asld=v109;
    const uint32_t bsld=v110;
    const uint32_t asst=v111;
    const uint32_t bsst=v112;
    const uint32_t csst=v113;
    const uint32_t csld=v114;
    const uint32_t tidx=v115;
    
    metadata_start();
    {
        metadata_set_lds_size(0x5000);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(68);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(43);
        metadata_set_vgprcnt(116);
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

    s_mov_b32(gidz,s4);
    s_mov_b32(s12,gidx);
    s_lda_b64(amap,argptr,0x0);
    s_lda_b128(s8,argptr,0x10);
    v_and_b32(v1,ic(63),v0);
    v_and_b32(v3,ic(31),v0);
    v_and_b32(v5,ic(7),v0);
    v_shr_b32(v2,v0,6);
    v_shr_b32(v4,v0,5);
    v_shr_b32(v6,v1,3);
    s_sync(lgkmcnt(0));

    s_shr_b32(s13,n,31);
    s_andk_b32(n,n,0x7fffffff);
    s_cmpk_u32(s13,0,eq);
    s_cmov_b32(gidx,gidy);
    s_csel_b32(gidy,s12,gidy);
    v_shl_or_b32(tidx,gidx,8,v0);
    v_shl_or_b32(v7,gidy,5,v3);
    v_shl_b32(v8,tidx,3);
    ldg_b64(ao,amap,v8,0);

    s_lda_b128(s4,argptr,0x20);
    s_shl_b32(s16,gidz,2);
    s_mul_i32(s17,ldb,k);
    S_MUL_U64_U32(s12,s16,ags);
    S_MUL_U64_U32(s14,s16,s17);
    s_shl_b32(col,gidy,6);
    s_lda_b64(relo,argptr,0x8);
    s_add_u32(s20,n,ic(1));
    s_shr_b32(s21,s20,1);
    s_sync(lgkmcnt(0));
    S_ADD_U64(abase,abase,s12);
    S_ADD_U64(bbase,bbase,s14);
    s_ld_b256(o,relo,0x00);
    v_cmp_u32(s21,v7,gt);
    v_cmov_b32(v7,zero,v7);
    v_mul_lo_u32(v8,ldb,v4);
    v_shl_b32(v9,v7,3);
    v_shl_add_u32(bo,v8,2,v9);
    s_sync(lgkmcnt(0));
    S_ADD_U64_U32(s20,abase,o+0);
    S_ADD_U64_U32(s22,abase,o+1);
    S_ADD_U64_U32(s24,abase,o+2);
    S_ADD_U64_U32(s26,abase,o+3);
    S_ADD_U64_U32(s28,abase,o+4);
    S_ADD_U64_U32(s30,abase,o+5);
    S_ADD_U64_U32(s32,abase,o+6);
    S_ADD_U64_U32(s34,abase,o+7);
    s_sync(vmcnt(0));
    ldg_b32(apld+0,s20,ao,0);
    ldg_b32(apld+1,s22,ao,0);
    ldg_b32(apld+2,s24,ao,0);
    ldg_b32(apld+3,s26,ao,0);
    ldg_b32(apld+4,s28,ao,0);
    ldg_b32(apld+5,s30,ao,0);
    ldg_b32(apld+6,s32,ao,0);
    ldg_b32(apld+7,s34,ao,0);
    ldg_b64(bpld,bbase,bo,0);

    //asld=(v2<<8)|(v5<<4)
    //bsld=v6<<4
    //asst=v0<<2
    //bsst=v0<<3
    //csst=(v2<<11)|(v6<<8)|(v5<<4)
    //csld=(v2<<11)|(v1<<2)
    s_ld_b256(o,relo,0x20);
    v_shl_b32(v3,v5,4);
    v_shl_b32(v4,v1,2);
    v_shl_b32(bsld,v6,4);
    v_shl_b32(asst,v0,2);
    v_shl_b32(bsst,v0,3);
    v_shl_or_b32(v7,v6,8,v3);
    v_shl_or_b32(asld,v2,8,v3);
    v_shl_or_b32(csld,v2,11,v4);
    v_shl_or_b32(csst,v2,11,v7);

    LDSZERO64(s20,true);
    s_sync(vmcnt(0)&lgkmcnt(0));
    s_barrier();
    lsstx_b32x2(asst,0x00,apld+0,0x04,apld+1);
    lsstx_b32x2(asst,0x08,apld+2,0x0c,apld+3);
    lsstx_b32x2(asst,0x10,apld+4,0x14,apld+5);
    lsstx_b32x2(asst,0x18,apld+6,0x1c,apld+7);
    lsst_b64(bsst,0x2000,bpld);
    s_shl_b32(eldb,ldb,5);
    s_movk_i32(so,64);
    s_sub_u32(k,k,ic(8));
    s_movk_i32(dbtr,0x2800);
    s_cmpk_u32(k,0,eq);
    s_cmovk_i32(eldb,0);
    if(kernel.icode&1){ s_nop(); }
    S_ADD_U64_U32(s20,abase,o+0);
    S_ADD_U64_U32(s22,abase,o+1);
    S_ADD_U64_U32(s24,abase,o+2);
    S_ADD_U64_U32(s26,abase,o+3);
    S_ADD_U64_U32(s28,abase,o+4);
    S_ADD_U64_U32(s30,abase,o+5);
    S_ADD_U64_U32(s32,abase,o+6);
    S_ADD_U64_U32(s34,abase,o+7);
    S_ADD_U64_U32(bbase,bbase,eldb);
    s_sync(lgkmcnt(0));
    s_barrier();
    lsld_b128(a[0][0],asld,0x0000);
    lsld_b128(b[0][0],bsld,0x2000);
    lsld_b128(a[0][4],asld,0x0080);
    lsld_b128(b[0][4],bsld,0x2080);

__lable__(0);
    lsld_b128(a[1][0],asld,0x0400);
    lsld_b128(b[1][0],bsld,0x2100);
    lsld_b128(a[1][4],asld,0x0480);
    lsld_b128(b[1][4],bsld,0x2180);
    v_xor_b32(asst,dbtr,asst);
    s_sync(lgkmcnt(4));
    s_ld_soe_b256(o,relo,so);
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_add_u32(so,so,ic(32));
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    ldg_b32(apld+0,s20,ao,0);
    ldg_b32(apld+1,s22,ao,0);
    ldg_b32(apld+2,s24,ao,0);
    ldg_b32(apld+3,s26,ao,0);
    ldg_b32(apld+4,s28,ao,0);
    ldg_b32(apld+5,s30,ao,0);
    ldg_b32(apld+6,s32,ao,0);
    ldg_b32(apld+7,s34,ao,0);
    ldg_b64(bpld,bbase,bo,0);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_sync(lgkmcnt(0));
    lsld_b128(a[0][0],asld,0x0800);
    lsld_b128(b[0][0],bsld,0x2200);
    lsld_b128(a[0][4],asld,0x0880);
    lsld_b128(b[0][4],bsld,0x2280);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_add_u32(s20,abase,o);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(s21,abase+1,zero);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    s_add_u32(s22,abase,o+1);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    s_addc_u32(s23,abase+1,zero);
    lsld_b128(a[1][0],asld,0x0c00);
    lsld_b128(b[1][0],bsld,0x2300);
    lsld_b128(a[1][4],asld,0x0c80);
    lsld_b128(b[1][4],bsld,0x2380);
    v_xor_b32(bsst,dbtr,bsst);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_add_u32(s24,abase,o+2);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    s_addc_u32(s25,abase+1,zero);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    s_add_u32(s26,abase,o+3);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_addc_u32(s27,abase+1,zero);
    lsld_b128(a[0][0],asld,0x1000);
    lsld_b128(b[0][0],bsld,0x2400);
    lsld_b128(a[0][4],asld,0x1080);
    lsld_b128(b[0][4],bsld,0x2480);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_add_u32(s28,abase,o+4); 
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(s29,abase+1,zero);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    s_add_u32(s30,abase,o+5);  
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    lsld_b128(a[1][0],asld,0x1400);
    lsld_b128(b[1][0],bsld,0x2500);
    lsld_b128(a[1][4],asld,0x1480);
    lsld_b128(b[1][4],bsld,0x2580);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_addc_u32(s31,abase+1,zero); 
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    s_add_u32(s32,abase,o+6);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    s_addc_u32(s33,abase+1,zero);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    lsld_b128(a[0][0],asld,0x1800);
    lsld_b128(b[0][0],bsld,0x2600);
    lsld_b128(a[0][4],asld,0x1880);
    lsld_b128(b[0][4],bsld,0x2680);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_add_u32(s34,abase,o+7);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(s35,abase+1,zero);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    s_cmpk_u32(k,8,eq);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    lsld_b128(a[1][0],asld,0x1c00);
    lsld_b128(b[1][0],bsld,0x2700);
    lsld_b128(a[1][4],asld,0x1c80);
    lsld_b128(b[1][4],bsld,0x2780);
    s_sync(lgkmcnt(5));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_cmovk_i32(eldb,0);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    v_xor_b32(asld,dbtr,asld);
    s_sync(vmcnt(0)&lgkmcnt(4));
    lsstx_b32x2(asst,0x00,apld+0,0x04,apld+1);
    lsstx_b32x2(asst,0x08,apld+2,0x0c,apld+3);
    lsstx_b32x2(asst,0x10,apld+4,0x14,apld+5);
    lsstx_b32x2(asst,0x18,apld+6,0x1c,apld+7);
    lsst_b64(bsst,0x2000,bpld);
    v_xor_b32(bsld,dbtr,bsld);
    V_OP4_R(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_sync(lgkmcnt(0));
    s_barrier();
    lsld_b128(a[0][0],asld,0x0000);
    lsld_b128(b[0][0],bsld,0x2000);
    lsld_b128(a[0][4],asld,0x0080);
    lsld_b128(b[0][4],bsld,0x2080);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    s_add_u32(bbase,bbase,eldb);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    s_addc_u32(bbase+1,bbase+1,zero);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    s_sub_u32(k,k,ic(8));
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    s_cbra_scc0(0);

    s_lda_b32(ldc,argptr,0x40);
    s_lda_b128(s0,argptr,0x30);
    s_mul_i32(s6,gidz,n);
    s_mov_b64(s4,exec);
    s_add_u32(s7,s6,col);
    s_sync(lgkmcnt(0));
    s_shl_b32(s8,ldc,2);
    s_shl_b32(s10,ldc,4);
    S_MUL_U64_U32(s12,s7,s8);
    S_ADD_U64(cbase,cbase,s12);
    v_cmp_u32(m,tidx,gt);
    s_mov_b64(s6,vcc);
    s_mov_b64(s12,cbase);

    for( int i=0, ilab=1; i<8; ++i )
    {
        const int s=i&3;
        if(i>0){
            if(s!=0){
            __lable__(ilab); ++ilab;
                s_mov_b64(exec,s4);
                s_add_u32(col,col,ic(1));
            } else {
                s_mov_b64(exec,s4);
                s_shl_b32(s28,s8,5);
                s_add_u32(col,col,ic(29));
                S_ADD_U64_U32(s12,cbase,s28);
            }
        }
        lsst_b128(csst,0x00,c[i][0]);
        lsst_b128(csst,0x80,c[i][4]);
        if(s==0){
            S_ADD_U64_U32(s14,s12,s10);
            S_ADD_U64_U32(s16,s14,s10);
            S_ADD_U64_U32(s18,s16,s10);
            S_ADD_U64_U32(s20,s18,s10);
            S_ADD_U64_U32(s22,s20,s10);
            S_ADD_U64_U32(s24,s22,s10);
            S_ADD_U64_U32(s26,s24,s10);
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
        s_mov_b64(exec,s6);
        lsldx_b32x2(v0,csld,0,1);
        lsldx_b32x2(v2,csld,2,3);
        lsldx_b32x2(v4,csld,4,5);
        lsldx_b32x2(v6,csld,6,7);

        s_cmp_u32(col,n,lt);
        s_cbra_scc0(7);
        s_sync(lgkmcnt(3));
        v_mul_f32(v0,alpha,v0);
        stg_b32(s12,co,0,v0);
    
        s_add_u32(s3,col,ic(4));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v1,alpha,v1);
        stg_b32(s14,co,0,v1);
    
        s_add_u32(s3,col,ic(8));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(2));
        v_mul_f32(v2,alpha,v2);
        stg_b32(s16,co,0,v2);
    
        s_add_u32(s3,col,ic(12));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v3,alpha,v3);
        stg_b32(s18,co,0,v3);
    
        s_add_u32(s3,col,ic(16));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(1));
        v_mul_f32(v4,alpha,v4);
        stg_b32(s20,co,0,v4);
    
        s_add_u32(s3,col,ic(20));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v5,alpha,v5);
        stg_b32(s22,co,0,v5);
    
        s_add_u32(s3,col,ic(24));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(0));
        v_mul_f32(v6,alpha,v6);
        stg_b32(s24,co,0,v6);
    
        s_add_u32(s3,col,ic(28));
        s_cmp_u32(s3,n,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v7,alpha,v7);
        stg_b32(s26,co,0,v7);
    }
__lable__(7);
    s_endp();
}