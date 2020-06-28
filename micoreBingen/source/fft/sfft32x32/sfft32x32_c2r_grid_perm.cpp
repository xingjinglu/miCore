#include"../../../include/gfxcoder.h"
#include"../../../include/fft/sfft32x32.h"

/*args : d_r, ldx, ldy, d_c, ldc, bks, xmagic, xshift, ymagic, yshift, grid, tile, nx, ny, ncells*/

void gfxcoder::sfft5x5_c2r_grid_perm( uint32_t mask )
{
    uint2 c[24];
    for( int i=0; i<48; ++i ){ CPTR(c)[i]=v0+i; }

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
    const uint32_t C3x   =s12;
    const uint32_t C3y   =s13;
    const uint32_t C4x   =s14;
    const uint32_t C4y   =s15;
    const uint32_t C5x   =s16;
    const uint32_t C5y   =s17;
    const uint32_t C6x   =s18;
    const uint32_t C6y   =s19;
    const uint32_t C7x   =s20;
    const uint32_t C7y   =s21;
    const uint32_t C8x   =s22;
    const uint32_t C8y   =s23;
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
    const uint32_t rbase =s0 ;
    const uint32_t ldx   =s2 ;
    const uint32_t ldy   =s3 ;
    const uint32_t ncells=s18;

    const uint32_t p      =v34;
    const uint32_t q      =v35;
    const uint32_t cvo    =v36;
    const uint32_t x      =v48;
    const uint32_t y      =v49;
    const uint32_t u      =v50;
    const uint32_t flipx  =v51;
    const uint32_t spa    =v52;
    const uint32_t spb    =v54;
    const uint32_t spc    =v55;
    const uint32_t icell  =v35;
    const uint32_t icell_y=v36;
    const uint32_t icell_x=v37;
    const uint32_t imap   =v38;
    const uint32_t ox     =v39;
    const uint32_t oy     =v40;
    const uint32_t rvo    =v32;
    const uint32_t valx   =v33;
    const uint32_t valy   =v34;

    metadata_start();
	{
        metadata_set_lds_size(0x4600);
        metadata_set_kernarg_align(4);
        metadata_set_kernarg_size(68);
        metadata_set_group_size(256);
        metadata_set_sgprcnt(28);
        metadata_set_vgprcnt(56);
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
    v_and_b32(x,ic(31),v0);
    v_and_b32(p,ic(7),v0);
    v_and_b32(u,ic(1),v0);
    v_shr_b32(y,v0,5);
    v_shr_b32(q,v0,3);
    v_sub_u32(v38,ic(32),x);
    s_shl_b32(s8,gidy,3);
    s_shl_b32(s9,gidx,6);
    s_sync(lgkmcnt(0));
    //===========================================================
    //d_c+=q*bks+by*ldc+(bx<<3)+p
    //===========================================================
    v_mul_lo_u32(v37,bks,q);
    v_and_b32(flipx,ic(31),v38);
    s_mul_i32(s10,ldc,s8);
    s_add_u32(s11,s10,s9);
    S_ADD_U64_U32(cbase,cbase,s11);
    v_add_shl_u32(cvo,v37,p,3);
    FFT32x32_C2R_LDPERM(c,cbase,cvo,spa,spb,spc,x,y,p,q,u,bks,s8);
    HIFFT32(c,spa,spb,spc,u,s4);
    VIFFT32(c,x,s4);
    //============================================================
    //ox=cell_x*tile_x
    //oy=cell_y*tile_y
    //d_r+=by*ldy+imap*ldx+oy*nx+ox+flipx
    //============================================================
    s_lda_b256(s4,argptr,0x20);
    s_movk_b32(s16,0xffff);
    s_shl_b32(s17,gidy,2);
    v_shl_or_b32(icell,gidx,3,y);
    if(mask&0x1){ for( int i=0; i<32; ++i ){ v_max_f32(CPTR(c)[i],zero,CPTR(c)[i]); } }
    s_sync(lgkmcnt(0));
    s_lda_b32(ncells,argptr,0x40);
    s_lda_b128(s0,argptr,0x0);
    s_shr_b32(grid_y,grid,16);
    s_shr_b32(tile_y,tile,16);
    s_and_b32(grid_x,grid,s16);
    s_and_b32(tile_x,tile,s16);
    CALC_SPLIT_IDX(imap,icell_y,icell,grid_x,xmagic,ymagic,s8);
    v_mul_u24(ox,tile_x,icell_x);
    v_mul_u24(oy,tile_y,icell_y);
    s_sub_u32(s4,grid_x,ic(1));
    s_sub_u32(s5,grid_y,ic(1));
    v_sub_u32(v41,nx,ox);
    v_sub_u32(v42,ny,oy);
    v_mov_b32(valx,tile_x);
    v_mov_b32(valy,tile_y);
    v_cmp_u32(s4,icell_x,gt);
    v_cmov_b32(valx,v41,valx);
    v_cmp_u32(s5,icell_y,gt);
    v_cmov_b32(valy,v42,valy);
    v_add_u32(ox,ox,flipx);
    s_sync(lgkmcnt(0));
    v_mul_lo_u32(v36,ldx,imap);
    v_mad_u24(v37,nx,oy,ox);
    S_MUL_U64_U32(s4,ldy,s17);
    S_ADD_U64(rbase,rbase,s4);
    v_add_shl_u32(rvo,v36,v37,2);
    FFT32x32_C2R_ST_SPLICE(rbase,rvo,c,flipx,icell,ncells,valx,valy,nx);
}