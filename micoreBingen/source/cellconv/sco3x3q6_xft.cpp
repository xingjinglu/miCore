#include"../../include/gfxcoder.h"

/*
bbase
bks
ldb
abase
inc
onc
lda
*/

void gfxcoder::sco3x3q6_xft( uint32_t flip )
{
    uint32_t c[8][8], a[3][3], b[8][3];
    for( int i=0; i<64; ++i ){ ((uint32_t*)&c[0][0])[i]=v0+i; }
    for( int i=0; i<8; ++i ){ b[i][0]=v0+i*8; b[i][1]=v64+i; b[i][2]=v7+i*8; }
    a[0][0]=b[0][0];
    a[0][1]=b[0][1];
    a[0][2]=b[0][2];
    a[2][0]=b[7][0];
    a[2][1]=b[7][1];
    a[2][2]=b[7][2];
    a[1][0]=v72;
    a[1][1]=v73;
    a[1][2]=v74;

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s9 ;
    const uint32_t gidy  =s10;
    const uint32_t gidz  =s11;
    const uint32_t bbase =s0 ;
    const uint32_t bks   =s2 ;
    const uint32_t ldb   =s3 ;
    const uint32_t abase =s4 ;
    const uint32_t inc   =s6 ;
    const uint32_t onc   =s7 ;
    const uint32_t lda   =s8 ;
    const uint32_t kcof0 =s18;
    const uint32_t kcof1 =s19;
    const uint32_t kcof2 =s20;
    const uint32_t kcof3 =s21;
    const uint32_t kcof4 =s22;
    const uint32_t kcof5 =s23;
    const uint32_t kcof6 =s24;
    const uint32_t kcof7 =s25;

    const uint32_t ao  =v75;
    const uint32_t bo  =v75;
    const uint32_t tidx=v76;

    metadata_start();
    {
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(36);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(30);
        metadata_set_vgprcnt(83);
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

    s_lda_b32(lda,argptr,0x20);
    s_shl_b32(gidz,s4,2);
    s_shl_b32(gidy,flip?s3:s2,2);
    s_mov_b32(gidx,flip?s2:s3);
    s_lda_b256(s0,argptr,0x0);
    v_shl_or_b32(tidx,gidx,6,v0);
    s_sync(lgkmcnt(0));

    v_cmp_u32(onc,tidx,gt);
    v_cmov_b32(ao,zero,tidx);
    s_mov_b64(s16,vcc);
    if(flip==0){
        //abase+=(gidz*inc+gidy)*9
        //ao=tidx*lda
        s_mul_i32(s12,gidz,inc);
        s_shl_b32(lda,lda,2);
        s_add_u32(s13,s12,gidy);
        v_mul_lo_u32(ao,lda,ao);
        s_shl3_add_u32(s14,s13,s13);
        S_ADD_U64_U32(abase,abase,s14);
        ldg_b32(a[0][0],abase,ao,0x00);
        ldg_b32(a[0][1],abase,ao,0x04);
        ldg_b32(a[0][2],abase,ao,0x08);
        ldg_b32(a[2][0],abase,ao,0x18);
        ldg_b32(a[2][1],abase,ao,0x1c);
        ldg_b32(a[2][2],abase,ao,0x20);
        ldg_b32(a[1][0],abase,ao,0x0c);
        ldg_b32(a[1][1],abase,ao,0x10);
        ldg_b32(a[1][2],abase,ao,0x14);
    } else {
        //abase+=gidz*inc*9+gidy*lda
        //ao=tidx*9
        s_mul_i32(s12,gidz,inc);
        s_mul_i32(s13,gidy,lda);
        v_mul_lo_u32(ao,ic(36),ao);
        s_shl3_add_u32(s14,s12,s12);
        s_add_u32(s15,s13,s14);
        S_ADD_U64_U32(abase,abase,s15);
        ldg_b32(a[2][2],abase,ao,0x00);
        ldg_b32(a[2][1],abase,ao,0x04);
        ldg_b32(a[2][0],abase,ao,0x08);
        ldg_b32(a[0][2],abase,ao,0x18);
        ldg_b32(a[0][1],abase,ao,0x1c);
        ldg_b32(a[0][0],abase,ao,0x20);
        ldg_b32(a[1][2],abase,ao,0x0c);
        ldg_b32(a[1][1],abase,ao,0x10);
        ldg_b32(a[1][0],abase,ao,0x14);
    }
    //bbase+=gidz*64*bks+gidy*ldb
    //bo=gidx*64+tid
    s_shl_b32(s18,bks,5);
    s_shl_b32(s19,bks,2);
    s_shl_b32(bks,bks,6);
    S_MUL_U64_U32(s4,gidy,ldb);
    S_MUL_U64_U32(s6,gidz,bks);
    S_ADD_U64(bbase,bbase,s4);
    S_ADD_U64(bbase,bbase,s6);
    S_ADD_U64_U32(bbase+1*2,bbase+0*2,s18);
    S_ADD_U64_U32(bbase+2*2,bbase+1*2,s18);
    S_ADD_U64_U32(bbase+3*2,bbase+2*2,s18);
    S_ADD_U64_U32(bbase+4*2,bbase+3*2,s18);
    S_ADD_U64_U32(bbase+5*2,bbase+4*2,s18);
    S_ADD_U64_U32(bbase+6*2,bbase+5*2,s18);
    S_ADD_U64_U32(bbase+7*2,bbase+6*2,s18);
    v_shl_b32(bo,tidx,2);
    v_add_u32(bo+1,s19,bo+0);
    v_add_u32(bo+2,s19,bo+1);
    v_add_u32(bo+3,s19,bo+2);
    v_add_u32(bo+4,s19,bo+3);
    v_add_u32(bo+5,s19,bo+4);
    v_add_u32(bo+6,s19,bo+5);
    v_add_u32(bo+7,s19,bo+6);
    s_movk_b32(kcof0,float_as_uint( 2.f/  9.f));
    s_movk_b32(kcof1,float_as_uint(-2.f/  9.f));
    s_movk_b32(kcof2,float_as_uint( 1.f/ 45.f));
    s_movk_b32(kcof3,float_as_uint(-1.f/ 45.f));
    s_movk_b32(kcof4,float_as_uint( 1.f/ 90.f));
    s_movk_b32(kcof5,float_as_uint(-1.f/ 90.f));
    s_movk_b32(kcof6,float_as_uint( 2.f/ 45.f));
    s_movk_b32(kcof7,float_as_uint( 1.f/180.f));

    s_sync(vmcnt(3));
    v_add_f32(b[1][0],a[0][0],a[2][0]);
    v_add_f32(b[1][1],a[0][1],a[2][1]);
    v_add_f32(b[1][2],a[0][2],a[2][2]);
    v_mul_f32(b[1][0],kcof1,b[1][0]);
    v_mul_f32(b[1][1],kcof1,b[1][1]);
    v_mul_f32(b[1][2],kcof1,b[1][2]);
    v_mul_f32(b[3][0],kcof4,a[0][0]);
    v_mul_f32(b[3][1],kcof4,a[0][1]);
    v_mul_f32(b[3][2],kcof4,a[0][2]);
    v_mul_f32(b[5][0],kcof2,a[0][0]);
    v_mul_f32(b[5][1],kcof2,a[0][1]);
    v_mul_f32(b[5][2],kcof2,a[0][2]);
    V_MAC_F32(b[3][0],kcof6,a[2][0]);
    V_MAC_F32(b[3][1],kcof6,a[2][1]);
    V_MAC_F32(b[3][2],kcof6,a[2][2]);
    V_MAC_F32(b[5][0],kcof7,a[2][0]);
    V_MAC_F32(b[5][1],kcof7,a[2][1]);
    V_MAC_F32(b[5][2],kcof7,a[2][2]);
    s_sync(vmcnt(0));
    v_fma_f32(b[2][0],kcof0,a[1][0],b[1][0]);
    v_fma_f32(b[2][1],kcof0,a[1][1],b[1][1]);
    v_fma_f32(b[2][2],kcof0,a[1][2],b[1][2]);
    V_MAC_F32(b[1][0],kcof1,a[1][0]);
    V_MAC_F32(b[1][1],kcof1,a[1][1]);
    V_MAC_F32(b[1][2],kcof1,a[1][2]);
    v_fma_f32(b[4][0],kcof3,a[1][0],b[3][0]);
    v_fma_f32(b[4][1],kcof3,a[1][1],b[3][1]);
    v_fma_f32(b[4][2],kcof3,a[1][2],b[3][2]);
    V_MAC_F32(b[3][0],kcof2,a[1][0]);
    V_MAC_F32(b[3][1],kcof2,a[1][1]);
    V_MAC_F32(b[3][2],kcof2,a[1][2]);
    v_fma_f32(b[6][0],kcof5,a[1][0],b[5][0]);
    v_fma_f32(b[6][1],kcof5,a[1][1],b[5][1]);
    v_fma_f32(b[6][2],kcof5,a[1][2],b[5][2]);
    V_MAC_F32(b[5][0],kcof4,a[1][0]);
    V_MAC_F32(b[5][1],kcof4,a[1][1]);
    V_MAC_F32(b[5][2],kcof4,a[1][2]);

    //===========================================================

    v_add_f32(c[0][1],b[0][0],b[0][2]);
    v_add_f32(c[1][1],b[1][0],b[1][2]);
    v_add_f32(c[2][1],b[2][0],b[2][2]);
    v_add_f32(c[3][1],b[3][0],b[3][2]);
    v_add_f32(c[4][1],b[4][0],b[4][2]);
    v_add_f32(c[5][1],b[5][0],b[5][2]);
    v_add_f32(c[6][1],b[6][0],b[6][2]);
    v_add_f32(c[7][1],b[7][0],b[7][2]);
    v_mul_f32(c[0][1],kcof1,c[0][1]);
    v_mul_f32(c[1][1],kcof1,c[1][1]);
    v_mul_f32(c[2][1],kcof1,c[2][1]);
    v_mul_f32(c[3][1],kcof1,c[3][1]);
    v_mul_f32(c[4][1],kcof1,c[4][1]);
    v_mul_f32(c[5][1],kcof1,c[5][1]);
    v_mul_f32(c[6][1],kcof1,c[6][1]);
    v_mul_f32(c[7][1],kcof1,c[7][1]);
    v_fma_f32(c[0][2],kcof0,b[0][1],c[0][1]);
    v_fma_f32(c[1][2],kcof0,b[1][1],c[1][1]);
    v_fma_f32(c[2][2],kcof0,b[2][1],c[2][1]);
    v_fma_f32(c[3][2],kcof0,b[3][1],c[3][1]);
    v_fma_f32(c[4][2],kcof0,b[4][1],c[4][1]);
    v_fma_f32(c[5][2],kcof0,b[5][1],c[5][1]);
    v_fma_f32(c[6][2],kcof0,b[6][1],c[6][1]);
    v_fma_f32(c[7][2],kcof0,b[7][1],c[7][1]);
    V_MAC_F32(c[0][1],kcof1,b[0][1]);
    V_MAC_F32(c[1][1],kcof1,b[1][1]);
    V_MAC_F32(c[2][1],kcof1,b[2][1]);
    V_MAC_F32(c[3][1],kcof1,b[3][1]);
    V_MAC_F32(c[4][1],kcof1,b[4][1]);
    V_MAC_F32(c[5][1],kcof1,b[5][1]);
    V_MAC_F32(c[6][1],kcof1,b[6][1]);
    V_MAC_F32(c[7][1],kcof1,b[7][1]);

    v_mul_f32(c[0][3],kcof4,b[0][0]);
    v_mul_f32(c[1][3],kcof4,b[1][0]);
    v_mul_f32(c[2][3],kcof4,b[2][0]);
    v_mul_f32(c[3][3],kcof4,b[3][0]);
    v_mul_f32(c[4][3],kcof4,b[4][0]);
    v_mul_f32(c[5][3],kcof4,b[5][0]);
    v_mul_f32(c[6][3],kcof4,b[6][0]);
    v_mul_f32(c[7][3],kcof4,b[7][0]);
    V_MAC_F32(c[0][3],kcof6,b[0][2]);
    V_MAC_F32(c[1][3],kcof6,b[1][2]);
    V_MAC_F32(c[2][3],kcof6,b[2][2]);
    V_MAC_F32(c[3][3],kcof6,b[3][2]);
    V_MAC_F32(c[4][3],kcof6,b[4][2]);
    V_MAC_F32(c[5][3],kcof6,b[5][2]);
    V_MAC_F32(c[6][3],kcof6,b[6][2]);
    V_MAC_F32(c[7][3],kcof6,b[7][2]);
    v_fma_f32(c[0][4],kcof3,b[0][1],c[0][3]);
    v_fma_f32(c[1][4],kcof3,b[1][1],c[1][3]);
    v_fma_f32(c[2][4],kcof3,b[2][1],c[2][3]);
    v_fma_f32(c[3][4],kcof3,b[3][1],c[3][3]);
    v_fma_f32(c[4][4],kcof3,b[4][1],c[4][3]);
    v_fma_f32(c[5][4],kcof3,b[5][1],c[5][3]);
    v_fma_f32(c[6][4],kcof3,b[6][1],c[6][3]);
    v_fma_f32(c[7][4],kcof3,b[7][1],c[7][3]);
    V_MAC_F32(c[0][3],kcof2,b[0][1]);
    V_MAC_F32(c[1][3],kcof2,b[1][1]);
    V_MAC_F32(c[2][3],kcof2,b[2][1]);
    V_MAC_F32(c[3][3],kcof2,b[3][1]);
    V_MAC_F32(c[4][3],kcof2,b[4][1]);
    V_MAC_F32(c[5][3],kcof2,b[5][1]);
    V_MAC_F32(c[6][3],kcof2,b[6][1]);
    V_MAC_F32(c[7][3],kcof2,b[7][1]);

    v_mul_f32(c[0][5],kcof2,b[0][0]);
    v_mul_f32(c[1][5],kcof2,b[1][0]);
    v_mul_f32(c[2][5],kcof2,b[2][0]);
    v_mul_f32(c[3][5],kcof2,b[3][0]);
    v_mul_f32(c[4][5],kcof2,b[4][0]);
    v_mul_f32(c[5][5],kcof2,b[5][0]);
    v_mul_f32(c[6][5],kcof2,b[6][0]);
    v_mul_f32(c[7][5],kcof2,b[7][0]);
    V_MAC_F32(c[0][5],kcof7,b[0][2]);
    V_MAC_F32(c[1][5],kcof7,b[1][2]);
    V_MAC_F32(c[2][5],kcof7,b[2][2]);
    V_MAC_F32(c[3][5],kcof7,b[3][2]);
    V_MAC_F32(c[4][5],kcof7,b[4][2]);
    V_MAC_F32(c[5][5],kcof7,b[5][2]);
    V_MAC_F32(c[6][5],kcof7,b[6][2]);
    V_MAC_F32(c[7][5],kcof7,b[7][2]);
    v_fma_f32(c[0][6],kcof5,b[0][1],c[0][5]);
    v_fma_f32(c[1][6],kcof5,b[1][1],c[1][5]);
    v_fma_f32(c[2][6],kcof5,b[2][1],c[2][5]);
    v_fma_f32(c[3][6],kcof5,b[3][1],c[3][5]);
    v_fma_f32(c[4][6],kcof5,b[4][1],c[4][5]);
    v_fma_f32(c[5][6],kcof5,b[5][1],c[5][5]);
    v_fma_f32(c[6][6],kcof5,b[6][1],c[6][5]);
    v_fma_f32(c[7][6],kcof5,b[7][1],c[7][5]);
    V_MAC_F32(c[0][5],kcof4,b[0][1]);
    V_MAC_F32(c[1][5],kcof4,b[1][1]);
    V_MAC_F32(c[2][5],kcof4,b[2][1]);
    V_MAC_F32(c[3][5],kcof4,b[3][1]);
    V_MAC_F32(c[4][5],kcof4,b[4][1]);
    V_MAC_F32(c[5][5],kcof4,b[5][1]);
    V_MAC_F32(c[6][5],kcof4,b[6][1]);
    V_MAC_F32(c[7][5],kcof4,b[7][1]);

    s_mov_b64(exec,s16);
    for( int i=0; i<8; ++i ){
        stg_b32(bbase+i*2,bo+0,0x0,c[i][0]);
        stg_b32(bbase+i*2,bo+1,0x0,c[i][1]);
        stg_b32(bbase+i*2,bo+2,0x0,c[i][2]);
        stg_b32(bbase+i*2,bo+3,0x0,c[i][3]);
        stg_b32(bbase+i*2,bo+4,0x0,c[i][4]);
        stg_b32(bbase+i*2,bo+5,0x0,c[i][5]);
        stg_b32(bbase+i*2,bo+6,0x0,c[i][6]);
        stg_b32(bbase+i*2,bo+7,0x0,c[i][7]);
    }
    s_endp();
}