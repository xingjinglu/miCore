#ifndef __gfxcoder_h__
#define __gfxcoder_h__

#include"hsaco/hsaco.h"
#include"gcnisa/gcnisa.h"
#include"mcode.h"

class gfxcoder
{
public:
    gfxcoder();
   ~gfxcoder();
public:
    void gen( uint8_t*, uint32_t* );
    const vector<string>& kernel_names() const;

private:
    void metadata_start();
    void metadata_set_lds_size( uint32_t );
    void metadata_set_kernarg_align( uint32_t );
    void metadata_set_kernarg_size( uint32_t );
    void metadata_set_private_size( uint32_t );
    void metadata_set_group_size( uint32_t );
    void metadata_set_wave_size( uint32_t );
    void metadata_set_sgprcnt( uint32_t );
    void metadata_set_vgprcnt( uint32_t );
    void metadata_end();

    void padding2d();
    void perm_flip();
    void genidx_co2d();
    void suffco7x4_om( uint32_t );
    void suffco7x4_dm( uint32_t );
    void suffco7x4_qm( uint32_t );
    void suffco8x5_om( uint32_t );
    void suffco8x5_dm( uint32_t );
    void suffco8x5_qm( uint32_t );
    void suffco8x6_om( uint32_t );
    void suffco8x6_dm( uint32_t );
    void suffco8x6_qm( uint32_t );
    void suffco7x7_om( uint32_t );
    void suffco7x7_dm( uint32_t );
    void suffco7x7_qm( uint32_t );
    void sufbco7x4_om();
    void sufbco7x4_dm();
    void sufbco7x4_qm();
    void sufbco8x5_om();
    void sufbco8x5_dm();
    void sufbco8x5_qm();
    void sufbco8x6_om();
    void sufbco8x6_dm();
    void sufbco8x6_qm();
    void sufbco7x7_om();
    void sufbco7x7_dm();
    void sufbco7x7_qm();
    void sfco   ( uint32_t );
    void sfco7x4( uint32_t );
    void sfco8x5( uint32_t );
    void sfco8x6( uint32_t );
    void sfco7x7( uint32_t );
    void sbco7x4();
    void sbco8x5();
    void sbco8x6();
    void sbco7x7();

    void sgemm6x5();
    void sgemm7x5();
    void sgemm8x5();
    void sgemm6x6();
    void sgemm7x6();
    void sgemm8x6();
    void sgemm7x7();
    void sco3x3q6_dta();
    void sco3x3q6_dtx();
    void sco3x3q6_dtp();
    void sco3x3q6_xft( uint32_t );
    void sco3x3q6_ota( uint32_t );
    void sco3x3q6_otx( uint32_t );

    void scgemm5x4();
    void scgemm5x4_ck();
    void scgemm5x5();
    void scgemm5x5_ck();
    void scgemm5x6();
    void scgemm5x6_ck();
    void scgemm6x4();
    void scgemm6x4_ck();
    void scgemm6x5();
    void scgemm6x5_ck();
    void scgemm6x6();
    void scgemm6x6_ck();
    void sfft4x4_r2c_perm( uint32_t );
    void sfft4x4_r2c_perm_flip( uint32_t );
    void sfft4x4_r2c_perm_pad( uint32_t );
    void sfft4x4_r2c_perm_s3x3();
    void sfft4x4_r2c_perm_s5x5();
    void sfft4x4_r2c_qerm_s3x3();
    void sfft4x4_r2c_qerm_s5x5();
    void sfft4x4_r2c_grid_perm();
    void sfft4x4_r2c_grid_perm_ex();
    void sfft4x4_r2c_grid_perm_pad();
    void sfft4x4_r2c_grad();
    void sfft4x4_r2c_grad_ex();
    void sfft4x4_r2c_grad_pad();
    void sfft4x4_r2c_grad_nov();
    void sfft4x4_c2r_perm( uint32_t );
    void sfft4x4_c2r_grid_perm( uint32_t );
    void sfft4x4_c2r_g3x1();
    void sfft4x4_c2r_g1x3();
    void sfft4x4_c2r_g5x1();
    void sfft4x4_c2r_g1x5();
    void sfft4x4_c2r_g7x1();
    void sfft4x4_c2r_g1x7();
    void sfft4x4_c2r_g9x1();
    void sfft4x4_c2r_g1x9();
    void sfft4x4_c2r_g3x3();
    void sfft4x4_c2r_g5x5();
    void sfft4x4_c2r_g7x7();

