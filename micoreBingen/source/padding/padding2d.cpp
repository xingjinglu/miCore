#include"../../include/gfxcoder.h"

/*
bbase:0x00
abase:0x08
anx  :0x10
any  :0x14
pad  :0x18
nc   :0x1c
ldb  :0x20
*/
void gfxcoder::padding2d()
{
    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s22;
    const uint32_t bbase =s0 ;
    const uint32_t abase =s2 ;
    const uint32_t anx   =s4 ;
    const uint32_t any   =s5 ;
    const uint32_t pad   =s6 ;
    const uint32_t nc    =s7 ;
    const uint32_t ldb   =s8 ;
    const uint32_t bnx   =s9 ;
    const uint32_t bny   =s10;
    const uint32_t npx   =s11;
    const uint32_t pl    =s12;
    const uint32_t pr    =s13;
    const uint32_t pt    =s14;
    const uint32_t pb    =s15;
    
    const uint32_t tidx=v0;
    const uint32_t chn =v1;
    const uint32_t pix =v2;
    const uint32_t v   =v3;
    const uint32_t u   =v4;
    const uint32_t val =v5;

    metadata_start();
    {
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(36);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(27);
        metadata_set_vgprcnt(8);
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

    s_lda_b128(s4,argptr,0x10);
    s_lda_b32(ldb,argptr,0x20);
    v_shl_or_b32(tidx,gidx,8,v0);
    s_mov_b32(gidy,s3);
    v_mov_b32(val,zero);
    s_sync(lgkmcnt(0));
    s_lda_b128(s0,argptr,0x0);
    s_movk_i32(s16,0xff);
    s_shr_b32(pr,pad, 8);
    s_shr_b32(pt,pad,16);
    s_shr_b32(pb,pad,24);
    s_and_b32(pl,s16,pad);
    s_and_b32(pr,s16,pr);
    s_and_b32(pt,s16,pt);
    s_add_u32(bnx,anx,pl);
    s_add_u32(bny,any,pt);
    s_add_u32(bnx,bnx,pr);
    s_add_u32(bny,bny,pb);
    s_mul_i32(npx,bnx,bny);
    VDM_U32(chn,pix,tidx,npx,v6,s16);
    VDM_U32(v,u,pix,bnx,v6,s16);
    v_sub_i32(u,u,pl);
    v_sub_i32(v,v,pt);
    /*if(((u-pl)>=0)&&((u-pl)<anx)&&((v-pt)>=0)&&((v-pt)<any)&&(chn<nc))*/
    v_cmp_u32(s14,u,zero,ge);
    v_cmp_u32(s16,v,zero,ge);
    v_cmp_u32(s18,anx,u,gt);
    v_cmp_u32(s12,nc,chn,gt);
    v_cmp_u32(any,v,gt);
    s_mov_b64(s20,exec);
    s_and_b64(s14,s14,s16);
    s_and_b64(s18,s18,s12);
    s_and_b64(s16,s14,vcc);
    s_and_b64(exec,s16,s18);
    /*gidy*nc*anx*any+(chn*any+v)*anx+u*/
    s_mul_i32(s14,gidy,nc);
    s_mul_i32(s15,anx,any);
    s_mul_i32(s16,s14,s15);
    s_movk_i32(s17,0);
    s_shl_b64(s14,s16,2);
    s_sync(lgkmcnt(0));
    S_ADD_U64(abase,abase,s14);
    v_mad_u24(v6,any,chn,v);
    v_mul_lo_u32(v7,anx,v6);
    v_add_shl_u32(v0,v7,u,2);
    ldg_b32(val,abase,v0,0x0);
    s_mov_b64(exec,s20);
    /*gidy*npx+chn*ldb+pix*/
    v_mul_lo_u32(v3,ldb,chn);
    v_add_shl_u32(v0,v3,pix,2);
    s_mul_i32(s4,gidy,npx);
    s_movk_i32(s5,0);
    s_shl_b64(s2,s4,2);
    S_ADD_U64(bbase,bbase,s2);
    s_sync(vmcnt(0));
    s_mov_b64(exec,s12);
    stg_b32(bbase,v0,0x0,val);
    s_endp();
}