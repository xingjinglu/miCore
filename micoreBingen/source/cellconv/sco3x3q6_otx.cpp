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

/*
==========================================================================================
for( int i=0; i<6; i++ ){
    sdata[0*448+lane*7+0]=c[i][0];
    sdata[1*448+lane*7+1]=c[i][1];
    sdata[2*448+lane*7+2]=c[i][2];
    sdata[3*448+lane*7+3]=c[i][3];
    sdata[4*448+lane*7+4]=c[i][4];
    sdata[5*448+lane*7+5]=c[i][5];
}
==========================================================================================
bbase+=gidz*bgs+gidy*yldb
bo=batch*xldb+y*nx+x
batch=tidx/(grid_x*grid_y)
lcell=tidx%(grid_x*grid_y)
cellx=lcell%grid_x
celly=lcell/grid_y
sidx[lane*3+0]=batch
sidx[lane*3+1]=cellx
sidx[lane*3+2]=celly
==========================================================================================
for( int i=0; i<6; ++i ){
    u=(i*64+lane)%6
    v=(i*64+lane)/6
    {celly,cellx,batch}=sidx[v]
    x=cellx*6+u
    y=celly*6
    if((batch<bs)&&(x<nx)){
        if((y+0)<ny){ out[batch*xldb+y*nx+x]=sdata[0*448+v*7+u] }
        if((y+1)<ny){ out[batch*xldb+y*nx+x]=sdata[1*448+v*7+u] }
        if((y+2)<ny){ out[batch*xldb+y*nx+x]=sdata[2*448+v*7+u] }
        if((y+3)<ny){ out[batch*xldb+y*nx+x]=sdata[3*448+v*7+u] }
        if((y+4)<ny){ out[batch*xldb+y*nx+x]=sdata[4*448+v*7+u] }
        if((y+5)<ny){ out[batch*xldb+y*nx+x]=sdata[5*448+v*7+u] }
    }
}
*/