    void sfft5x5_r2c_perm( uint32_t );
    void sfft5x5_r2c_perm_flip( uint32_t );
    void sfft5x5_r2c_perm_pad( uint32_t );
    void sfft5x5_r2c_perm_s3x3();
    void sfft5x5_r2c_perm_s5x5();
    void sfft5x5_r2c_qerm_s3x3();
    void sfft5x5_r2c_qerm_s5x5();
    void sfft5x5_r2c_grid_perm();
    void sfft5x5_r2c_grid_perm_ex();
    void sfft5x5_r2c_grid_perm_pad();
    void sfft5x5_r2c_grad();
    void sfft5x5_r2c_grad_ex();
    void sfft5x5_r2c_grad_pad();
    void sfft5x5_r2c_grad_nov();
    void sfft5x5_c2r_perm( uint32_t );
    void sfft5x5_c2r_grid_perm( uint32_t );
    void sfft5x5_c2r_g3x1();
    void sfft5x5_c2r_g1x3();
    void sfft5x5_c2r_g5x1();
    void sfft5x5_c2r_g1x5();
    void sfft5x5_c2r_g7x1();
    void sfft5x5_c2r_g1x7();
    void sfft5x5_c2r_g9x1();
    void sfft5x5_c2r_g1x9();
    void sfft5x5_c2r_g3x3();
    void sfft5x5_c2r_g5x5();
    void sfft5x5_c2r_g7x7();

    void alignib();
    void dpp_ror_b32( uint32_t, uint32_t, uint32_t );
    void dpp_srr_b32( uint32_t, uint32_t, uint32_t );
    void dpp_shf_xor_b32( uint32_t, uint32_t, uint32_t );
    inline void __lable__( uint32_t i ){ kernel.ilable[i]=kernel.icode; }

