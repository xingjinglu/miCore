#ifndef __elf_h__
#define __elf_h__

#include<cstdint>
#include"strop.h"

#define ELF_ID 0x464c457f

#define EI_CLASS      4
#define EI_DATA       5
#define EI_VERSION    6
#define EI_OSABI      7
#define EI_ABIVERSION 8
#define EI_PAD        9

#define ELFCLASSNONE              0
#define ELFCLASS32                1
#define ELFCLASS64                2
#define ELFDATANONE               0
#define ELFDATA2LSB               1
#define ELFOSABI_NONE             0
#define ELFOSABI_AMDGPU_HSA      64
#define ELFOSABI_AMDGPU_PAL      65
#define ELFABIVERSION_AMDGPU_HSA  1
#define ELFABIVERSION_AMDGPU_PAL  0

#define ET_NONE   0x0000
#define ET_REL    0x0001
#define ET_EXEC   0x0002
#define ET_DYN    0x0003
#define ET_CORE   0x0004
#define ET_LOOS   0xfe00
#define ET_HIOS   0xfeff
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

#define EM_NONE   0x00
#define EM_X86_64 0x3e
#define EM_AMDGPU 0xe0

#define EF_AMDGPU_MACH        0x000000ff
#define EF_AMDGPU_XNACK       0x00000100
#define EF_AMDGPU_SRAM_ECC    0x00000200
#define EF_AMDGPU_MACH_GFX900 0x0000002c
#define EF_AMDGPU_MACH_GFX902 0x0000002d
#define EF_AMDGPU_MACH_GFX904 0x0000002e
#define EF_AMDGPU_MACH_GFX906 0x0000002f
#define EF_AMDGPU_MACH_GFX908 0x00000030
#define EF_AMDGPU_MACH_GFX909 0x00000031

#define EV_NONE    0
#define EV_CURRENT 1

#define PT_NONE      0x00000000
#define PT_LOAD      0x00000001
#define PT_DYNAMIC   0x00000002
#define PT_INTERP    0x00000003
#define PT_NOTE      0x00000004
#define PT_PHDR      0x00000006
#define PT_LOOS      0x60000000
#define PT_HIOS      0x6fffffff
#define PT_LOPROC    0x70000000
#define PT_HIPROC    0x7fffffff
#define PT_GNU_STACK 0x6474e551
#define PT_GNU_RELRO 0x6474e552

#define PF_X     0x00000001
#define PF_W     0x00000002
#define PF_R     0x00000004
#define PF_MOS   0x0ff00000
#define PF_MPROC 0xf0000000

#define SHT_NULL     0x00000000
#define SHT_PROGBITS 0x00000001
#define SHT_SYMTAB   0x00000002
#define SHT_STRTAB   0x00000003
#define SHT_NOTE     0x00000007
#define SHT_NOBITS   0x00000008
#define SHT_LOOS     0x60000000
#define SHT_HIOS     0x6fffffff
#define SHT_LOPROC   0x8fffffff
#define SHT_HIPROC   0xffffffff

#define SHF_WRITE     0x00000001
#define SHF_ALLOC     0x00000002
#define SHF_EXECINSTR 0x00000004
#define SHF_STRINGS   0x00000020
#define SHF_MPROC     0xf0000000

#define SHN_UNDEF     0x0000
#define SHN_LOREVERSE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_LOOS      0xff20
#define SHN_HIOS      0xff3f
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_XINDEX    0xffff
#define SHN_HIREVERSE 0xffff

#define STT_NOTYPE            0x0
#define STT_OBJECT            0x1
#define STT_FUNC              0x2
#define STT_SECTION           0x3
#define STT_FILE              0x4
#define STT_COMMON            0x5
#define STT_LOOS              0xa
#define STT_HIOS              0xc
#define STT_LOPROC            0xd
#define STT_HIPROC            0xf
#define STT_AMDGPU_HSA_KERNEL 0xa

#define STB_LOCAL      0x0
#define STB_GLOBAL     0x1
#define STB_WEAK       0x2
#define STB_NUM        0x3
#define STB_LOOS       0xa
#define STB_GNU_UNIQUE 0xa
#define STB_HIOS       0xc
#define STB_LOPROC     0xd
#define STB_HIPROC     0xf

#define ELF_ST_BIND(n)         (((uint8_t)(n))>>4)
#define ELF_ST_TYPE(n)         ((n)&0xf)
#define ELF_ST_INFO(bind,type) (((bind)<<4)+((type)&0xf))

#define STV_DEFAULT   0
#define STV_INTERNAL  1
#define STV_HIDDEN    2
#define STV_PROTECTED 3

#define ELF_ST_VIS(n) ((n)&0x3)

#define NT_AMD_AMDGPU_HSA_METADATA 10
#define NT_AMD_AMDGPU_ISA          11
#define NT_AMDGPU_METADATA         32

typedef struct{
    uint8_t  ident[16];
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint64_t entry;
    uint64_t phoff;
    uint64_t shoff;
    uint32_t flag;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phcnt;
    uint16_t shentsize;
    uint16_t shcnt;
    uint16_t shstrndx;
} elf64_ehdr;

typedef struct{
    uint32_t type;
    uint32_t flags;
    uint64_t offset;
    uint64_t vaddr;
    uint64_t paddr;
    uint64_t filenb;
    uint64_t memnb;
    uint64_t align;
} elf64_phdr;

typedef struct{
    uint32_t name;
    uint32_t type;
    uint64_t flags;
    uint64_t addr;
    uint64_t offset;
    uint64_t size;
    uint32_t link;
    uint32_t info;
    uint64_t align;
    uint64_t entsize;
} elf64_shdr;

typedef struct{
    uint32_t name;
    uint8_t  info;
    uint8_t  other;
    uint16_t shndx;
    uint64_t value;
    uint64_t size;
} elf64_sym;

typedef struct{
    uint32_t name;
    uint32_t desc;
    uint32_t type;
} elf64_nhdr;

#endif