void gfxcoder::sco3x3q6_otx( uint32_t relu )
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
    const uint32_t gidy  =s35;
    const uint32_t gidz  =s36;
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
    const uint32_t ny    =s14;
    const uint32_t grid  =s32;
    const uint32_t gridx =s32;
    const uint32_t gridy =s33;
    const uint32_t bs    =s34;
    const uint32_t ncells=s20;
    const uint32_t kcof0 =s12;
    const uint32_t kcof1 =s13;
    const uint32_t kcof2 =s14;

    const uint32_t lane =v112;
    const uint32_t tidx =v113;
    const uint32_t ao   =v64 ;
    const uint32_t v    =v36 ;
    const uint32_t u    =v37 ;
    const uint32_t celly=v38 ;
    const uint32_t cellx=v39 ;
    const uint32_t batch=v40 ;
    const uint32_t cell =v41 ;
    const uint32_t x    =v42 ;
    const uint32_t y    =v43 ;
    const uint32_t bo   =v44 ;
    const uint32_t spy  =v45 ;
    const uint32_t spx  =v46 ;

    metadata_start();
    {
        metadata_set_lds_size(0x2d00);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(72);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(41);
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
    
    //abase+=gidz*bks*64+gidy*lda+tidx
    s_lda_b64(s32,argptr,0x10);
    s_lda_b32(s34,argptr,0x44);
    S_MUL_U64_U32(s10,gidy,lda);
    S_MUL_U64_U32(s12,gidz,bks);
    s_shl_b32(s2,bks,5);
    s_shl_b32(s3,bks,2);
    S_ADD_U64(s8,s10,s12);
    S_ADD_U64(abase,abase,s8);
    S_ADD_U64_U32(abase+1*2,abase+0*2,s2);
    S_ADD_U64_U32(abase+2*2,abase+1*2,s2);
    S_ADD_U64_U32(abase+3*2,abase+2*2,s2);
    S_ADD_U64_U32(abase+4*2,abase+3*2,s2);
    S_ADD_U64_U32(abase+5*2,abase+4*2,s2);
    S_ADD_U64_U32(abase+6*2,abase+5*2,s2);
    S_ADD_U64_U32(abase+7*2,abase+6*2,s2);
    v_shl_b32(ao,tidx,2);
    s_sync(lgkmcnt(0));
    s_mul_i32(gridy,gridy,gridx);
    s_mul_i32(ncells,gridy,bs);
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

    s_movk_i32(s2,0x700);
    v_mul_u24(v96,ic(28),lane);
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
    s_lda_b32(ny,argptr,0x40);
    s_lda_b128(s0,argptr,0x30);
    v_mul_u24(spy,ic(12),lane);
    V_MDM_U32(batch,tidx,gridy,amag);
    V_MDM_U32(celly,cell,gridx,bmag);
    lsst_b96(spy,0x2a00,celly);
    s_movk_i32(s15,0xab);
    S_MUL_U64_U32(s10,gidy,ldy);
    S_MUL_U64_U32(s16,gidz,bgs);
    S_ADD_U64(s10,s10,s16);
    V_MDMX_U32(v,lane,ic(6),s15,ic(10));
    v_mad_u24(v47,ic(7),v,u);
    v_mul_u24(spy,ic(12),v);
    v_shl_b32(spx,v47,2);
    s_sync(lgkmcnt(0));
    lsld_b96(celly,spy,0x2a00);
    lsldx_b32x2(v0,spx,0*7,1*7);
    lsldx_b32x2(v2,spx,2*7,3*7);
    lsldx_b32x2(v4,spx,4*7,5*7);
    s_mov_b64(s12,s2);
    s_shl_b32(s16,s3,2);
    S_ADD_U64(bbase,bbase,s10);
    S_ADD_U64_U32(bbase+1*2,bbase+0*2,s16);
    S_ADD_U64_U32(bbase+2*2,bbase+1*2,s16);
    S_ADD_U64_U32(bbase+3*2,bbase+2*2,s16);
    S_ADD_U64_U32(bbase+4*2,bbase+3*2,s16);
    S_ADD_U64_U32(bbase+5*2,bbase+4*2,s16);
    s_mov_b64(s30,exec);
    s_sync(lgkmcnt(3));
    v_mul_lo_u32(v47,ldx,batch);
    v_mul_u24(y,ic(6),celly);
    v_mad_u24(x,ic(6),cellx,u);
    v_mad_u24(v48,nx,y,x);
    v_sub_i32(y,ny,y);
    v_add_shl_u32(bo,v47,v48,2);
    v_cmp_u32(s16,nx,x,gt);
    v_cmp_u32(bs,batch,gt);
    s_and_b64(s16,s16,vcc);
    v_cmp_i32(s18,y,ic(0),gt);
    v_cmp_i32(s20,y,ic(1),gt);
    v_cmp_i32(s22,y,ic(2),gt);
    v_cmp_i32(s24,y,ic(3),gt);
    v_cmp_i32(s26,y,ic(4),gt);
    v_cmp_i32(s28,y,ic(5),gt);

    for( int i=0; i<6; ++i )
    {
        s_sync(lgkmcnt(0));
        s_and_b64(exec,s16,s18); stg_b32(bbase+0*2,bo,0x0,v0+i*6);
        s_and_b64(exec,s16,s20); stg_b32(bbase+1*2,bo,0x0,v1+i*6);
        s_and_b64(exec,s16,s22); stg_b32(bbase+2*2,bo,0x0,v2+i*6);
        s_and_b64(exec,s16,s24); stg_b32(bbase+3*2,bo,0x0,v3+i*6);
        s_and_b64(exec,s16,s26); stg_b32(bbase+4*2,bo,0x0,v4+i*6);
        s_and_b64(exec,s16,s28); stg_b32(bbase+5*2,bo,0x0,v5+i*6);
        if(i<5){
            s_mov_b64(exec,s30);
            v_add_u32(lane,ic(64),lane);
            V_MDMX_U32(v,lane,ic(6),s15,ic(10));
            v_mul_u24(spy,ic(12),v);
            lsld_b96(celly,spy,0x2a00);
            v_mad_u24(v47,ic(7),v,u);
            v_shl_b32(spx,v47,2);
            lsldx_b32x2(v0+(i+1)*6,spx,0*7,1*7);
            lsldx_b32x2(v2+(i+1)*6,spx,2*7,3*7);
            lsldx_b32x2(v4+(i+1)*6,spx,4*7,5*7);
            s_sync(lgkmcnt(3));
            v_mul_lo_u32(v47,ldx,batch);
            v_mul_u24(y,ic(6),celly);
            v_mad_u24(x,ic(6),cellx,u);
            v_mad_u24(v48,nx,y,x);
            v_sub_i32(y,ny,y);
            v_add_shl_u32(bo,v47,v48,2);
            v_cmp_u32(s16,nx,x,gt);
            v_cmp_u32(bs,batch,gt);
            s_and_b64(s16,s16,vcc);
            v_cmp_i32(s18,y,ic(0),gt);
            v_cmp_i32(s20,y,ic(1),gt);
            v_cmp_i32(s22,y,ic(2),gt);
            v_cmp_i32(s24,y,ic(3),gt);
            v_cmp_i32(s26,y,ic(4),gt);
            v_cmp_i32(s28,y,ic(5),gt);
        }
    }
    s_endp();
}