    inline void s_mov_b32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_mov_b32 |a; }
    inline void s_mov_b64      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_mov_b64 |a; }
    inline void s_cmov_b32     ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_cmov_b32|a; }
    inline void s_cmov_b64     ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_cmov_b64|a; }
    inline void s_movk_b32     ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_mov_b32 |lit; kernel.instr[kernel.icode++]=a; }
    inline void s_movk_b64     ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_mov_b64 |lit; kernel.instr[kernel.icode++]=a; }
    inline void s_cmovk_b32    ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_cmov_b32|lit; kernel.instr[kernel.icode++]=a; }
    inline void s_cmovk_b64    ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_cmov_b64|lit; kernel.instr[kernel.icode++]=a; }
    inline void s_not_b32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_not_b32 |a; }
    inline void s_not_b64      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_not_b64 |a; }
    inline void s_bfz_b32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_bfz_b32 |a; }
    inline void s_bfz_b64      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_bfz_b64 |a; }
    inline void s_bfs_b32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_bfs_b32 |a; }
    inline void s_bfs_b64      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_bfs_b64 |a; }
    inline void s_andexec_b64  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_andexec_b64  |a; }
    inline void s_andnexec_b64 ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_andnexec_b64 |a; }
    inline void s_andn1exec_b64( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_andn1exec_b64|a; }
    inline void s_nandexec_b64 ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_sop1|(b<<16)|sop1_nandexec_b64 |a; }
    
    inline void s_movk_i32  ( uint32_t b, uint16_t a ){ kernel.instr[kernel.icode++]=encoding_sopk|sopk_movk_b32  |(b<<16)|a; }
    inline void s_cmovk_i32 ( uint32_t b, uint16_t a ){ kernel.instr[kernel.icode++]=encoding_sopk|sopk_cmovk_b32 |(b<<16)|a; }
    inline void s_addk_i32  ( uint32_t b, uint16_t a ){ kernel.instr[kernel.icode++]=encoding_sopk|sopk_addk_i32  |(b<<16)|a; }
    inline void s_mulk_i32  ( uint32_t b, uint16_t a ){ kernel.instr[kernel.icode++]=encoding_sopk|sopk_mulk_i32  |(b<<16)|a; }
    inline void s_getreg_b32( uint32_t b, uint16_t a ){ kernel.instr[kernel.icode++]=encoding_sopk|sopk_getreg_b32|(b<<16)|a; }
    inline void s_cmpk_i32  ( uint32_t a, uint16_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_sopk|((2+op)<<23)|(a<<16)|b; }
    inline void s_cmpk_u32  ( uint32_t a, uint16_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_sopk|((8+op)<<23)|(a<<16)|b; }
    
    inline void s_add_u32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_add_u32     |(c<<16)|(b<<8)|a; }
    inline void s_sub_u32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_sub_u32     |(c<<16)|(b<<8)|a; }
    inline void s_addc_u32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_addc_u32    |(c<<16)|(b<<8)|a; }
    inline void s_subc_u32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_subc_u32    |(c<<16)|(b<<8)|a; }
    inline void s_add_i32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_add_i32     |(c<<16)|(b<<8)|a; }
    inline void s_sub_i32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_sub_i32     |(c<<16)|(b<<8)|a; }
    inline void s_csel_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_csel_b32    |(c<<16)|(b<<8)|a; }
    inline void s_csel_b64    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_csel_b64    |(c<<16)|(b<<8)|a; }
    inline void s_and_b32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_and_b32     |(c<<16)|(b<<8)|a; }
    inline void s_and_b64     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_and_b64     |(c<<16)|(b<<8)|a; }
    inline void s_or_b32      ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_or_b32      |(c<<16)|(b<<8)|a; }
    inline void s_or_b64      ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_or_b64      |(c<<16)|(b<<8)|a; }
    inline void s_xor_b32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_xor_b32     |(c<<16)|(b<<8)|a; }
    inline void s_xor_b64     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_xor_b64     |(c<<16)|(b<<8)|a; }
    inline void s_andn2_b32   ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_andn2_b32   |(c<<16)|(b<<8)|a; }
    inline void s_andn2_b64   ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_andn2_b64   |(c<<16)|(b<<8)|a; }
    inline void s_nand_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_nand_b32    |(c<<16)|(b<<8)|a; }
    inline void s_nand_b64    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_nand_b64    |(c<<16)|(b<<8)|a; }
    inline void s_mul_i32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_mul_i32     |(c<<16)|(b<<8)|a; }
    inline void s_mul_hi_u32  ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_mul_hi_u32  |(c<<16)|(b<<8)|a; }
    inline void s_mul_hi_i32  ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_mul_hi_i32  |(c<<16)|(b<<8)|a; }
    inline void s_shl1_add_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl1_add_u32|(c<<16)|(b<<8)|a; }
    inline void s_shl2_add_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl2_add_u32|(c<<16)|(b<<8)|a; }
    inline void s_shl3_add_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl3_add_u32|(c<<16)|(b<<8)|a; }
    inline void s_shl4_add_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl4_add_u32|(c<<16)|(b<<8)|a; }
    inline void s_shl_b32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl_b32     |(c<<16)|((128u+b)<<8)|a; }
    inline void s_shl_b64     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shl_b64     |(c<<16)|((128u+b)<<8)|a; }
    inline void s_shr_b32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shr_b32     |(c<<16)|((128u+b)<<8)|a; }
    inline void s_shr_b64     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_shr_b64     |(c<<16)|(b<<8)|a; }

    inline void s_addk_u32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_add_u32 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_subk_u32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_sub_u32 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_rsubk_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_sub_u32 |(c<<16)|(b<<8)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void s_cselk_b32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_csel_b32|(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_cselk_b64( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_csel_b64|(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_andk_b32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_and_b32 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_andk_b64 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_and_b64 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_ork_b32  ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_or_b32  |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_ork_b64  ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_or_b64  |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_xork_b32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_xor_b32 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }
    inline void s_xork_b64 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_sop2|sop2_xor_b64 |(c<<16)|0xff00|a   ; kernel.instr[kernel.icode++]=b; }

    inline void s_cmp_i32 ( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_sopc|((0+op)<<16)|(b<<8)|a; }
    inline void s_cmp_u32 ( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_sopc|((6+op)<<16)|(b<<8)|a; }
    inline void s_cmpk_b32( uint32_t a,  int32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_sopc|(((b>=0?6:0)+op)<<16)|(a<<8)|0xff; kernel.instr[kernel.icode++]=int_as_uint(b); }

    inline void s_nop ( uint16_t n=0 ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_nop|(n&0xffff); }
    inline void s_bra ( uint16_t n   ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_bra|(n&0xffff); }
    inline void s_cbra_scc0     ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_scc0  |(n&0xffff); }
    inline void s_cbra_scc1     ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_scc1  |(n&0xffff); }
    inline void s_cbra_vccz     ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_vccz  |(n&0xffff); }
    inline void s_cbra_vccnz    ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_vccnz |(n&0xffff); }
    inline void s_cbra_execz    ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_execz |(n&0xffff); }
    inline void s_cbra_execnz   ( uint16_t n ){ kernel.ibranch[kernel.nbranches++]=kernel.icode; kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_execnz|(n&0xffff); }
    inline void s_branch        (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_bra        |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_scc0  (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_scc0  |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_scc1  (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_scc1  |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_vccz  (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_vccz  |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_vccnz (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_vccnz |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_execz (  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_execz |(int16_as_uint16(n)&0xffff); }
    inline void s_cbranch_execnz(  int16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_cbra_execnz|(int16_as_uint16(n)&0xffff); }
    inline void s_setprio       ( uint16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_setprio    |(int16_as_uint16(n)&0xffff); }
    inline void s_sync          ( uint16_t n ){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_sync|n; }
    inline void s_barrier       (){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_barrier; }
    inline void s_endp          (){ kernel.instr[kernel.icode++]=encoding_sopp|sopp_endp; kernel.relocate_branches(); }

    inline void s_lda_b32    ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b32 |0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=argofs+io; }
    inline void s_lda_b64    ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b64 |0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=argofs+io; }
    inline void s_lda_b128   ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b128|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=argofs+io; }
    inline void s_lda_b256   ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b256|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=argofs+io; }
    inline void s_lda_b512   ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b512|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=argofs+io; }
    inline void s_ld_b32     ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b32 |0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=io; }
    inline void s_ld_b64     ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b64 |0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=io; }
    inline void s_ld_b128    ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b128|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=io; }
    inline void s_ld_b256    ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b256|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=io; }
    inline void s_ld_b512    ( uint32_t dst , uint32_t base, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b512|0x20000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=io; }
    inline void s_ld_soe_b32 ( uint32_t dst , uint32_t base, uint32_t so ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b32 |0x00000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=so; }
    inline void s_ld_soe_b64 ( uint32_t dst , uint32_t base, uint32_t so ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b64 |0x00000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=so; }
    inline void s_ld_soe_b128( uint32_t dst , uint32_t base, uint32_t so ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b128|0x00000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=so; }
    inline void s_ld_soe_b256( uint32_t dst , uint32_t base, uint32_t so ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b256|0x00000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=so; }
    inline void s_ld_soe_b512( uint32_t dst , uint32_t base, uint32_t so ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b512|0x00000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=so; }
    inline void s_ld_soe_b32 ( uint32_t dst , uint32_t base, uint32_t so, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b32 |0x24000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=(so<<25)|io; }
    inline void s_ld_soe_b64 ( uint32_t dst , uint32_t base, uint32_t so, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b64 |0x24000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=(so<<25)|io; }
    inline void s_ld_soe_b128( uint32_t dst , uint32_t base, uint32_t so, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b128|0x24000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=(so<<25)|io; }
    inline void s_ld_soe_b256( uint32_t dst , uint32_t base, uint32_t so, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b256|0x24000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=(so<<25)|io; }
    inline void s_ld_soe_b512( uint32_t dst , uint32_t base, uint32_t so, uint32_t io ){ kernel.instr[kernel.icode++]=encoding_smem|smop_ld_b512|0x24000|(dst<<6)|(base>>1); kernel.instr[kernel.icode++]=(so<<25)|io; }
    
    inline void lsld_b32     ( uint32_t dst , uint32_t addr, uint32_t o ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b32 |o; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_b64     ( uint32_t dst , uint32_t addr, uint32_t o ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b64 |o; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_b96     ( uint32_t dst , uint32_t addr, uint32_t o ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b96 |o; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_b128    ( uint32_t dst , uint32_t addr, uint32_t o ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b128|o; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_b32x2   ( uint32_t dst , uint32_t addr, uint32_t o0, uint32_t o1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b32x2 |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_b64x2   ( uint32_t dst , uint32_t addr, uint32_t o0, uint32_t o1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ld_b64x2 |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }                                
    inline void lsldx_b32x2  ( uint32_t dst , uint32_t addr, uint32_t o0, uint32_t o1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ldx_b32x2|(o1<<8)|o0; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsldx_b64x2  ( uint32_t dst , uint32_t addr, uint32_t o0, uint32_t o1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_ldx_b64x2|(o1<<8)|o0; kernel.instr[kernel.icode++]=((dst-256)<<24)|(addr-256); }
    inline void lsld_lane_b32( uint32_t dst , uint32_t o   ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_laneld_b32|o; kernel.instr[kernel.icode++]=(dst-256)<<24; }
    inline void lsst_lane_b32( uint32_t o   , uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_lanest_b32|o; kernel.instr[kernel.icode++]=(src-256)<< 8; }
    inline void ls_append    ( uint32_t dst , uint32_t o   ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_append    |o; kernel.instr[kernel.icode++]=(dst-256)<<24; }
    inline void ls_consume   ( uint32_t dst , uint32_t o   ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_consume   |o; kernel.instr[kernel.icode++]=(dst-256)<<24; }
    inline void lsst_b32     ( uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b32 |o; kernel.instr[kernel.icode++]=((src-256)<<8)|(addr-256); }
    inline void lsst_b64     ( uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b64 |o; kernel.instr[kernel.icode++]=((src-256)<<8)|(addr-256); }
    inline void lsst_b96     ( uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b96 |o; kernel.instr[kernel.icode++]=((src-256)<<8)|(addr-256); }
    inline void lsst_b128    ( uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b128|o; kernel.instr[kernel.icode++]=((src-256)<<8)|(addr-256); }
    inline void lsst_b32x2   ( uint32_t addr, uint32_t o0, uint32_t dat0, uint32_t o1, uint32_t dat1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b32x2  |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dat1-256)<<16)|((dat0-256)<<8)|(addr-256); }
    inline void lsst_b64x2   ( uint32_t addr, uint32_t o0, uint32_t dat0, uint32_t o1, uint32_t dat1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_st_b64x2  |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dat1-256)<<16)|((dat0-256)<<8)|(addr-256); }
    inline void lsstx_b32x2  ( uint32_t addr, uint32_t o0, uint32_t dat0, uint32_t o1, uint32_t dat1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_stx_b32x2 |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dat1-256)<<16)|((dat0-256)<<8)|(addr-256); }
    inline void lsstx_b64x2  ( uint32_t addr, uint32_t o0, uint32_t dat0, uint32_t o1, uint32_t dat1 ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_stx_b64x2 |(o1<<8)|o0; kernel.instr[kernel.icode++]=((dat1-256)<<16)|((dat0-256)<<8)|(addr-256); }
    inline void ls_perm_b32  ( uint32_t dst , uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_perm_b32 |o; kernel.instr[kernel.icode++]=((dst-256)<<24)|((src-256)<<8)|(addr-256); }
    inline void ls_bperm_b32 ( uint32_t dst , uint32_t addr, uint32_t o, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_ds|dsop_bperm_b32|o; kernel.instr[kernel.icode++]=((dst-256)<<24)|((src-256)<<8)|(addr-256); }
    inline void ls_nop       (){ kernel.instr[kernel.icode++]=encoding_ds|dsop_nop; kernel.instr[kernel.icode++]=0; }

    inline void v_mov_b32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_mov_b32      <<9)|((b-256)<<17)|a; }
    inline void v_movk_b32     ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_mov_b32      <<9)|((b-256)<<17)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_readlane0_b32( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_readlane0_b32<<9)|( b     <<17)|a; }
    inline void v_cvt_f16_f32  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_cvt_f16_f32  <<9)|((b-256)<<17)|a; }
    inline void v_cvt_f32_i32  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_cvt_f32_u32  <<9)|((b-256)<<17)|a; }
    inline void v_cvt_f32_u32  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_cvt_f32_i32  <<9)|((b-256)<<17)|a; }
    inline void v_cvt_u32_f32  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_cvt_i32_f32  <<9)|((b-256)<<17)|a; }
    inline void v_cvt_i32_f32  ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_cvt_u32_f32  <<9)|((b-256)<<17)|a; }
    inline void v_rcp_f32      ( uint32_t b, uint32_t a ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_rcp_f32      <<9)|((b-256)<<17)|a; }
    inline void v_exch_b32     ( uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop1|(vop1_exch_b32     <<9)|((b-256)<<17)|a; }
    
    inline void v_cmov_b32   ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_cmov_b32   <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_add_f32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_add_f32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_sub_f32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_sub_f32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_mul_f32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mul_f32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_mul_u24    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mul_u24    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_mul_hi_u24 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mul_hi_u24 <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_min_f32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_min_f32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_max_f32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_max_f32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_and_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_and_b32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_or_b32     ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_or_b32     <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_xor_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_xor_b32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_add_co_u32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_add_co_u32 <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_sub_co_u32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_sub_co_u32 <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_rsub_co_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_rsub_co_u32<<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_addc_co_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_addc_co_u32<<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_subc_co_u32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_subc_co_u32<<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_add_u32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_add_u32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_sub_u32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_sub_u32    <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_rsub_u32   ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_rsub_u32   <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_shr_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_shr_b32    <<25)|((c-256)<<17)|((a-256)<<9)|(128u+b); }
    inline void v_shl_b32    ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_shl_b32    <<25)|((c-256)<<17)|((a-256)<<9)|(128u+b); }
    inline void v_dp2_i32_i16( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_dp2_i32_i16<<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_dp4_i32_i8 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_dp4_i32_i8 <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_dp8_i32_i4 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_dp8_i32_i4 <<25)|((c-256)<<17)|((b-256)<<9)|a; }
    inline void v_fmac_f16x2 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_fmac_f16x2 <<25)|((c-256)<<17)|((b-256)<<9)|a; }

    inline void v_dp2_f32_f16( uint32_t c, uint32_t a, uint32_t b ){
        if(((a|b)&0x200)==0){
            kernel.instr[kernel.icode++]=encoding_vop2|(vop2_dp2_f32_f16<<25)|((c-256)<<17)|((b-256)<<9)|a;
        } else {
            kernel.instr[kernel.icode++]=encoding_vop3|((vop2_dp2_f32_f16+0x100)<<16)|(c-256);
            kernel.instr[kernel.icode++]=vop_negmask(a,b,0)|(b<<9)|a;
        }
    }
    inline void v_mac_f32( uint32_t c, uint32_t a, uint32_t b ){
        if(((a|b)&0x200)==0){
            kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mac_f32<<25)|((c-256)<<17)|((b-256)<<9)|a;
        } else {
            kernel.instr[kernel.icode++]=encoding_vop3|((vop2_mac_f32+0x100)<<16)|(c-256);
            kernel.instr[kernel.icode++]=vop_negmask(a,b,0)|(b<<9)|a;
        }
    }
    inline void v_fmac_f32( uint32_t c, uint32_t a, uint32_t b ){
        if(((a|b)&0x200)==0){
            kernel.instr[kernel.icode++]=encoding_vop2|(vop2_fmac_f32<<25)|((c-256)<<17)|((b-256)<<9)|a;
        } else {
            kernel.instr[kernel.icode++]=encoding_vop3|((vop2_fmac_f32+0x100)<<16)|(c-256);
            kernel.instr[kernel.icode++]=vop_negmask(a,b,0)|(b<<9)|a;
        }
    }

    inline void v_cmov_b32   ( uint32_t c, uint32_t a, uint32_t b, uint32_t cc                ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_cmov_b32   )<<16)|(c-256); kernel.instr[kernel.icode++]=(cc<<18)|(b<<9)|a; }
    inline void v_add_co_u32 ( uint32_t vdst, uint32_t sdst, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_add_co_u32 )<<16)|(sdst<<8)|(vdst-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_sub_co_u32 ( uint32_t vdst, uint32_t sdst, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_sub_co_u32 )<<16)|(sdst<<8)|(vdst-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_rsub_co_u32( uint32_t vdst, uint32_t sdst, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_rsub_co_u32)<<16)|(sdst<<8)|(vdst-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_addc_co_u32( uint32_t vdst, uint32_t sdst, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_addc_co_u32)<<16)|(sdst<<8)|(vdst-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_subc_co_u32( uint32_t vdst, uint32_t sdst, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|((0x100+vop2_subc_co_u32)<<16)|(sdst<<8)|(vdst-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }

    inline void v_addk_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_add_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_subk_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_sub_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_mulk_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mul_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_mink_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_min_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_maxk_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_max_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_mack_f32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mac_f32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_cmovk_b32( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_cmov_b32<<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_mulk_u24 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_mul_u24 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_andk_b32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_and_b32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_ork_b32  ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_or_b32  <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_xork_b32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_xor_b32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_addk_u32 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop2|(vop2_add_u32 <<25)|((c-256)<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }

    inline void v_mad_i24        ( uint32_t d, int    a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mad_i24    |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|(a<0?(-a):a)|((a<0)<<29); }
    inline void v_mad_u24        ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mad_u24    |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_fma_f32        ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_fma_f32    |(d-256); kernel.instr[kernel.icode++]=vop_negmask(a,b,c)|((c&0x1ff)<<18)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_fma_f64        ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_fma_f64    |(d-256); kernel.instr[kernel.icode++]=vop_negmask(a,b,c)|((c&0x1ff)<<18)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_perm_b32       ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_perm_b32   |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_mad_u16        ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mad_u32_u16|(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_mad_u64_u32    ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mad_u64_u32|(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_add3_u32       ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_add3_u32   |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_or3_b32        ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_or3_b32    |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_and_or_b32     ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_and_or_b32 |(d-256); kernel.instr[kernel.icode++]=(c<<18)|(b<<9)|a; }
    inline void v_shl_add_u32    ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_shl_add_u32|(d-256); kernel.instr[kernel.icode++]=(c<<18)|((128u+b)<<9)|a; }
    inline void v_add_shl_u32    ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_add_shl_u32|(d-256); kernel.instr[kernel.icode++]=((128u+c)<<18)|(b<<9)|a; }
    inline void v_shl_or_b32     ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_shl_or_b32 |(d-256); kernel.instr[kernel.icode++]=(c<<18)|((128u+b)<<9)|a; }
    inline void v_mul_lo_u32     ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop_mul_lo_u32      |(d-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_mul_hi_u32     ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop_mul_hi_u32      |(d-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_mul_f64        ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mul_f64        |(d-256); kernel.instr[kernel.icode++]=vop_negmask(a,b,0)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_cvt_f16x2_f32x2( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_cvt_f16x2_f32x2|(d-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_shl_b64        ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_shl_b64        |(d-256); kernel.instr[kernel.icode++]=(a<<9)|b; }
    inline void v_shr_b64        ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_shr_b64        |(d-256); kernel.instr[kernel.icode++]=(a<<9)|b; }
    inline void v_mbcnt_lo_u32   ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mbcnt_lo_u32   |(d-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_mbcnt_hi_u32   ( uint32_t d, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_mbcnt_hi_u32   |(d-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_add_i32        ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_add_i32        |(c-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_sub_i32        ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_sub_i32        |(c-256); kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_pack_b32_f16x2 ( uint32_t c, uint32_t a, uint32_t b ){ kernel.instr[kernel.icode++]=encoding_vop3|vop3_pack_b32_f16x2 |(c-256); kernel.instr[kernel.icode++]=(b<<9)|a; }

    inline void v_min_f16x2  ( uint32_t d, uint32_t a, uint32_t b           ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_min_f16x2  |((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_max_f16x2  ( uint32_t d, uint32_t a, uint32_t b           ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_max_f16x2  |((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_add_f16x2  ( uint32_t d, uint32_t a, uint32_t b           ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_add_f16x2  |((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_mul_f16x2  ( uint32_t d, uint32_t a, uint32_t b           ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_mul_f16x2  |((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_fma_f16x2  ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_fma_f16x2  |((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|((c&0x4000)<<13)|((c&0x1ff)<<18)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_fma_f32_f16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_fma_f32_f16|((b&0x800)<<2)|(a&0x4800)|(d-256); kernel.instr[kernel.icode++]=((b&0x4000)<<14)|(c<<18)|((b&0x1ff)<<9)|(a&0x1ff); }
    inline void v_dp2_f32_f16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp2_f32_f16|0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp2_i32_i16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp2_i32_i16|0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp2_u32_u16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp2_u32_u16|0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp4_i32_i8 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp4_i32_i8 |0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp4_u32_u8 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp4_u32_u8 |0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp8_i32_i4 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp8_i32_i4 |0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }
    inline void v_dp8_u32_u4 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_vopp|vopp_dp8_u32_u4 |0x4000|(d-256); kernel.instr[kernel.icode++]=0x18000000|(c<<18)|(b<<9)|a; }

    inline void v_cmp_u32 ( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vopc|((vopc_cmp_u32 +ivcmpop[op])<<17)|((b-256)<<9)|a; }
    inline void v_cmpx_u32( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vopc|((vopc_cmpx_u32+ivcmpop[op])<<17)|((b-256)<<9)|a; }
    inline void v_cmp_i32 ( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vopc|((vopc_cmp_i32 +ivcmpop[op])<<17)|((b-256)<<9)|a; }
    inline void v_cmpk_u32( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vopc|((vopc_cmp_u32+ivcmpop[op])<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_cmpk_i32( uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vopc|((vopc_cmp_i32+ivcmpop[op])<<17)|((b-256)<<9)|0xff; kernel.instr[kernel.icode++]=a; }
    inline void v_cmp_u32 ( uint32_t cc, uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vop3|((vopc_cmp_u32+ivcmpop[op])<<16)|cc; kernel.instr[kernel.icode++]=(b<<9)|a; }
    inline void v_cmp_i32 ( uint32_t cc, uint32_t a, uint32_t b, uint32_t op ){ kernel.instr[kernel.icode++]=encoding_vop3|((vopc_cmp_i32+ivcmpop[op])<<16)|cc; kernel.instr[kernel.icode++]=(b<<9)|a; }

    inline void ldg_b32 ( uint32_t vdst, uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b032|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void ldg_b64 ( uint32_t vdst, uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b064|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void ldg_b96 ( uint32_t vdst, uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b096|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void ldg_b128( uint32_t vdst, uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b128|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void stg_b32 ( uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b032|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void stg_b64 ( uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b064|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void stg_b96 ( uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b096|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }
    inline void stg_b128( uint32_t sbase, uint32_t vofs, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b128|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|((flag&0x2u)<<22)|(sbase<<16)|(vofs-256); }

    inline void ldg_bi_b32 ( uint32_t vdst, uint32_t vptr, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b032|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void ldg_bi_b64 ( uint32_t vdst, uint32_t vptr, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b064|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void ldg_bi_b96 ( uint32_t vdst, uint32_t vptr, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b096|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void ldg_bi_b128( uint32_t vdst, uint32_t vptr, uint32_t iofs, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_ld_b128|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vdst-256)<<24)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void stg_bi_b32 ( uint32_t vptr, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b032|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void stg_bi_b64 ( uint32_t vptr, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b064|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void stg_bi_b96 ( uint32_t vptr, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b096|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }
    inline void stg_bi_b128( uint32_t vptr, uint32_t iofs, uint32_t vsrc, uint32_t flag=0 ){ kernel.instr[kernel.icode++]=encoding_global|vmop_st_b128|((flag&0x1u)<<16)|(iofs&0x1fff); kernel.instr[kernel.icode++]=((vsrc-256)<< 8)|0x7f0000|((flag&0x2u)<<22)|(vptr-256); }

    inline void v_movout_b32( uint32_t dst, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_mma|vopp_movout_b32|(dst-256); kernel.instr[kernel.icode++]=src; }
    inline void v_movin_b32 ( uint32_t dst, uint32_t src ){ kernel.instr[kernel.icode++]=encoding_mma|vopp_movin_b32 |(dst-256); kernel.instr[kernel.icode++]=src; }
    inline void mma_32x32x1_f32_f32 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma02b16p_32x32x01_f32_f32|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_32x32x2_f32_f32 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b16p_32x32x02_f32_f32|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_32x32x4_f32_f16 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma02b16p_32x32x04_f32_f16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_32x32x8_f32_f16 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b16p_32x32x08_f32_f16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_32x32x2_f32_bf16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma02b16p_32x32x02_f32_b16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_32x32x4_f32_bf16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b16p_32x32x04_f32_b16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x1_f32_f32 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma04b08p_16x16x01_f32_f32|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x4_f32_f32 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b08p_16x16x04_f32_f32|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x4_f32_f16 ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma04b08p_16x16x04_f32_f16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x16_f32_f16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b08p_16x16x16_f32_f16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x2_f32_bf16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma04b08p_16x16x02_f32_b16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_16x16x8_f32_bf16( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma01b08p_16x16x08_f32_b16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_4x4x1_f32_f32   ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma16b02p_04x04x01_f32_f32|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_4x4x4_f32_f16   ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma16b02p_04x04x04_f32_f16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }
    inline void mma_4x4x2_f32_bf16  ( uint32_t d, uint32_t a, uint32_t b, uint32_t c ){ kernel.instr[kernel.icode++]=encoding_mma|opc_mma16b02p_04x04x02_f32_b16|(d-256); kernel.instr[kernel.icode++]=(((b<<1)|a)&0x18000000)|(c<<18)|(((b<<9)|a)&0x3ffff); }

private:
    void (gfxcoder::*p_routine[128])();
    void (gfxcoder::*p_routine_mask[128])( uint32_t );
    void (gfxcoder::*p_routine_fft4x4_static[4])( uint32_t );
    void (gfxcoder::*p_routine_fft5x5_static[4])( uint32_t );

private:
    vector<string> knames;
    metadata_t*    metadata;
    kernelOb       kernel;
    uint32_t       argofs;
    uint32_t       nroutines;
    uint32_t       nroutines_mask;
    uint32_t       arch;
};

#endif
