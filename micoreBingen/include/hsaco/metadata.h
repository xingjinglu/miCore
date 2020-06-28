#ifndef __metadata__
#define __metadata__

#include<stdint.h>

struct arginfo_t{
    uint8_t size;
    uint8_t offs;
    uint8_t kind;
    uint8_t type;
};

struct metadata_t{
    uint32_t  lds_size;
    uint32_t  kernarg_align;
    uint32_t  kernarg_size;
    uint32_t  private_size;
    uint32_t  group_size;
    uint32_t  wave_size;
    uint32_t  sgprcnt;
    uint32_t  vgprcnt;
    uint32_t  nargs;
    arginfo_t args[32];
};

#define arg_kind_direct 0x0
#define arg_kind_globuf 0x1
#define arg_type_u32    0x0
#define arg_type_u64    0x1
#define arg_type_f32    0x2
#define arg_type_f64    0x3
#define arg_type_f16    0x4
#define arg_type_bf16   0x5

#endif