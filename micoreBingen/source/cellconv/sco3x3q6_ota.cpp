#include"../../include/gfxcoder.h"

/*
abase: 0x00
bks  : 0x08
lda  : 0x0c
grid : 0x10
amag : 0x18
bmag : 0x20
ldy  : 0x28, onx*ony
bgs  : 0x2c, onx*ony*gonc
bbase: 0x30
ldx  : 0x38, onx*ony*onc
nx   : 0x3c
ny   : 0x40
bs   : 0x44
*/

void gfxcoder::sco3x3q6_ota( uint32_t relu )
{
    uint32_t a[8][8], b[6][8], c[6][6], d_a[8], s_a[8], d_b[6], s_b[6];
    for( int i=0; i<64; ++i ){ ((uint32_t*)&a[0][0])[i]=v0+i; }
    for( int i=0; i<8; ++i ){
        b[0][i]=a[0][i];
        b[5][i]=a[7][i];
    }
    for( int i=0; i<8; ++i ){
        b[1][i]=v64+0*8+i;
        b[2][i]=v64+1*8+i;
        b[3][i]=v64+2*8+i;
        b[4][i]=v64+3*8+i;
    }
    for( int i=0; i<8; ++i ){
        d_a[i]=v96+0+i;
        s_a[i]=v96+8+i;
    }
    for( int i=0; i<6; ++i ){
        c[i][0]=b[i][0];
        c[i][5]=b[i][7];
    }
    for( int i=0; i<6; ++i ){
        c[i][1]=((uint32_t*)&a[3][0])[i*4+0];
        c[i][2]=((uint32_t*)&a[3][0])[i*4+1];
        c[i][3]=((uint32_t*)&a[3][0])[i*4+2];
        c[i][4]=((uint32_t*)&a[3][0])[i*4+3];
        d_b[i]=v96+0+i;
        s_b[i]=v96+6+i;
    }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s24;
    const uint32_t gidz  =s25;
    const uint32_t abase =s4 ;
    const uint32_t bks   =s6 ;
    const uint32_t lda   =s7 ;
    const uint32_t amag  =s4 ;
    const uint32_t bmag  =s6 ;
    const uint32_t ldy   =s8 ;
    const uint32_t bgs   =s9 ;
    const uint32_t bbase =s0 ;
    const uint32_t ldx   =s12;
    const uint32_t nx    =s13;
    const uint32_t grid  =s20;
    const uint32_t gridx =s20;
    const uint32_t gridy =s21;
    const uint32_t bs    =s22;
    const uint32_t ncells=s23;
    const uint32_t kcof0 =s12;
    const uint32_t kcof1 =s13;
    const uint32_t kcof2 =s14;

    const uint32_t lane =v112;
    const uint32_t tidx =v113;
    const uint32_t ao   =v64 ;
    const uint32_t bo   =v36 ;
    const uint32_t celly=v0  ;
    const uint32_t cellx=v1  ;
    const uint32_t batch=v2  ;
    const uint32_t cell =v3  ;
    const uint32_t sst  =v4  ;

    metadata_start();
    {
        metadata_set_lds_size(0x2d00);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(72);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(30);
        metadata_set_vgprcnt(114);
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
    s_shl_b32(gidy,s3,2);
    s_lda_b128(s4,argptr,0x0);
    v_shl_or_b32(tidx,gidx,6,v0);
    v_mov_b32(lane,v0);
    s_sync(lgkmcnt(0));

    s_lda_b64(s20,argptr,0x10);
    s_lda_b32(s22,argptr,0x44);
    S_MUL_U64_U32(s10,gidy,lda);
    S_MUL_U64_U32(s12,gidz,bks);
    S_ADD_U64(s8,s10,s12);
    s_shl_b32(s2,bks,5);
    s_shl_b32(s3,bks,2);
    v_shl_b32(ao,tidx,2);
    S_ADD_U64(abase,abase,s8);
    S_ADD_U64_U32(abase+1*2,abase+0*2,s2);
    S_ADD_U64_U32(abase+2*2,abase+1*2,s2);
    S_ADD_U64_U32(abase+3*2,abase+2*2,s2);
    S_ADD_U64_U32(abase+4*2,abase+3*2,s2);
    S_ADD_U64_U32(abase+5*2,abase+4*2,s2);
    S_ADD_U64_U32(abase+6*2,abase+5*2,s2);
    S_ADD_U64_U32(abase+7*2,abase+6*2,s2);
    s_sync(lgkmcnt(0));
    s_mul_i32(gridy,gridy,gridx);
    s_mul_i32(ncells,bs,gridy);
    v_add_u32(ao+1,s3,ao+0);
    v_add_u32(ao+2,s3,ao+1);
    v_add_u32(ao+3,s3,ao+2);
    v_add_u32(ao+4,s3,ao+3);
    v_add_u32(ao+5,s3,ao+4);
    v_add_u32(ao+6,s3,ao+5);
    v_add_u32(ao+7,s3,ao+6);
    v_cmp_u32(ncells,tidx,gt);
    s_andexec_b64(s2,vcc);
    for( int i=0; i<8; ++i ){
        ldg_b32(a[i][0],abase+i*2,ao+0,0x0);
        ldg_b32(a[i][1],abase+i*2,ao+1,0x0);
        ldg_b32(a[i][2],abase+i*2,ao+2,0x0);
        ldg_b32(a[i][3],abase+i*2,ao+3,0x0);
        ldg_b32(a[i][4],abase+i*2,ao+4,0x0);
        ldg_b32(a[i][5],abase+i*2,ao+5,0x0);
        ldg_b32(a[i][6],abase+i*2,ao+6,0x0);
        ldg_b32(a[i][7],abase+i*2,ao+7,0x0);
    }
    s_mov_b64(exec,s2);
    s_movk_b32(kcof0,float_as_uint(8.00000f));
    s_movk_b32(kcof1,float_as_uint(16.0000f));
    s_movk_b32(kcof2,float_as_uint(32.0000f));
    
    s_sync(vmcnt(40));
    for( int i=0; i<8; ++i ){
        v_sub_f32(b[1][i],a[1][i],a[2][i]);
        v_add_f32(b[2][i],a[1][i],a[2][i]);
    }
    s_sync(vmcnt(24));
    for( int i=0; i<8; ++i ){
        v_sub_f32(d_a[i],a[3][i],a[4][i]);
        v_add_f32(s_a[i],a[3][i],a[4][i]);
    }
    for( int i=0; i<8; ++i ){ v_add_f32(b[0][i],a[0][i],b[2][i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(b[0][i],b[0][i],s_a[i] ); }
    for( int i=0; i<8; ++i ){ v_fma_f32(b[3][i],kcof0,d_a[i],b[1][i]); }
    for( int i=0; i<8; ++i ){ v_fma_f32(b[4][i],kcof1,s_a[i],b[2][i]); }
    s_sync(vmcnt(0));
    for( int i=0; i<8; ++i ){ v_add_f32(b[5][i],b[1][i],a[7][i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[1][i],f2   ,d_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[2][i],f4   ,s_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[5][i],kcof2,d_a[i]); }
    for( int i=0; i<8; ++i ){
        v_sub_f32(d_a[i],a[5][i],a[6][i]);
        v_add_f32(s_a[i],a[5][i],a[6][i]);
    }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[0][i],kcof2,s_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[1][i],kcof1,d_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[2][i],kcof0,s_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[3][i],f4   ,d_a[i]); }
    for( int i=0; i<8; ++i ){ V_MAC_F32(b[4][i],f2   ,s_a[i]); }
    for( int i=0; i<8; ++i ){ v_add_f32(b[5][i],b[5][i],d_a[i]); }

    //=========================================================================================
    s_lda_b64(s4,argptr,0x18);
    s_lda_b64(s6,argptr,0x20);
    s_lda_b64(s8,argptr,0x28);
    //=========================================================================================

    for( int i=0; i<6; ++i ){
        v_sub_f32(c[i][1],b[i][1],b[i][2]);
        v_add_f32(c[i][2],b[i][1],b[i][2]);
    }
    for( int i=0; i<6; ++i ){
        v_sub_f32(d_b[i],b[i][3],b[i][4]);
        v_add_f32(s_b[i],b[i][3],b[i][4]);
    }
    for( int i=0; i<6; ++i ){ v_add_f32(c[i][0],b[i][0],c[i][2]); }
    for( int i=0; i<6; ++i ){ v_add_f32(c[i][0],c[i][0],s_b[i] ); }
    for( int i=0; i<6; ++i ){ v_fma_f32(c[i][3],kcof0,d_b[i],c[i][1]); }
    for( int i=0; i<6; ++i ){ v_fma_f32(c[i][4],kcof1,s_b[i],c[i][2]); }

    for( int i=0; i<6; ++i ){ v_add_f32(c[i][5],c[i][1],b[i][7]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][1],f2   ,d_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][2],f4   ,s_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][5],kcof2,d_b[i]); }
    for( int i=0; i<6; ++i ){
        v_sub_f32(d_b[i],b[i][5],b[i][6]);
        v_add_f32(s_b[i],b[i][5],b[i][6]);
    }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][0],kcof2,s_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][1],kcof1,d_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][2],kcof0,s_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][3],f4   ,d_b[i]); }
    for( int i=0; i<6; ++i ){ V_MAC_F32(c[i][4],f2   ,s_b[i]); }
    for( int i=0; i<6; ++i ){ v_add_f32(c[i][5],c[i][5],d_b[i]); }

    //=========================================================================================

    v_mul_u24(v96,ic(28),lane);
    s_movk_i32(s2,0x700);
    v_add_u32(v96+1,s2,v96+0);
    v_add_u32(v96+2,s2,v96+1);
    v_add_u32(v96+3,s2,v96+2);
    v_add_u32(v96+4,s2,v96+3);
    v_add_u32(v96+5,s2,v96+4);
    if(relu){
        v_max_f32(c[0][0],zero,c[0][0]);
        v_max_f32(c[0][1],zero,c[0][1]);
        v_max_f32(c[0][2],zero,c[0][2]);
        v_max_f32(c[0][3],zero,c[0][3]);
        v_max_f32(c[0][4],zero,c[0][4]);
        v_max_f32(c[0][5],zero,c[0][5]);
    }
    for( int i=0; i<6; ++i ){
        lsst_b32x2(v96+i,0,c[i][0],1,c[i][1]);
        lsst_b32x2(v96+i,2,c[i][2],3,c[i][3]);
        lsst_b32x2(v96+i,4,c[i][4],5,c[i][5]);
        if(relu&&(i<5)){
            v_max_f32(c[i+1][0],zero,c[i+1][0]);
            v_max_f32(c[i+1][1],zero,c[i+1][1]);
            v_max_f32(c[i+1][2],zero,c[i+1][2]);
            v_max_f32(c[i+1][3],zero,c[i+1][3]);
            v_max_f32(c[i+1][4],zero,c[i+1][4]);
            v_max_f32(c[i+1][5],zero,c[i+1][5]);
        }
    }
    s_sync(lgkmcnt(0));
    s_lda_b128(s0,argptr,0x30);
    V_MDM_U32(batch,tidx,gridy,amag);
    V_MDM_U32(celly,cell,gridx,bmag);
    v_mul_u24(sst,ic(12),lane);
    s_movk_i32(s15,0xab);
    lsst_b96(sst,0x2a00,celly);
    V_MDMX_U32(v42,lane,ic(6),s15,ic(10)); v_add_u32(lane,ic(64),lane);
    V_MDMX_U32(v44,lane,ic(6),s15,ic(10)); v_add_u32(lane,ic(64),lane);
    V_MDMX_U32(v46,lane,ic(6),s15,ic(10)); v_add_u32(lane,ic(64),lane);
    V_MDMX_U32(v48,lane,ic(6),s15,ic(10)); v_add_u32(lane,ic(64),lane);
    V_MDMX_U32(v50,lane,ic(6),s15,ic(10)); v_add_u32(lane,ic(64),lane);
    V_MDMX_U32(v52,lane,ic(6),s15,ic(10));
    v_mul_u24(v54,ic(12),v42);
    v_mul_u24(v55,ic(12),v44);
    v_mul_u24(v56,ic(12),v46);
    v_mul_u24(v57,ic(12),v48);
    v_mul_u24(v58,ic(12),v50);
    v_mul_u24(v59,ic(12),v52);
    s_sync(lgkmcnt(0));
    s_mov_b64(s12,s2);
    lsld_b96(v60,v54,0x2a00);
    lsld_b96(v63,v55,0x2a00);
    lsld_b96(v66,v56,0x2a00);
    lsld_b96(v69,v57,0x2a00);
    lsld_b96(v72,v58,0x2a00);
    lsld_b96(v75,v59,0x2a00);
    S_MUL_U64_U32(s16,gidy,ldy);
    S_MUL_U64_U32(s18,gidz,bgs);
    S_ADD_U64(bbase,bbase,s16);
    S_ADD_U64(bbase,bbase,s18);
    s_shl_b32(s15,nx,2);
    S_ADD_U64_U32(bbase+1*2,bbase+0*2,s15);
    S_ADD_U64_U32(bbase+2*2,bbase+1*2,s15);
    S_ADD_U64_U32(bbase+3*2,bbase+2*2,s15);
    S_ADD_U64_U32(bbase+4*2,bbase+3*2,s15);
    S_ADD_U64_U32(bbase+5*2,bbase+4*2,s15);

    for( int i=0; i<6; ++i ){
        s_sync(lgkmcnt(5-i));
        v_mul_lo_u32(v86,ldx,v62+i*3);
        v_mad_u24(v87,ic(7),v42+i*2,v43+i*2);
        v_shl_b32(v78+i,v87,2);
        v_mul_u24(v88,ic(6),v60+i*3);
        v_mad_u24(v89,ic(6),v61+i*3,v43+i*2);
        v_mad_u24(v87,nx,v88,v89);
        v_add_shl_u32(bo+i,v86,v87,2);
    }
    for( int i=0; i<6; ++i ){
        lsldx_b32x2(v0+i*6,v78+i,0*7,1*7);
        lsldx_b32x2(v2+i*6,v78+i,2*7,3*7);
        lsldx_b32x2(v4+i*6,v78+i,4*7,5*7);
    }
    s_mov_b64(s12,exec);
    for( int i=0; i<6; ++i ){
        v_cmpx_u32(bs,v62+i*3,gt);
        s_sync(lgkmcnt(15-i*3));
        stg_b32(bbase+0*2,bo+i,0x0,v0+i*6);
        stg_b32(bbase+1*2,bo+i,0x0,v1+i*6);
        stg_b32(bbase+2*2,bo+i,0x0,v2+i*6);
        stg_b32(bbase+3*2,bo+i,0x0,v3+i*6);
        stg_b32(bbase+4*2,bo+i,0x0,v4+i*6);
        stg_b32(bbase+5*2,bo+i,0x0,v5+i*6);
        if(i<5){ s_mov_b64(exec,s12); }
    }
    s_endp();
}