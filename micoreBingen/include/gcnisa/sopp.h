#ifndef __sopp_h__
#define __sopp_h__

#define encoding_sopp 0xbf800000u

#define vmcnt(n)   (0x0f70|((((n)&0x30)<<10)|((n)&0xf)))
#define lgkmcnt(n) (0xc07f|(((n)&0xf)<<8))

#define sopp_nop               ( 0u<<16)
#define sopp_endp              ( 1u<<16)
#define sopp_bra               ( 2u<<16)
#define sopp_cbra_scc0         ( 4u<<16)
#define sopp_cbra_scc1         ( 5u<<16)
#define sopp_cbra_vccz         ( 6u<<16)
#define sopp_cbra_vccnz        ( 7u<<16)
#define sopp_cbra_execz        ( 8u<<16)
#define sopp_cbra_execnz       ( 9u<<16)
#define sopp_barrier           (10u<<16)
#define sopp_sync              (12u<<16)
#define sopp_setprio           (15u<<16)
#define sopp_off_vgpr_idx      (28u<<16)
#define sopp_set_vgpr_idx_mode (29u<<16)

#endif