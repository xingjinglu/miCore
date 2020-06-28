#ifndef __vmem_h__
#define __vmem_h__

#define encoding_global 0xdc008000u

#define glc 0x1u
#define nv  0x2u

#define vmop_ld_b032 (20u<<18)
#define vmop_ld_b064 (21u<<18)
#define vmop_ld_b096 (22u<<18)
#define vmop_ld_b128 (23u<<18)
#define vmop_st_b032 (28u<<18)
#define vmop_st_b064 (29u<<18)
#define vmop_st_b096 (30u<<18)
#define vmop_st_b128 (31u<<18)

#endif