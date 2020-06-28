#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft16x16.h"

void gfxcoder::sfft4x4_c2r_grid_perm( uint32_t mask )
{
    uint2 c[12];
    for( int i=0; i<24; ++i ){ CPTR(c)[i]=v0+i; }

    const uint32_t argptr=s0 ;
    const uint32_t gidx  =s2 ;
    const uint32_t gidy  =s3 ;
    const uint32_t cbase =s4 ;
    const uint32_t ldc   =s6 ;
    const uint32_t bks   =s7 ;
    const uint32_t C0x   =s6 ;
    const uint32_t C0y   =s7 ;
    const uint32_t C1x   =s8 ;
    const uint32_t C1y   =s9 ;
    const uint32_t C2x   =s10;
    const uint32_t C2y   =s11;
    const uint32_t xmagic=s4 ;
    const uint32_t xshift=s5 ;
    const uint32_t ymagic=s6 ;
    const uint32_t yshift=s7 ;
    const uint32_t grid  =s8 ;
    const uint32_t tile  =s9 ;
    const uint32_t nx    =s10;
    const uint32_t ny    =s11;
    const uint32_t grid_x=s12;
    const uint32_t grid_y=s13;
    const uint32_t tile_x=s14;
    const uint32_t tile_y=s15;
    const uint32_t ncells=s16;
    const uint32_t rbase =s0 ;
    const uint32_t ldx   =s2 ;
    const uint32_t ldy   =s3 ;


    const uint32_t cvo    =v18;
    const uint32_t x      =v24;
    const uint32_t y      =v25;
    const uint32_t u      =v26;
    const uint32_t flipx  =v27;
    const uint32_t spa    =v28;
    const uint32_t spb    =v29;
    const uint32_t spc    =v30;
    const uint32_t rvo    =v16;
    const uint32_t valx   =v17;
    const uint32_t valy   =v18;
    const uint32_t icell  =v19;
    const uint32_t icell_y=v20;
    const uint32_t icell_x=v21;
    const uint32_t imap   =v22;
    const uint32_t ox     =v23;
    const uint32_t oy     =v24;

    metadata_start();
	{
        metadata_set_lds_size(0x2440);
        metadata_set_kernarg_align(5);
        metadata_set_kernarg_size(68);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(23);
        metadata_set_vgprcnt(31);
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
    s_lda_b32(ncells,argptr,0x40);
    v_shr_b32(y,v0,4);
    v_and_b32(x,ic(15),v0);
    v_and_b32(u,ic(1),v0);
    v_sub_u32(v20,ic(16),x);
    v_shl_or_b32(v21,gidx,4,x);
    s_shl_b32(s8,gidy,3);
    s_shl_b32(s9,gidx,7);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=by*ldc+(bx<<4)+y*bks+x
    //===========================================================
    v_mul_lo_u32(v19,bks,y);
    v_and_b32(flipx,ic(15),v20);
    s_mul_i32(s10,ldc,s8);
    s_add_u32(s11,s10,s9);
    S_ADD_U64_U32(cbase,cbase,s11);
    v_add_shl_u32(cvo,v19,x,3);
    v_cmp_u32(ncells,v21,gt);
    FFT16x16_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,u,bks,vcc,s8);
    HIFFT16(c,spa,spb,spc,u,s4);
    VIFFT16(c,x,s4);
    //============================================================
    //ox=cell_x*tile_x
    //oy=cell_y*tile_y
    //valx=(cell_x<grid_x-1)?sx:(nx-ox)
    //valy=(cell_y<grid_y-1)?sy:(ny-oy)
    //d_r+=by*ldy+imap*ldx+oy*nx+ox+flipx
    //============================================================
    s_lda_b256(s4,argptr,0x20);
    s_movk_b32(s17,0xffff);
    s_shl_b32(s18,gidy,2);
    v_shl_or_b32(icell,gidx,4,y);
    if(mask&1){ for( int i=0; i<16; ++i ){ v_max_f32(CPTR(c)[i],zero,CPTR(c)[i]); } }
    s_sync(lgkmcnt(0));
    s_lda_b128(s0,argptr,0x0);
    s_shr_b32(grid_y,grid,16);
    s_shr_b32(tile_y,tile,16);
    s_and_b32(grid_x,grid,s17);
    s_and_b32(tile_x,tile,s17);
    CALC_SPLIT_IDX(imap,icell_y,icell,grid_x,xmagic,ymagic,s8);
    v_mul_u24(ox,tile_x,icell_x);
    v_mul_u24(oy,tile_y,icell_y);
    s_sub_u32(s4,grid_x,ic(1));
    s_sub_u32(s5,grid_y,ic(1));
    v_sub_u32(v25,nx,ox);
    v_sub_u32(v26,ny,oy);
    v_mov_b32(valx,tile_x);
    v_mov_b32(valy,tile_y);
    v_cmp_u32(s4,icell_x,gt);
    v_cmov_b32(valx,v25,valx);
    v_cmp_u32(s5,icell_y,gt);
    v_cmov_b32(valy,v26,valy);
    v_add_u32(ox,ox,flipx);
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v25,ldx,imap);
    v_mad_u24(v26,nx,oy,ox);
    S_MUL_U64_U32(s4,s18,ldy);
    S_ADD_U64(rbase,rbase,s4);
    v_add_shl_u32(rvo,v25,v26,2);
    FFT16x16_C2R_ST_SPLICE(rbase,rvo,c,flipx,icell,ncells,valx,valy,nx);
}
