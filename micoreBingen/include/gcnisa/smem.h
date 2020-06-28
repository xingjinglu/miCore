#ifndef __smem_h__
#define __smem_h__

#define encoding_smem 0xc0000000u

#define smop_ld_b32       (0u<<18)
#define smop_ld_b64       (1u<<18)
#define smop_ld_b128      (2u<<18)
#define smop_ld_b256      (3u<<18)
#define smop_ld_b512      (4u<<18)
#define smop_atom_exch    (128u<<18)
#define smop_atom_cmpexch (129u<<18)
#define smop_atom_add     (130u<<18)
#define smop_atom_sub     (131u<<18)
#define smop_atom_smin    (132u<<18)
#define smop_atom_umin    (133u<<18)
#define smop_atom_smax    (134u<<18)
#define smop_atom_umax    (135u<<18)
#define smop_atom_and     (136u<<18)
#define smop_atom_or      (137u<<18)
#define smop_atom_xor     (138u<<18)
#define smop_atom_inc     (139u<<18)
#define smop_atom_dec     (140u<<18)

#endif