#include"../../include/gfxcoder.h"

/*
abase
bbase
lda
ldb, ldb>=align(n,4)
k
n
fvo
*/

void gfxcoder::perm_flip()
{
    const uint32_t argptr=s0 ;
    const uint32_t bbase =s0 ;
    const uint32_t abase =s2 ;
    const uint32_t lda   =s4 ;
    const uint32_t ldb   =s5 ;
    const uint32_t k     =s6 ;
    const uint32_t n     =s7 ;
    const uint32_t fvo   =s8 ;
    const uint32_t pk    =s9 ;
    const uint32_t gidx  =s10;
    const uint32_t gidy  =s11;
    const uint32_t gidz  =s12;
    const uint32_t pn    =s13;

    const uint32_t lane =v0;
    const uint32_t ao   =v1;
    const uint32_t bo   =v2;
    const uint32_t tidx =v3;
    const uint32_t val  =v3;

    metadata_start();
    {
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(40);
        metadata_set_group_size(64);
        metadata_set_sgprcnt(28);
        metadata_set_vgprcnt(4);
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

    s_mov_b32(gidx,s2);
    s_mov_b32(gidy,s3);
    s_mov_b32(gidz,s4);
    s_lda_b64(s8,argptr,0x20);
    s_lda_b256(s0,argptr,0x00);
    v_shl_or_b32(tidx,gidx,6,lane);
    v_shl_b32(bo,tidx,2);
    s_sync(lgkmcnt(0));

    /*pn=PSIZE(n,3) */
    s_add_u32(pn,n,ic(3));
    s_andn2_b32(pn,pn,ic(3));

    /* bbase+=gidz*pk*ldb+gidy*fvo*ldb */
    s_mul_i32(s18,gidz,pk);
    s_mul_i32(s19,gidy,fvo);
    s_shl_b32(ldb,ldb,2);
    S_MUL_U64_U32(s14,ldb,s18);
    S_MUL_U64_U32(s16,ldb,s19);
    S_ADD_U64(bbase,bbase,s14);
    s_mov_b64(s18,bbase);
    S_ADD_U64(bbase,bbase,s16);

    /* abase+=gidz*n*fvo+gidy*lda+(fvo-1) */
    v_mul_lo_u32(ao,fvo,tidx);
    s_mul_i32(s20,n,fvo);
    s_shl_b32(s21,gidz,2);
    s_shl_b32(s22,gidy,2);
    s_sub_u32(fvo,fvo,ic(1));
    s_shl_b32(s23,fvo,2);
    v_shl_b32(ao,ao,2);
    S_MUL_U64_U32(s14,s20,s21);
    S_MUL_U64_U32(s16,lda,s22);
    S_ADD_U64(abase,abase,s14);
    S_ADD_U64(abase,abase,s16);
    S_ADD_U64_U32(abase,abase,s23);

    /*
    for( i=0; i<fvo; ++i ){
        val=0
        if((tidx<n){ ldg_b32(val,abase,ao,0x0) }
        sync(vmcnt(0))
        if(tidx<pn){ stg_b32(bbase,bo,0x0,val) }
        abase+=4, bbase+=ldb
    }
    */
    s_mov_b64(s14,exec);
    v_cmp_u32(s16,pn,tidx,gt);
    v_cmp_u32(n,tidx,gt);
    
__lable__(0);
    v_mov_b32(val,zero);
    s_and_b64(exec,vcc,s14);
    ldg_b32(val,abase,ao,0x0);
    s_sync(vmcnt(0));
    s_and_b64(exec,s16,s14);
    stg_b32(bbase,bo,0x0,val);
    S_SUB_U64_U32(abase,abase,ic(4));
    S_ADD_U64_U32(bbase,bbase,ldb);
    s_sub_u32(fvo,fvo,ic(1));
    s_cbra_scc0(0);

    /*
    if(gidy==0){
        if(tidx<pn){ for( i=k; i<pk; ++i ){ stg_b32(bbase[gidz*pk*ldb+k*ldb+bo+i*ldb],bo,0x0,zero) } }
    }
    */
    s_cmpk_u32(gidy,0,eq);
    s_cbra_scc0(2);
    s_cmp_u32(k,pk,lt);
    s_cbra_scc0(2);
    s_sub_u32(s7,pk,k);
    S_MUL_U64_U32(bbase,k,ldb);
    S_ADD_U64(bbase,bbase,s18);
    s_sub_u32(s7,s7,ic(1));
    s_mov_b64(exec,s16);
    v_mov_b32(val,zero);
__lable__(1);
    stg_b32(bbase,bo,0x0,val);
    S_ADD_U64_U32(bbase,bbase,ldb);
    s_sub_u32(s7,s7,ic(1));
    s_cbra_scc0(1);

__lable__(2);
    s_endp();
}
    
    
    
    
    
    
    
    

    


