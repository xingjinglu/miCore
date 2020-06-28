#ifndef __kernelOb_h__
#define __kernelOb_h__

#include"pgmrsrc.h"

#define iceil(a,b) (((a)>>(b))+(((a)&((1<<(b))-1))!=0))
#define imax(a,b)  ((a)>(b)?(a):(b))
#define DESCR(p)   reinterpret_cast<kernel_descr_t*>(p)

struct kernel_descr_t{
    uint32_t group_segment_size;
    uint32_t private_segment_size;
    uint8_t  rev0[8];
    uint64_t kernel_code_entry_offset;
    uint8_t  rev1[20];
    uint32_t compute_pgmrsrc3;
    uint32_t compute_pgmrsrc1;
    uint32_t compute_pgmrsrc2;
    uint16_t kernel_code_prop;
    uint8_t  rev2[6];
};

struct kernelOb
{
    inline kernelOb():icode(0){}
    inline kernelOb( uint8_t* p ):descr(p),icode(0){}
	inline void start_descr(){
        descr+=(icode<<2);
        instr=reinterpret_cast<uint32_t*>(descr+64);
        for( int i=0; i<64; i+=8 ){ *reinterpret_cast<uint64_t*>(&descr[i])=0x0000000000000000ul; }
    }
    inline void end_descr(){ icode=nbranches=0; descr+=64; }

    inline void set_lds_size    ( uint32_t n ){ DESCR(descr)->group_segment_size=n; }
    inline void set_private_size( uint32_t n ){ DESCR(descr)->private_segment_size=n; }
    inline void set_entry_offset( uint64_t o ){ DESCR(descr)->kernel_code_entry_offset=o; }

    inline void set_vregcnt              ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(imax(iceil(n,2),0)-1); }
    inline void set_sregcnt              ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(((imax(iceil(n,4),0)<<1)-1)<<6); }
    inline void set_fp32_mode_round      ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(n<<12); }
    inline void set_fp16_fp64_mode_round ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(n<<14); }
    inline void set_fp32_mode_denorm     ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(n<<16); }
    inline void set_fp16_fp64_mode_denorm( uint32_t n ){ DESCR(descr)->compute_pgmrsrc1|=(n<<18); }
    inline void enable_dx10_clamp        (            ){ DESCR(descr)->compute_pgmrsrc1|=(1<<21); }
    inline void enable_ieee_mode         (            ){ DESCR(descr)->compute_pgmrsrc1|=(1<<23); }

    inline void enable_sgpr_private_segment_ofs(            ){ DESCR(descr)->compute_pgmrsrc2|=1; }
    inline void set_user_sgprcnt               ( uint32_t n ){ DESCR(descr)->compute_pgmrsrc2|=(n<< 1); }
    inline void enable_sgpr_group_id_x         (            ){ DESCR(descr)->compute_pgmrsrc2|=(1<< 7); }
    inline void enable_sgpr_group_id_y         (            ){ DESCR(descr)->compute_pgmrsrc2|=(1<< 8); }
    inline void enable_sgpr_group_id_z         (            ){ DESCR(descr)->compute_pgmrsrc2|=(1<< 9); }
    inline void enable_group_info              (            ){ DESCR(descr)->compute_pgmrsrc2|=(1<<10); }
    inline void enable_vgpr_iterm_id_1d        (            ){ DESCR(descr)->compute_pgmrsrc2|=(amdgpu_vgpr_itermid_1d<<11); }
    inline void enable_vgpr_iterm_id_2d        (            ){ DESCR(descr)->compute_pgmrsrc2|=(amdgpu_vgpr_itermid_2d<<11); }
    inline void enable_vgpr_iterm_id_3d        (            ){ DESCR(descr)->compute_pgmrsrc2|=(amdgpu_vgpr_itermid_3d<<11); }

    inline void enable_private_segment     (){ DESCR(descr)->kernel_code_prop|=0x01; }
    inline void enable_dispach_ptr         (){ DESCR(descr)->kernel_code_prop|=0x02; }
    inline void enable_queue_ptr           (){ DESCR(descr)->kernel_code_prop|=0x04; }
    inline void enable_kernarg_segment     (){ DESCR(descr)->kernel_code_prop|=0x08; }
    inline void enable_dispach_id          (){ DESCR(descr)->kernel_code_prop|=0x10; }
    inline void enable_flat_scratch_init   (){ DESCR(descr)->kernel_code_prop|=0x20; }
    inline void enable_private_segment_size(){ DESCR(descr)->kernel_code_prop|=0x40; }

    void relocate_branches();

    uint32_t  ibranch[128];
    uint32_t  ilable[128];
    uint8_t * descr;
    uint32_t* instr;
    uint32_t  icode;
    uint32_t  nbranches;
};

#endif