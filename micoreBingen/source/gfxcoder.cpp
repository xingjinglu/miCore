#include"../include/gfxcoder.h"

#define MAX_ENTRIES 1024
#define MAX_ENTRY_SIZE 64
#define ADD_ROUTINE(name){ p_routine[nroutines++]=&gfxcoder::name; knames.push_back(#name); }
#define ADD_MROUTINE(name){ p_routine_mask[nroutines_mask++]=&gfxcoder::name; }
#define ADD_MROUTINEX(name){ p_routine_mask[nroutines_mask++]=&gfxcoder::name; knames.push_back(#name); knames.push_back(#name##"_relu"); }
#define ADD_ROUTINE_FFT(cell,i,p){ p_routine_fft##cell##x##cell##_static[i]=&gfxcoder::p; }

gfxcoder::gfxcoder():nroutines(0),nroutines_mask(0),argofs(0)
{
    knames.reserve(MAX_ENTRIES);
    for_each( knames.begin(), knames.end(), []( string& str ){ str.reserve(MAX_ENTRY_SIZE); } );
    ADD_ROUTINE( padding2d );
    ADD_ROUTINE( perm_flip );
    ADD_ROUTINE( genidx_co2d );
    ADD_ROUTINE( sbco7x4 );
    ADD_ROUTINE( sbco8x5 );
    ADD_ROUTINE( sbco8x6 );
    ADD_ROUTINE( sbco7x7 );
    ADD_ROUTINE( sufbco7x4_om );
    ADD_ROUTINE( sufbco7x4_dm );
    ADD_ROUTINE( sufbco7x4_qm );
    ADD_ROUTINE( sufbco8x5_om );
    ADD_ROUTINE( sufbco8x5_dm );
    ADD_ROUTINE( sufbco8x5_qm );
    ADD_ROUTINE( sufbco8x6_om );
    ADD_ROUTINE( sufbco8x6_dm );
    ADD_ROUTINE( sufbco8x6_qm );
    ADD_ROUTINE( sufbco7x7_om );
    ADD_ROUTINE( sufbco7x7_dm );
    ADD_ROUTINE( sufbco7x7_qm );
    ADD_ROUTINE( sgemm6x5 );
    ADD_ROUTINE( sgemm7x5 );
    ADD_ROUTINE( sgemm8x5 );
    ADD_ROUTINE( sgemm6x6 );
    ADD_ROUTINE( sgemm7x6 );
    ADD_ROUTINE( sgemm8x6 );
    ADD_ROUTINE( sgemm7x7 );
    ADD_ROUTINE( sco3x3q6_dta );
    ADD_ROUTINE( sco3x3q6_dtx );
    ADD_ROUTINE( sco3x3q6_dtp );
    ADD_ROUTINE( scgemm5x4    );
    ADD_ROUTINE( scgemm5x4_ck );
    ADD_ROUTINE( scgemm5x5    );
    ADD_ROUTINE( scgemm5x5_ck );
    ADD_ROUTINE( scgemm5x6    );
    ADD_ROUTINE( scgemm5x6_ck );
    ADD_ROUTINE( scgemm6x4    );
    ADD_ROUTINE( scgemm6x4_ck );
    ADD_ROUTINE( scgemm6x5    );
    ADD_ROUTINE( scgemm6x5_ck );
    ADD_ROUTINE( scgemm6x6    );
    ADD_ROUTINE( scgemm6x6_ck );
    ADD_ROUTINE( sfft4x4_r2c_perm_s3x3 );
    ADD_ROUTINE( sfft4x4_r2c_perm_s5x5 );
    ADD_ROUTINE( sfft4x4_r2c_qerm_s3x3 );
    ADD_ROUTINE( sfft4x4_r2c_qerm_s5x5 );
    ADD_ROUTINE( sfft4x4_r2c_grid_perm );
    ADD_ROUTINE( sfft4x4_r2c_grid_perm_ex );
    ADD_ROUTINE( sfft4x4_r2c_grid_perm_pad );
    ADD_ROUTINE( sfft4x4_r2c_grad );
    ADD_ROUTINE( sfft4x4_r2c_grad_ex );
    ADD_ROUTINE( sfft4x4_r2c_grad_pad );
    ADD_ROUTINE( sfft4x4_r2c_grad_nov );
    ADD_ROUTINE( sfft4x4_c2r_g3x1 );
    ADD_ROUTINE( sfft4x4_c2r_g5x1 );
    ADD_ROUTINE( sfft4x4_c2r_g7x1 );
    ADD_ROUTINE( sfft4x4_c2r_g9x1 );
    ADD_ROUTINE( sfft4x4_c2r_g1x3 );
    ADD_ROUTINE( sfft4x4_c2r_g1x5 );
    ADD_ROUTINE( sfft4x4_c2r_g1x7 );
    ADD_ROUTINE( sfft4x4_c2r_g1x9 );
    ADD_ROUTINE( sfft4x4_c2r_g3x3 );
    ADD_ROUTINE( sfft4x4_c2r_g5x5 );
    ADD_ROUTINE( sfft4x4_c2r_g7x7 );
    ADD_ROUTINE( sfft5x5_r2c_perm_s3x3 );
    ADD_ROUTINE( sfft5x5_r2c_perm_s5x5 );
    ADD_ROUTINE( sfft5x5_r2c_qerm_s3x3 );
    ADD_ROUTINE( sfft5x5_r2c_qerm_s5x5 );
    ADD_ROUTINE( sfft5x5_r2c_grid_perm );
    ADD_ROUTINE( sfft5x5_r2c_grid_perm_ex );
    ADD_ROUTINE( sfft5x5_r2c_grid_perm_pad );
    ADD_ROUTINE( sfft5x5_r2c_grad );
    ADD_ROUTINE( sfft5x5_r2c_grad_ex );
    ADD_ROUTINE( sfft5x5_r2c_grad_pad );
    ADD_ROUTINE( sfft5x5_r2c_grad_nov );
    ADD_ROUTINE( sfft5x5_c2r_g3x1 );
    ADD_ROUTINE( sfft5x5_c2r_g5x1 );
    ADD_ROUTINE( sfft5x5_c2r_g7x1 );
    ADD_ROUTINE( sfft5x5_c2r_g9x1 );
    ADD_ROUTINE( sfft5x5_c2r_g1x3 );
    ADD_ROUTINE( sfft5x5_c2r_g1x5 );
    ADD_ROUTINE( sfft5x5_c2r_g1x7 );
    ADD_ROUTINE( sfft5x5_c2r_g1x9 );
    ADD_ROUTINE( sfft5x5_c2r_g3x3 );
    ADD_ROUTINE( sfft5x5_c2r_g5x5 );
    ADD_ROUTINE( sfft5x5_c2r_g7x7 );

    ADD_MROUTINEX( suffco7x4_om );
    ADD_MROUTINEX( suffco7x4_dm );
    ADD_MROUTINEX( suffco7x4_qm );
    ADD_MROUTINEX( suffco8x5_om );
    ADD_MROUTINEX( suffco8x5_dm );
    ADD_MROUTINEX( suffco8x5_qm );
    ADD_MROUTINEX( suffco8x6_om );
    ADD_MROUTINEX( suffco8x6_dm );
    ADD_MROUTINEX( suffco8x6_qm );
    ADD_MROUTINEX( suffco7x7_om );
    ADD_MROUTINEX( suffco7x7_dm );
    ADD_MROUTINEX( suffco7x7_qm );
    ADD_MROUTINEX( sfco    );
    ADD_MROUTINEX( sfco7x4 );
    ADD_MROUTINEX( sfco8x5 );
    ADD_MROUTINEX( sfco8x6 );
    ADD_MROUTINEX( sfco7x7 );
    ADD_MROUTINE( sco3x3q6_xft );
    knames.push_back("sco3x3q6_fft");
    knames.push_back("sco3x3q6_bft");
    ADD_MROUTINEX( sco3x3q6_ota );
    ADD_MROUTINEX( sco3x3q6_otx );
    ADD_MROUTINEX( sfft4x4_c2r_grid_perm );
    ADD_MROUTINEX( sfft5x5_c2r_grid_perm );

    ADD_ROUTINE_FFT(4,0,sfft4x4_r2c_perm);
    for( int i=0; i<16; ([this]( int n ){ knames.push_back(string("sfft4x4_r2c_perm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(4,1,sfft4x4_r2c_perm_flip);
    for( int i=0; i<16; ([this]( int n ){ knames.push_back(string("sfft4x4_r2c_qerm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(4,2,sfft4x4_r2c_perm_pad);
    for( int i=0; i<16; ([this]( int n ){ knames.push_back(string("sfft4x4_r2c_perm_p")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(4,3,sfft4x4_c2r_perm);
    for( int i=0; i<16; ([this]( int n ){ knames.push_back(string("sfft4x4_c2r_perm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    for( int i=0; i<16; ([this]( int n ){ knames.push_back(string("sfft4x4_c2r_perm_v")+string("_relu")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(5,0,sfft5x5_r2c_perm);
    for( int i=0; i<32; ([this]( int n ){ knames.push_back(string("sfft5x5_r2c_perm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(5,1,sfft5x5_r2c_perm_flip);
    for( int i=0; i<32; ([this]( int n ){ knames.push_back(string("sfft5x5_r2c_qerm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(5,2,sfft5x5_r2c_perm_pad);
    for( int i=0; i<32; ([this]( int n ){ knames.push_back(string("sfft5x5_r2c_perm_p")+string((n<10?"0":""))+to_string(n)); })(++i) );
    ADD_ROUTINE_FFT(5,3,sfft5x5_c2r_perm);
    for( int i=1; i<32; ([this]( int n ){ knames.push_back(string("sfft5x5_c2r_perm_v")+string((n<10?"0":""))+to_string(n)); })(++i) );
    for( int i=1; i<32; ([this]( int n ){ knames.push_back(string("sfft5x5_r2c_perm_v")+string("_relu")+string((n<10?"0":""))+to_string(n)); })(++i) );
}
gfxcoder::~gfxcoder()
{
    for_each( knames.begin(), knames.end(), []( string& str ){ string().swap(str); } );
    vector<string>().swap(knames);
}
void gfxcoder::gen( uint8_t* addr, uint32_t* cosizes )
{
    uint32_t nkern=nroutines+(nroutines_mask<<1);
    metadata=reinterpret_cast<metadata_t*>(addr);
    kernel.descr=addr+nkern*sizeof(metadata_t);
    for( uint32_t i=0; i<nroutines; ++i ){
        (this->*p_routine[i])();
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<nroutines_mask<<1; ++i ){
        (this->*p_routine_mask[i>>1])(i&1);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<16; ++i ){
        (this->*p_routine_fft4x4_static[0])(i+1);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<16; ++i ){
        (this->*p_routine_fft4x4_static[1])(i+1);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<16; ++i ){
        (this->*p_routine_fft4x4_static[2])(i);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<32; ++i ){
        (this->*p_routine_fft4x4_static[3])(((i>>4)<<8)|(i&15));
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<32; ++i ){
        (this->*p_routine_fft5x5_static[0])(i+1);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<32; ++i ){
        (this->*p_routine_fft5x5_static[1])(i+1);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<32; ++i ){
        (this->*p_routine_fft5x5_static[2])(i);
        *cosizes++=kernel.icode<<2;
    }
    for( uint32_t i=0; i<64; ++i ){
        (this->*p_routine_fft5x5_static[3])(((i>>5)<<8)|(i&31));
        *cosizes++=kernel.icode<<2;
    }
}
const vector<string>& gfxcoder::kernel_names() const
{
    return knames;
}
void gfxcoder::metadata_start()
{
    metadata->lds_size=0;
    metadata->private_size=0;
    metadata->wave_size=64;
}
void gfxcoder::metadata_set_lds_size( uint32_t n )
{
    metadata->lds_size=n;
}
void gfxcoder::metadata_set_kernarg_align( uint32_t n )
{
    metadata->kernarg_align=n;
}
void gfxcoder::metadata_set_kernarg_size( uint32_t n )
{
    metadata->kernarg_size=n;
}
void gfxcoder::metadata_set_private_size( uint32_t n )
{
    metadata->private_size=n;
}
void gfxcoder::metadata_set_group_size( uint32_t n )
{
    metadata->group_size=n;
}
void gfxcoder::metadata_set_wave_size( uint32_t n )
{
    metadata->wave_size=n;
}
void gfxcoder::metadata_set_sgprcnt( uint32_t n )
{
    metadata->sgprcnt=n;
}
void gfxcoder::metadata_set_vgprcnt( uint32_t n )
{
    metadata->vgprcnt=n;
}
void gfxcoder::metadata_set_arg( uint8_t size, uint8_t offs, uint8_t kind, uint8_t type )
{
    metadata->args[argidx++]={size,offs,kind,type};
}
void gfxcoder::metadata_end()
{
    ++metadata;
}
void gfxcoder::alignib()
{
    int padding=kernel.icode&15;
    if(padding>0){
        s_branch(padding-1);
        for( int i=0; i<padding-1; ++i ){ kernel.instr[kernel.icode++]=0; }
    }
}
void gfxcoder::dpp_srr_b32( uint32_t dst, uint32_t src, uint32_t n )
{
    v_mov_b32(dst,dpp);
    kernel.instr[kernel.icode++]=DPP(src,0x120+n,1,0xf,0xf);
}
void gfxcoder::dpp_ror_b32( uint32_t dst, uint32_t src, uint32_t n )
{
    uint32_t ctrl=0x13f+n;
    v_mov_b32(dst,dpp);
    kernel.instr[kernel.icode++]=DPP(src,ctrl,1,0xf,0xf);
}
void gfxcoder::dpp_shf_xor_b32( uint32_t dst, uint32_t src, uint32_t n )
{
    uint32_t ctrl=n==1?0xb1:0x4e;
    v_mov_b32(dst,dpp);
    kernel.instr[kernel.icode++]=DPP(src,ctrl,1,0xf,0xf);
}