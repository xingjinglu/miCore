#include"../../include/gfxcoder.h"

/*
d_a   : 0x00
d_b   : 0x08
abks  : 0x10
bbks  : 0x14
lda   : 0x18
ldb   : 0x1c
m     : 0x20
n     : 0x24
k     : 0x28
alpha : 0x2c
d_c   : 0x30
ldc   : 0x38
cbks  : 0x3c
*/

void gfxcoder::sgemm8x6()
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
    const uint32_t gidz  =s22;
    const uint32_t abase =s4 ;
    const uint32_t bbase =s6 ;
    const uint32_t abks  =s8 ;
    const uint32_t bbks  =s9 ;
    const uint32_t lda   =s10;
    const uint32_t ldb   =s11;
    const uint32_t m     =s12;
    const uint32_t n     =s13;
    const uint32_t k     =s8 ;
    const uint32_t col   =s21;
    const uint32_t elda  =s2 ;
    const uint32_t eldb  =s3 ;
    const uint32_t dbtr  =s9 ;
    const uint32_t cbase =s0 ;
    const uint32_t ldc   =s2 ;
    const uint32_t cbks  =s3 ;
    const uint32_t alpha =s20;

    const uint32_t apld=v96 ;
    const uint32_t bpld=v104;
    const uint32_t ao  =v106;
    const uint32_t bo  =v108;
    const uint32_t asld=v109;
    const uint32_t bsld=v110;
    const uint32_t asst=v111;
    const uint32_t bsst=v112;
    const uint32_t csst=v113;
    const uint32_t csld=v114;
    const uint32_t tidx=v115;
    const uint32_t co  =v64 ;

    metadata_start();
    {
        metadata_set_lds_size(0x5800);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(64);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(32);
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

    s_shl_b32(gidz,s4,2);
    s_lda_b256(s4,argptr,0x00);
    v_and_b32(v1,ic(63),v0);
    v_and_b32(v3,ic(31),v0);
    v_shr_b32(v2,v0,6);
    v_shr_b32(v4,v0,5);
    v_shl_or_b32(v5,gidx,6,v1);
    v_shl_or_b32(v6,gidy,5,v3);
    v_shl_or_b32(tidx,gidx,8,v0);
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
    v_shl_b32(v6,v6,3);
    v_shl_add_u32(ao,v7,2,v5);
    v_shl_add_u32(bo,v8,2,v6);
    v_shl_add_u32(ao+1,lda,4,ao);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    ldg_b64(bpld,bbase,bo,0);

    //v3=lane&7
    //v4=lane>>3
    //asst=v0<<4
    //bsst=v0<<3
    //bsld=v4<<4
    //asld=(v2<< 8)|(v3<<4)
    //csst=(v2<<11)|(v4<<8)|(v3<<4)
    //csld=(v2<<11)|(v1<<2)
    //col=gidy<<6
    v_and_b32(v3,ic(7),v1);
    v_shr_b32(v4  ,v1, 3);
    v_shl_b32(v5  ,v3, 4);
    v_shl_b32(v6  ,v2,11);
    v_shl_b32(asst,v0, 4);
    v_shl_b32(bsst,v0, 3);
    v_shl_b32(bsld,v4, 4);
    v_shl_or_b32(v7,v4,8,v5);
    v_shl_or_b32(asld,v2,8,v5);
    v_shl_or_b32(csld,v1,2,v6);
    v_or_b32(csst,v6,v7);
    s_shl_b32(col,gidy,6);

    for( int i=0; i<64; ++i ){ v_mov_b32(((uint32_t*)&c[0][0])[i],zero); }
    s_sync(vmcnt(0)&lgkmcnt(0));
    lsst_b128(asst,0x0000,apld+0);
    lsst_b128(asst,0x1000,apld+4);
    lsst_b64(bsst,0x2000,bpld);
    s_sub_u32(k,k,ic(8));
    s_shl_b32(elda,lda,5);
    s_shl_b32(eldb,ldb,5);
    s_movk_i32(dbtr,0x3000);
    s_cmpk_u32(k,0,eq);
    s_cmovk_i32(elda,0);
    s_cmovk_i32(eldb,0);
    S_ADD_U64_U32(abase,abase,elda);
    S_ADD_U64_U32(bbase,bbase,eldb);
    s_sync(lgkmcnt(0));
    s_barrier();
    lsld_b128(a[0][0],asld,0x0000);
    lsld_b128(a[0][4],asld,0x0080);
    lsld_b128(b[0][0],bsld,0x2000);
    lsld_b128(b[0][4],bsld,0x2080);

__lable__(0); 
    lsld_b128(a[1][0],asld,0x0400);
    lsld_b128(b[1][0],bsld,0x2100);
    lsld_b128(a[1][4],asld,0x0480);
    lsld_b128(b[1][4],bsld,0x2180);
    v_xor_b32(asst,dbtr,asst);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    ldg_b128(apld+0,abase,ao+0,0);
    ldg_b128(apld+4,abase,ao+1,0);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    s_cmpk_u32(k,8,eq);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_cmovk_i32(elda,0);
    lsld_b128(a[0][0],asld,0x0800);
    lsld_b128(b[0][0],bsld,0x2200);
    lsld_b128(a[0][4],asld,0x0880);
    lsld_b128(b[0][4],bsld,0x2280);
    v_xor_b32(bsst,dbtr,bsst);
    s_sync(lgkmcnt(4));
    ldg_b64(bpld+0,bbase,bo,0);
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    lsld_b128(a[1][0],asld,0x0c00);
    lsld_b128(b[1][0],bsld,0x2300);
    lsld_b128(a[1][4],asld,0x0c80);
    lsld_b128(b[1][4],bsld,0x2380);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_cmovk_i32(eldb,0);
    lsld_b128(a[0][0],asld,0x1000);
    lsld_b128(b[0][0],bsld,0x2400);
    lsld_b128(a[0][4],asld,0x1080);
    lsld_b128(b[0][4],bsld,0x2480);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    s_add_u32(abase,abase,elda);    
    lsld_b128(a[1][0],asld,0x1400);
    lsld_b128(b[1][0],bsld,0x2500);
    lsld_b128(a[1][4],asld,0x1480);
    lsld_b128(b[1][4],bsld,0x2580);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_S(&c[3][4],&a[0][4],b[0][3]);
    V_OP4_S(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    V_OP4_S(&c[4][4],&a[0][4],b[0][4]);
    V_OP4_S(&c[5][4],&a[0][4],b[0][5]);
    V_OP4_S(&c[6][4],&a[0][4],b[0][6]);
    V_OP4_T(&c[7][4],&a[0][4],b[0][7]);
    s_addc_u32(abase+1,abase+1,zero);
    lsld_b128(a[0][0],asld,0x1800);
    lsld_b128(b[0][0],bsld,0x2600);
    lsld_b128(a[0][4],asld,0x1880);
    lsld_b128(b[0][4],bsld,0x2680);
    s_sync(lgkmcnt(4));
    V_OP4_R(&c[0][0],&a[1][0],b[1][0]);
    V_OP4_S(&c[1][0],&a[1][0],b[1][1]);
    V_OP4_S(&c[2][0],&a[1][0],b[1][2]);
    V_OP4_S(&c[3][0],&a[1][0],b[1][3]);
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    s_add_u32(bbase,bbase,eldb);  
    lsld_b128(a[1][0],asld,0x1c00);
    lsld_b128(b[1][0],bsld,0x2700);
    lsld_b128(a[1][4],asld,0x1c80);
    lsld_b128(b[1][4],bsld,0x2780);
    s_sync(lgkmcnt(5));
    V_OP4_R(&c[0][0],&a[0][0],b[0][0]);
    V_OP4_S(&c[1][0],&a[0][0],b[0][1]);
    V_OP4_S(&c[2][0],&a[0][0],b[0][2]);
    V_OP4_S(&c[3][0],&a[0][0],b[0][3]);
    s_addc_u32(bbase+1,bbase+1,zero);
    V_OP4_S(&c[0][4],&a[0][4],b[0][0]);
    V_OP4_S(&c[1][4],&a[0][4],b[0][1]);
    V_OP4_S(&c[2][4],&a[0][4],b[0][2]);
    V_OP4_T(&c[3][4],&a[0][4],b[0][3]);
    v_xor_b32(asld,dbtr,asld);
    s_sync(vmcnt(0)&lgkmcnt(4));
    lsst_b128(asst,0x0000,apld+0);
    lsst_b128(asst,0x1000,apld+4);
    lsst_b64(bsst,0x2000,bpld);
    v_xor_b32(bsld,dbtr,bsld);
    V_OP4_R(&c[4][0],&a[0][0],b[0][4]);
    V_OP4_S(&c[5][0],&a[0][0],b[0][5]);
    V_OP4_S(&c[6][0],&a[0][0],b[0][6]);
    V_OP4_S(&c[7][0],&a[0][0],b[0][7]);
    s_sub_u32(k,k,ic(8));
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
    V_OP4_S(&c[0][4],&a[1][4],b[1][0]);
    V_OP4_S(&c[1][4],&a[1][4],b[1][1]);
    V_OP4_S(&c[2][4],&a[1][4],b[1][2]);
    V_OP4_S(&c[3][4],&a[1][4],b[1][3]);
    V_OP4_S(&c[4][0],&a[1][0],b[1][4]);
    V_OP4_S(&c[5][0],&a[1][0],b[1][5]);
    V_OP4_S(&c[6][0],&a[1][0],b[1][6]);
    V_OP4_S(&c[7][0],&a[1][0],b[1][7]);
    V_OP4_S(&c[4][4],&a[1][4],b[1][4]);
    V_OP4_S(&c[5][4],&a[1][4],b[1][5]);
    V_OP4_S(&c[6][4],&a[1][4],b[1][6]);
    V_OP4_T(&c[7][4],&a[1][4],b[1][7]);
    s_cbra_scc0(0);

    ///cbase+=gidz*cbks+col*ldc
    ///co=tidx<<2
    s_lda_b32(alpha,argptr,0x2c);
    s_lda_b128(s0,argptr,0x30);
    v_shl_b32(co,tidx,2);
    v_cmp_u32(m,tidx,gt);
    s_mov_b64(s18,vcc);
    s_mov_b64(s16,exec);
    s_shl_b32(s8,col,2);
    s_mov_b32(s26,n);
    s_sync(lgkmcnt(0));
    S_MUL_U64_U32(s4,gidz,cbks);
    S_MUL_U64_U32(s6,s8,ldc);
    S_ADD_U64(cbase,cbase,s4);
    S_ADD_U64(cbase,cbase,s6);  
    s_shl_b32(s22,ldc,4);
    s_shl_b32(s23,ldc,2);
    s_mov_b64(s24,cbase);
    
    for( int i=0, ilab=1; i<8; ++i )
    {
        const int s=i&3;
        if(i>0){
            if(s!=0){
            __lable__(ilab); ++ilab;
                s_mov_b64(exec,s16);
                s_add_u32(col,col,ic(1));
            } else {
                s_mov_b64(exec,s16);
                s_shl_b32(s27,s23,5);
                s_add_u32(col,col,ic(29));
                S_ADD_U64_U32(s0,s24,s27);
            }
        }
        lsst_b128(csst,0x00,c[i][0]);
        lsst_b128(csst,0x80,c[i][4]);
        if(s==0){
            S_ADD_U64_U32(s2 ,s0 ,s22);
            S_ADD_U64_U32(s4 ,s2 ,s22);
            S_ADD_U64_U32(s6 ,s4 ,s22);
            S_ADD_U64_U32(s8 ,s6 ,s22);
            S_ADD_U64_U32(s10,s8 ,s22);
            S_ADD_U64_U32(s12,s10,s22);
            S_ADD_U64_U32(s14,s12,s22);
        } else {
            S_ADD_U64_U32(s0 ,s0 ,s23);
            S_ADD_U64_U32(s2 ,s2 ,s23);
            S_ADD_U64_U32(s4 ,s4 ,s23);
            S_ADD_U64_U32(s6 ,s6 ,s23);
            S_ADD_U64_U32(s8 ,s8 ,s23);
            S_ADD_U64_U32(s10,s10,s23);
            S_ADD_U64_U32(s12,s12,s23);
            S_ADD_U64_U32(s14,s14,s23);
        }
        s_mov_b64(exec,s18);
        s_sync(lgkmcnt(0));
        lsldx_b32x2(v0,csld,0,1);
        lsldx_b32x2(v2,csld,2,3);
        lsldx_b32x2(v4,csld,4,5);
        lsldx_b32x2(v6,csld,6,7);

        s_cmp_u32(col,s26,lt);
        s_cbra_scc0(7);
        s_sync(lgkmcnt(3));
        v_mul_f32(v0,alpha,v0);
        stg_b32(s0,co,0,v0);
    
        s_add_u32(s27,col,ic(4));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v1,alpha,v1);
        stg_b32(s2,co,0,v1);
    
        s_add_u32(s27,col,ic(8));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(2));
        v_mul_f32(v2,alpha,v2);
        stg_b32(s4,co,0,v2);
    
        s_add_u32(s27,col,ic(12));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v3,alpha,v3);
        stg_b32(s6,co,0,v3);

        s_add_u32(s27,col,ic(16));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(1));
        v_mul_f32(v4,alpha,v4);
        stg_b32(s8,co,0,v4);
    
        s_add_u32(s27,col,ic(20));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v5,alpha,v5);
        stg_b32(s10,co,0,v5);

        s_add_u32(s27,col,ic(24));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        s_sync(lgkmcnt(0));
        v_mul_f32(v6,alpha,v6);
        stg_b32(s12,co,0,v6);
    
        s_add_u32(s27,col,ic(28));
        s_cmp_u32(s27,s26,lt);
        s_cbra_scc0(s<3?ilab:7);
        v_mul_f32(v7,alpha,v7);
        stg_b32(s14,co,0,v7);
    }
__lable__(7);
    s_endp();
}