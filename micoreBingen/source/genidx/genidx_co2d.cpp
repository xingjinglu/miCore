#include"../../include/gfxcoder.h"

/*
base  : 0x00
amaps : 0x08
anx   : 0x0c
sd    : 0x10
lda   : 0x14
onc   : 0x18
m     : 0x1c
cnx   : 0x20
cny   : 0x24
bnx   : 0x28
bny   : 0x2c
ldb   : 0x30
srelo : 0x34
*/

void gfxcoder::genidx_co2d()
{
    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t cnx   =s2 ;
    const uint32_t cny   =s3 ;
    const uint32_t base  =s4 ;
    const uint32_t amaps =s6 ;
    const uint32_t anx   =s7 ;
    const uint32_t sd    =s8 ;
    const uint32_t lda   =s9 ;
    const uint32_t onc   =s10;
    const uint32_t m     =s11;
    const uint32_t bnx   =s18;
    const uint32_t bny   =s19;
    const uint32_t ldb   =s0 ;
    const uint32_t srelo =s1 ;
    const uint32_t su    =s14;
    const uint32_t sv    =s15;
    const uint32_t du    =s15;
    const uint32_t dv    =s16;
    
    const uint32_t lane=v0;
    const uint32_t tid =v1;
    const uint32_t bt  =v2;
    const uint32_t pix =v3;
    const uint32_t y   =v4;
    const uint32_t x   =v5;
    const uint32_t chn =v2;
    const uint32_t fi  =v3;
    const uint32_t v   =v4;
    const uint32_t u   =v5;

    metadata_start();
    {
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(56);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(24);
        metadata_set_vgprcnt(10);
    }
    metadata_end();

    kernel.start_descr();
    {
        kernel.enable_kernarg_segment();
        kernel.set_fp32_mode_round(amdgpu_fp_mode_rn);
        kernel.set_fp32_mode_denorm(amdgpu_fp_denorm_fsd);
        kernel.enable_dx10_clamp();
        kernel.enable_ieee_mode();
        kernel.set_user_sgprcnt(2);
        kernel.enable_sgpr_group_id_x();
        kernel.enable_vgpr_iterm_id_1d();
    }
    kernel.end_descr();

    v_shl_or_b32(tid,gidx,6,lane);
    s_lda_b256(s4,argptr,0x0);
    s_lda_b64(s2,argptr,0x20);
    s_sync(lgkmcnt(0));

    //tid=i<m?i:(m-1)
    //bat=tid/npix
    //pix=tid%npix
    //x=pix%onx
    //y=pix/onx
    s_sub_u32(s12,m,ic(1));
    s_mul_i32(s17,cnx,cny);
    v_cmp_u32(m,tid,gt);
    v_mov_b32(v7,s12);
    v_cmov_b32(v6,v7,tid);
    VDMX_U32(bt,pix,v6,s17,v7,s12);
    VDMX_U32(y,x,pix,cnx,v6,s12);
    
    //amap[0]=(bt*lda+sv*y*anx+su*x)<<2
    //amap[1]=(bt*npix*onc+pix)<<2
    s_lda_b64(bnx,argptr,0x28);
    s_lda_b64(ldb,argptr,0x30);
    s_shr_b32(sv,sd,6);
    s_and_b32(su,sd,ic(63));
    s_and_b32(sv,sv,ic(63));
    s_mul_i32(s12,sv,anx);
    s_mul_i32(s13,s17,onc);
    v_mul_lo_u32(v6,lda,bt);
    v_mul_lo_u32(v7,s13,bt);
    v_mad_u24(v8,s12,y,v6);
    v_mad_u24(v8,su,x,v8);
    v_add_shl_u32(v9,v7,pix,2);
    v_shl_b32(v0,tid,3);
    v_shl_b32(v8,v8,2);
    v_cmp_u32(amaps,tid,gt);
    s_andexec_b64(s2,vcc);
    stg_b64(base,v0,0x0,v8);
    s_mov_b64(exec,s2);
    s_shl_b32(s9,amaps,3);
    
    /*(c*ldb+dv*v*anx+du*u)<<2*/
    s_sync(lgkmcnt(0));
    s_mul_i32(s2,bny,bnx);
    S_ADD_U64_U32(base,base,s9);
    VDMX_U32(chn,fi,tid,s2,v6,s10);
    VDMX_U32(v,u,fi,bnx,v6,s10);
    s_shr_b32(du,sd,12);
    s_shr_b32(dv,sd,18);
    s_and_b32(du,du,ic(63));
    v_mul_lo_u32(v6,ldb,chn);
    s_mul_i32(s2,dv,anx);
    s_add_u32(s3,srelo,ic(7));
    s_andn2_b32(s3,s3,ic(7));
    s_add_u32(s3,s3,ic(32));
    v_mul_u24(v7,du,u);
    v_mad_u24(v8,s2,v,v6);
    v_add_shl_u32(v6,v7,v8,2);
    v_cmp_u32(srelo,tid,gt);
    v_cmov_b32(v0,zero,v6);
    v_shl_b32(v2,tid,2);
    v_cmpx_u32(s3,tid,gt);
    stg_b32(base,v2,0x0,v0);
    s_endp();
}