#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft32x32.h"

/*args : d_c, ldc, bks, d_r, ncells, nx, ldx, ldy, grid, tile, xmagic, xshift, ymagic, yshift, ny, pad*/

void gfxcoder::sfft5x5_r2c_grid_perm_pad()
{
    uint2 c[24];
    for( int i=0; i<16; ++i ){ c[i].x=v0+i; c[i].y=v16+i; }
    for( int i=0; i<16; ++i ){ CPTR(c)[32+i]=v32+i; }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t rbase =s4 ;
    const uint32_t ncells=s6 ;
    const uint32_t nx    =s7 ;
    const uint32_t ldx   =s8 ;
    const uint32_t ldy   =s9 ;
    const uint32_t grid  =s10;
    const uint32_t tile  =s11;
    const uint32_t xmagic=s12;
    const uint32_t xshift=s13;
    const uint32_t ymagic=s14;
    const uint32_t yshift=s15;
    const uint32_t ny    =s16;
    const uint32_t pad   =s17;
    const uint32_t grid_x=s18;
    const uint32_t grid_y=s19;
    const uint32_t tile_x=s20;
    const uint32_t tile_y=s21;
    const uint32_t pad_x =s22;
    const uint32_t pad_y =s23;
    const uint32_t C0x   =s7 ;
    const uint32_t C0y   =s8 ;
    const uint32_t C1x   =s9 ;
    const uint32_t C1y   =s10;
    const uint32_t C2x   =s11;
    const uint32_t C2y   =s12;
    const uint32_t C3x   =s13;
    const uint32_t C3y   =s14;
    const uint32_t C4x   =s15;
    const uint32_t C4y   =s16;
    const uint32_t C5x   =s17;
    const uint32_t C5y   =s18;
    const uint32_t C6x   =s19;
    const uint32_t C6y   =s20;
    const uint32_t C7x   =s21;
    const uint32_t C7y   =s22;
    const uint32_t C8x   =s23;
    const uint32_t C8y   =s24;
    const uint32_t sk0   =s25;
    const uint32_t sk1   =s26;
    const uint32_t sk2   =s27;
    const uint32_t sk3   =s28;
    const uint32_t sk4   =s29;
    const uint32_t sk5   =s30;
    const uint32_t sk6   =s31;
    const uint32_t k0x   =s32;
    const uint32_t k0y   =s33;
    const uint32_t k1x   =s34;
    const uint32_t k1y   =s35;
    const uint32_t k2x   =s36;
    const uint32_t k2y   =s37;
    const uint32_t k3x   =s38;
    const uint32_t k3y   =s39;
    const uint32_t k4x   =s40;
    const uint32_t k4y   =s41;
    const uint32_t k5x   =s42;
    const uint32_t k5y   =s43;
    const uint32_t k6x   =s44;
    const uint32_t k6y   =s45;
    const uint32_t k7x   =s46;
    const uint32_t k7y   =s47;
    const uint32_t k8x   =s48;
    const uint32_t k8y   =s49;
    const uint32_t k9x   =s50;
    const uint32_t k9y   =s51;
    const uint32_t kax   =s52;
    const uint32_t kay   =s53;
    const uint32_t kbx   =s54;
    const uint32_t kby   =s55;
    const uint32_t kcx   =s56;
    const uint32_t kcy   =s57;
    const uint32_t kdx   =s58;
    const uint32_t kdy   =s59;
    const uint32_t cbase =s0 ;
    const uint32_t ldc   =s2 ;
    const uint32_t bks   =s3 ;

    const uint32_t rvo    =v32;
    const uint32_t icell  =v33;
    const uint32_t icell_y=v34;
    const uint32_t icell_x=v35;
    const uint32_t imap   =v36;
    const uint32_t ox     =v37;
    const uint32_t oy     =v38;   
    const uint32_t x      =v39;
    const uint32_t y      =v40;
    const uint32_t v      =v41;
    const uint32_t p      =v48;
    const uint32_t q      =v49;
    const uint32_t u      =v50;
    const uint32_t aperm  =v51;
    const uint32_t xsst   =v52;
    const uint32_t xsld   =v54;
    const uint32_t ysst   =v55;
    const uint32_t ysld   =v52;
    const uint32_t osst   =v56;
    const uint32_t osld   =v57;
    const uint32_t cvo    =v34;

    metadata_start();
	{
        metadata_set_lds_size(0x8840);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(72);
        metadata_set_group_size(512);
        metadata_set_sgprcnt(64);
        metadata_set_vgprcnt(58);
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

    s_lda_b256(s4,argptr,0x10);
    s_lda_b128(s12,argptr,0x30);
    s_lda_b64(s16,argptr,0x40);
    v_and_b32(x,ic(31),v0);
    v_and_b32(p,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,5);
    v_shr_b32(q,v0,4);
    v_shr_b32(v,x,1);
    v_shl_or_b32(icell,gidx,4,y);
    s_movk_b32(s24,0xffff);
    s_shl_b32(s25,gidy,2);
    s_sync(lgkmcnt(0));
    //======================================================================
	//ox=cell_x*tx-pad_x+x;
	//oy=cell_y*ty-pad_y;
	//d_r+=gidy*ldy+imap*ldx+(icell_y==0?0:oy)*nx+ox;
    //======================================================================
    s_shr_b32(grid_y,grid,16);
    s_shr_b32(tile_y,tile,16);
    s_shr_b32(pad_y,pad,16);
    s_and_b32(grid_x,grid,s24);
    s_and_b32(tile_x,tile,s24);
    s_and_b32(pad_x,pad,s24);
    CALC_SPLIT_IDX(imap,icell_y,icell,grid_x,xmagic,ymagic,s26);
    v_mul_lo_u32(v43,ldx,imap);
    S_MUL_U64_U32(s8,s25,ldy);
    v_mul_u24(ox,tile_x,icell_x);
    v_mul_u24(oy,tile_y,icell_y);
    v_sub_i32(ox,ox,pad_x);
    v_sub_i32(oy,oy,pad_y);
    v_add_i32(ox,ox,x);
    v_cmp_u32(zero,icell_y,ne);
    v_cmov_b32(v42,zero,oy);
    v_mad_u24(v44,nx,v42,v43);
    v_add_shl_u32(rvo,v44,ox,2);
    S_ADD_U64(rbase,rbase,s8);
    //======================================================================
    FFT32x32_R2C_LDR_SPLIT_PAD(c,rbase,rvo,ox,oy,icell,ncells,nx,ny);
    FFT32x32_R2C_CALC_LDS_PTRS(aperm,xsst,xsld,ysst,osst,osld,x,y,p,q,u,v,s7);
    FFT32x32_SET_RF();
    FFT32x32_SET_SCOEF();
    s_sync(vmcnt(0));
    VFFT32(c,xsst,xsld);
    HFFT32(c,ysst,ysld,u,aperm,s4,);
    //======================================================================
    //d_c+=gidy*ldc+(gidx<<4)+q*bks+p
    //======================================================================
    v_shl_or_b32(v36,gidx,4,p);
    s_shl_b32(s4,gidx,7);
    s_shl_b32(s5,gidy,3);
    s_lda_b128(s0,argptr,0x0);
    s_movk_i32(s9,0);
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v35,bks,q);
    s_mul_i32(s7,ldc,s5);
    s_mov_b32(s8,bks);
    s_add_u32(s2,s4,s7);
    s_shl_b64(s34,s8,8);
    S_ADD_U64_U32(cbase,cbase,s2);
    v_add_shl_u32(cvo,v35,p,3);
    v_cmp_u32(ncells,v36,gt);
    FFT32x32_R2C_PERMST(cbase,cvo,s34,c,osst,osld,vcc);
}