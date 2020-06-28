#include"../../include/hsaco/generator.h"
#include"../../include/hsaco/msgpack.h"

#define MAX_BUF_SIZE   64
#define alignment(n,m) (((n)+(m)-1)&(~((m)-1)))
#define ELF_EHDR(ptr)  reinterpret_cast<elf64_ehdr*>(ptr)
#define ELF_PHDR(ptr)  reinterpret_cast<elf64_phdr*>(&ptr[ELF_EHDR(ptr)->phoff])
#define ELF_SHDR(ptr)  reinterpret_cast<elf64_shdr*>(&ptr[ELF_EHDR(ptr)->shoff])
#define ELF_NHDR(ptr)  reinterpret_cast<elf64_nhdr*>(ptr)

const char generator::k_note_name[]={'A','M','D','G','P','U','\0'};
const uint8_t generator::k_amdhsa_version[]={1,0};
const char* generator::k_kind[]={"by_value","global_buffer"};
const char* generator::k_type[]={"u32","u64","f32","f64","f16"};
uint32_t generator::required_size( const metadata_t* meta, const uint32_t* cosizes, const vector<string>& knames )
{
    nkern=static_cast<uint32_t>(knames.size());
    sinfo[inote].size=get_section_size_note( meta, cosizes, knames );
    sinfo[irodt].size=get_section_size_rodata();
    sinfo[itext].size=get_section_size_text( cosizes );
    sinfo[isymt].size=get_section_size_symtab();
    sinfo[ishst].size=get_section_size_shstrtab();
    sinfo[istrt].size=get_section_size_strtab( knames );
    sinfo[inote].offs=alignment((sizeof(elf64_ehdr)+4*sizeof(elf64_phdr)),4);
    sinfo[irodt].offs=alignment((sinfo[inote].offs+sinfo[inote].size),0x40);
    sinfo[itext].offs=alignment((sinfo[irodt].offs+sinfo[irodt].size),0x1000);
    sinfo[isymt].offs=alignment((sinfo[itext].offs+sinfo[itext].size),0x8);
    sinfo[ishst].offs=sinfo[isymt].offs+sinfo[isymt].size;
    sinfo[istrt].offs=sinfo[ishst].offs+sinfo[ishst].size;
    uint64_t shoff=sinfo[istrt].offs+sinfo[istrt].size;
    return (nbytes=alignment(shoff,0x40)+7*sizeof(elf64_shdr));
}
uint32_t generator::get_section_offset_note() const
{
    return sinfo[inote].offs;
}
uint32_t generator::get_section_offset_rodata() const
{
    return sinfo[irodt].offs;
}
uint32_t generator::get_section_offset_text() const
{
    return sinfo[itext].offs;
}
uint32_t generator::metadata_get_args_size( const metadata_t* meta ) const
{
    uint32_t o=msgpack_encode_str( nullptr, ".args" );
    for( uint32_t i=0; i<meta->nargs; ++i ){
        o+=msgpack_encode_str( nullptr, ".offset" );
        o+=msgpack_encode_uint( nullptr, meta->args[i].offs );
        o+=msgpack_encode_str( nullptr, ".size" );
        o+=msgpack_encode_uint( nullptr, meta->args[i].size );
        o+=msgpack_encode_str( nullptr, ".value_kind" );
        o+=msgpack_encode_str( nullptr, k_kind[meta->args[i].kind] );
        o+=msgpack_encode_str( nullptr, ".value_type" );
        o+=msgpack_encode_str( nullptr, k_type[meta->args[i].type] );
	}
    return o;
}
uint32_t generator::metadata_encode_args( uint8_t* note, const metadata_t* meta )
{
    uint32_t o=msgpack_encode_str( note, ".args" );
    for( uint32_t i=0; i<meta->nargs; ++i ){
        o+=msgpack_encode_str( &note[o], ".offset" );
        o+=msgpack_encode_uint( &note[o], meta->args[i].offs );
        o+=msgpack_encode_str( &note[o], ".size" );
        o+=msgpack_encode_uint( &note[o], meta->args[i].size );
        o+=msgpack_encode_str( &note[o], ".value_kind" );
        o+=msgpack_encode_str( &note[o], k_kind[meta->args[i].kind] );
        o+=msgpack_encode_str( &note[o], ".value_type" );
        o+=msgpack_encode_str( &note[o], k_type[meta->args[i].type] );
    }
    return o;
}
uint32_t generator::get_section_size_note( const metadata_t* meta, const uint32_t* cosizes, const vector<string>& knames ) const
{
    char buf[MAX_BUF_SIZE];
    uint32_t p=sizeof(elf64_nhdr)+sizeof(k_note_name)/sizeof(k_note_name[0]);
    p=alignment(p,4);
    p+=msgpack_encode_map( nullptr, 2 );
    p+=msgpack_encode_str( nullptr, "amdhsa.kernels" );
    p+=msgpack_encode_arr_prefix( nullptr, nkern );
    p+=msgpack_encode_map_prefix( nullptr, 11 );
    for( uint32_t i=0; i<nkern; ++i ){
        memset( buf, 0, MAX_BUF_SIZE );
        istrcpy( &buf[istrcpy( buf, knames[i].c_str() )], ".kd" );
        p+=msgpack_encode_str( nullptr, ".name" );
        p+=msgpack_encode_str( nullptr, knames[i].c_str() );
        p+=msgpack_encode_str( nullptr, ".symbol" );
        p+=msgpack_encode_str( nullptr, buf );
        p+=msgpack_encode_str( nullptr, ".group_segment_fiexed_size" );
        p+=msgpack_encode_uint( nullptr, meta[i].lds_size );
        p+=msgpack_encode_str( nullptr, ".kernarg_segment_align" );
        p+=msgpack_encode_uint( nullptr, meta[i].kernarg_align );
        p+=msgpack_encode_str( nullptr, ".kernarg_segment_size" );
        p+=msgpack_encode_uint( nullptr, meta[i].kernarg_size );
        p+=msgpack_encode_str( nullptr, ".private_segment_fiexed_size" );
        p+=msgpack_encode_uint( nullptr, meta[i].private_size );
        p+=msgpack_encode_str( nullptr, ".max_flat_workgroup_size" );
        p+=msgpack_encode_uint( nullptr, meta[i].group_size );
        p+=msgpack_encode_str( nullptr, ".wavefront_size" );
        p+=msgpack_encode_uint( nullptr, meta[i].wave_size );
        p+=msgpack_encode_str( nullptr, ".sgpr_count" );
        p+=msgpack_encode_uint( nullptr, meta[i].sgprcnt );
        p+=msgpack_encode_str( nullptr, ".vgpr_count" );
        p+=msgpack_encode_uint( nullptr, meta[i].vgprcnt );
        p+=metadata_get_args_size( &meta[i] );
    }
    p+=msgpack_encode_str( nullptr, "amdhsa.version" );
    p+=msgpack_encode_array( nullptr, k_amdhsa_version, 2 );
    return alignment(p,4);
}
uint32_t generator::get_section_size_rodata() const
{
    return (nkern<<6);
}
uint32_t generator::get_section_size_text( const uint32_t* cosizes ) const
{
    uint32_t size=0;
    for( uint32_t i=0; i<nkern; ++i ){
        size=alignment(size,256);
        size+=(cosizes[i]);
    }
    return size;
}
uint32_t generator::get_section_size_symtab() const
{
    return (((nkern<<1)|1)*sizeof(elf64_sym));
}
uint32_t generator::get_section_size_shstrtab() const
{
    return 47;
}
uint32_t generator::get_section_size_strtab( const vector<string>& knames ) const
{
    uint32_t size=(nkern<<1)|1;
    for( uint32_t i=0; i<nkern; ++i ){
        size+=(istrlen(knames[i].c_str())<<1)+3;
    }
    return size;
}
void generator::gen_elf_header()
{
    elf64_ehdr*&& eh=ELF_EHDR(hsaco);
    uint32_t shoff=sinfo[istrt].offs+sinfo[istrt].size;
    *reinterpret_cast<uint32_t*>(&eh->ident[0])=ELF_ID;
    eh->ident[EI_CLASS     ]=ELFCLASS64;
    eh->ident[EI_DATA      ]=ELFDATA2LSB;
    eh->ident[EI_VERSION   ]=EV_CURRENT;
    eh->ident[EI_OSABI     ]=ELFOSABI_AMDGPU_HSA;
    eh->ident[EI_ABIVERSION]=ELFABIVERSION_AMDGPU_HSA;
    eh->ident[EI_PAD+0     ]=0;
    eh->ident[EI_PAD+1     ]=0;
    eh->ident[EI_PAD+2     ]=0;
    eh->ident[EI_PAD+3     ]=0;
    eh->ident[EI_PAD+4     ]=0;
    eh->ident[EI_PAD+5     ]=0;
    eh->ident[EI_PAD+6     ]=0;
    eh->type     =ET_DYN;
    eh->machine  =EM_AMDGPU;
    eh->version  =EV_CURRENT;
    eh->entry    =sinfo[itext].offs;
    eh->phoff    =sizeof(elf64_ehdr);
    eh->shoff    =alignment(shoff,0x40);
    eh->flag     =eflag;
    eh->ehsize   =sizeof(elf64_ehdr);
    eh->phentsize=sizeof(elf64_phdr);
    eh->phcnt    =4;
    eh->shentsize=sizeof(elf64_shdr);
    eh->shcnt    =7;
    eh->shstrndx =5;
}
void generator::gen_program_headers()
{
    elf64_phdr*&& ph=ELF_PHDR(hsaco);
    ph[0].type  =PT_PHDR;
    ph[0].flags =PF_R;
    ph[0].offset=0x40;
    ph[0].vaddr =0x40;
    ph[0].paddr =0x40;
    ph[0].filenb=ELF_EHDR(hsaco)->phcnt*sizeof(elf64_phdr);
    ph[0].memnb =ph[0].filenb;
    ph[0].align =0x8;

    ph[1].type  =PT_LOAD;
    ph[1].flags =PF_R;
    ph[1].offset=0;
    ph[1].vaddr =0;
    ph[1].paddr =0;
    ph[1].filenb=sinfo[irodt].offs+sinfo[irodt].size;
    ph[1].memnb =ph[1].filenb;
    ph[1].align =0x1000;

    ph[2].type  =PT_LOAD;
    ph[2].flags =PF_R|PF_X;
    ph[2].offset=sinfo[itext].offs;
    ph[2].vaddr =ELF_EHDR(hsaco)->entry;
    ph[2].paddr =ELF_EHDR(hsaco)->entry;
    ph[2].filenb=sinfo[itext].size;
    ph[2].memnb =sinfo[itext].size;
    ph[2].align =0x1000;

    ph[3].type  =PT_NOTE;
    ph[3].flags =PF_R;
    ph[3].offset=sinfo[inote].offs;
    ph[3].vaddr =sinfo[inote].offs;
    ph[3].paddr =sinfo[inote].offs;
    ph[3].filenb=sinfo[inote].size;
    ph[3].memnb =sinfo[inote].size;
    ph[3].align =4;
}
void generator::gen_section_note( const metadata_t* meta, const uint32_t* cosizes, const vector<string>& knames )
{
    char buf[MAX_BUF_SIZE];
    uint8_t* note=&hsaco[ELF_SHDR(hsaco)[inote].offset];
    ELF_NHDR(note)->name=sizeof(k_note_name)/sizeof(k_note_name[0]);
    ELF_NHDR(note)->desc=sinfo[inote].size-sizeof(elf64_nhdr)-ELF_NHDR(note)->name;
    ELF_NHDR(note)->type=NT_AMDGPU_METADATA;
    uint32_t o=sizeof(elf64_nhdr)+ELF_NHDR(note)->name;
    uint32_t p=alignment(o,4);
    ELF_NHDR(note)->desc-=(p-o);
    ELF_NHDR(note)->desc=alignment(ELF_NHDR(note)->desc,4);
    iccpy(reinterpret_cast<char*>(&note[sizeof(elf64_nhdr)]),k_note_name,ELF_NHDR(note)->name);
    p+=msgpack_encode_map( &note[p], 2 );
    p+=msgpack_encode_str( &note[p], "amdhsa.kernels" );
    p+=msgpack_encode_arr_prefix( &note[p], nkern );
    p+=msgpack_encode_map_prefix( &note[p], 11 );
    for( uint32_t i=0; i<nkern; ++i ){
        memset( buf, 0, MAX_BUF_SIZE );
        istrcpy( &buf[istrcpy( buf, knames[i].c_str() )], ".kd" );
        p+=msgpack_encode_str( &note[p], ".name" );
        p+=msgpack_encode_str( &note[p], knames[i].c_str() );
        p+=msgpack_encode_str( &note[p], ".symbol" );
        p+=msgpack_encode_str( &note[p], buf );
        p+=msgpack_encode_str( &note[p], ".group_segment_fiexed_size" );
        p+=msgpack_encode_uint( &note[p], meta[i].lds_size );
        p+=msgpack_encode_str( &note[p], ".kernarg_segment_align" );
        p+=msgpack_encode_uint( &note[p], meta[i].kernarg_align );
        p+=msgpack_encode_str( &note[p], ".kernarg_segment_size" );
        p+=msgpack_encode_uint( &note[p], meta[i].kernarg_size );
        p+=msgpack_encode_str( &note[p], ".private_segment_fiexed_size" );
        p+=msgpack_encode_uint( &note[p], meta[i].private_size );
        p+=msgpack_encode_str( &note[p], ".max_flat_workgroup_size" );
        p+=msgpack_encode_uint( &note[p], meta[i].group_size );
        p+=msgpack_encode_str( &note[p], ".wavefront_size" );
        p+=msgpack_encode_uint( &note[p], meta[i].wave_size );
        p+=msgpack_encode_str( &note[p], ".sgpr_count" );
        p+=msgpack_encode_uint( &note[p], meta[i].sgprcnt );
        p+=msgpack_encode_str( &note[p], ".vgpr_count" );
        p+=msgpack_encode_uint( &note[p], meta[i].vgprcnt );
        p+=metadata_encode_args( &note[p], &meta[i] );
    }
    p+=msgpack_encode_str( &note[p], "amdhsa.version" );
    msgpack_encode_array( &note[p], k_amdhsa_version, 2 );
}
void generator::gen_section_text( const uint8_t* code, const uint32_t* cosizes )
{
    const metadata_t* meta=reinterpret_cast<const metadata_t*>(code);
    uint64_t odesc=ELF_SHDR(hsaco)[irodt].offset;
    uint64_t otext=ELF_SHDR(hsaco)[itext].offset;
    kernelOb kernel(&hsaco[odesc]);
    code+=nkern*sizeof(metadata_t);
    for( uint32_t i=0, ent=0; i<nkern; ++i ){
        uint32_t cosize=cosizes[i];
        memcpy( &hsaco[odesc], &code[ent], 64 );
        memcpy( &hsaco[otext], &code[ent+64], cosize );
        kernel.set_lds_size(meta[i].lds_size);
        kernel.set_private_size(meta[i].private_size);
        kernel.set_entry_offset(otext-odesc);
        kernel.set_sregcnt(meta[i].sgprcnt);
        kernel.set_vregcnt(meta[i].vgprcnt);
        ent+=(64+cosize); kernel.descr+=64; otext+=alignment(cosize,256); odesc+=64;
    }
}
void generator::gen_section_symtab( const uint32_t* cosizes )
{
    elf64_shdr*&& sh=ELF_SHDR(hsaco);
    elf64_shdr* shsym=&sh[isymt];
    elf64_sym* symtab=reinterpret_cast<elf64_sym*>(&hsaco[shsym->offset]);
    symtab[0].name =0;
    symtab[0].info =0;
    symtab[0].other=0;
    symtab[0].shndx=0;
    symtab[0].value=0;
    symtab[0].size =0;
    uint64_t otext=sinfo[itext].offs;
    uint64_t odesc=sinfo[irodt].offs;
    for( uint32_t i=0; i<nkern; ++i ){
        uint32_t s=(i<<1)|1;
        uint32_t cosize=cosizes[i];
        symtab[s].info=ELF_ST_INFO(STB_GLOBAL,STT_FUNC);
        symtab[s].other=ELF_ST_VIS(STV_PROTECTED);
        symtab[s].shndx=itext;
        symtab[s].value=otext;
        symtab[s].size=cosize;
        otext+=alignment(cosize,256);
        symtab[s+1].info=ELF_ST_INFO(STB_GLOBAL,STT_OBJECT);
        symtab[s+1].other=ELF_ST_VIS(STV_DEFAULT);
        symtab[s+1].shndx=irodt;
        symtab[s+1].value=odesc;
        symtab[s+1].size=64;
        odesc+=64;
    }
}
void generator::gen_section_shstrtab()
{
    elf64_shdr*&& sh=ELF_SHDR(hsaco);
    char* shstrtab=reinterpret_cast<char*>(&hsaco[sh[ishst].offset]);
    shstrtab[0]='\0';
    sh[0].name=0;
    sh[1].name=1;
    istrcpy( &shstrtab[1], ".note" );
    shstrtab[6]='\0';
    sh[2].name=7;
    istrcpy( &shstrtab[7], ".rodata" );
    shstrtab[14]='\0';
    sh[3].name=15;
    istrcpy( &shstrtab[15], ".text" );
    shstrtab[20]='\0';
    sh[4].name=21;
    istrcpy( &shstrtab[21], ".symtab" );
    shstrtab[28]='\0';
    sh[5].name=29;
    istrcpy( &shstrtab[29], ".shstrtab" );
    shstrtab[38]='\0';
    sh[6].name=39;
    istrcpy( &shstrtab[39], ".strtab" );
    shstrtab[46]='\0';
}
void generator::gen_section_strtab( const vector<string>& knames )
{
    elf64_shdr*&& sh=ELF_SHDR(hsaco);
    elf64_shdr* shsym=&sh[isymt];
    elf64_shdr* shstr=&sh[istrt];
    char* strtab=reinterpret_cast<char*>(&hsaco[shstr->offset]);
    elf64_sym* symtab=reinterpret_cast<elf64_sym*>(&hsaco[shsym->offset]);
    strtab[0]='\0';
    uint32_t p=0;
    for( uint32_t i=0; i<nkern; ++i ){
        uint32_t s=(i<<1)|1;
        symtab[s].name=++p;
        p+=istrcpy( &strtab[p], knames[i].c_str() );
        strtab[p]='\0';
        symtab[s+1].name=++p;
        p+=istrcpy( &strtab[p], knames[i].c_str() );
        p+=istrcpy( &strtab[p], ".kd" );
        strtab[p]='\0';
    }
}
void generator::gen( const uint8_t* code, const uint32_t* cosizes, const vector<string>& knames )
{
    gen_elf_header();
    gen_program_headers();
    elf64_shdr*&& sh=ELF_SHDR(hsaco);

    sh[inull].name   =0;
    sh[inull].type   =0;
    sh[inull].flags  =0;
    sh[inull].addr   =0;
    sh[inull].offset =0;
    sh[inull].size   =0;
    sh[inull].info   =0;
    sh[inull].link   =0;
    sh[inull].align  =0;
    sh[inull].entsize=0;

    sh[inote].type   =SHT_NOTE;
    sh[inote].flags  =SHF_ALLOC;
    sh[inote].addr   =sinfo[inote].offs;
    sh[inote].offset =sinfo[inote].offs;
    sh[inote].size   =sinfo[inote].size;
    sh[inote].info   =0;
    sh[inote].link   =0;
    sh[inote].align  =4;
    sh[inote].entsize=0;

    sh[irodt].type   =SHT_PROGBITS;
    sh[irodt].flags  =SHF_ALLOC;
    sh[irodt].addr   =sinfo[irodt].offs;
    sh[irodt].offset =sinfo[irodt].offs;
    sh[irodt].size   =sinfo[irodt].size;
    sh[irodt].info   =0;
    sh[irodt].link   =0;
    sh[irodt].align  =64;
    sh[irodt].entsize=0;

    sh[itext].type   =SHT_PROGBITS;
    sh[itext].flags  =SHF_ALLOC|SHF_EXECINSTR;
    sh[itext].addr   =sinfo[itext].offs;
    sh[itext].offset =sinfo[itext].offs;
    sh[itext].size   =sinfo[itext].size;
    sh[itext].info   =0;
    sh[itext].link   =0;
    sh[itext].align  =256;
    sh[itext].entsize=0;

    sh[isymt].type   =SHT_SYMTAB;
    sh[isymt].flags  =0;
    sh[isymt].addr   =0;
    sh[isymt].offset =sinfo[isymt].offs;
    sh[isymt].size   =sinfo[isymt].size;
    sh[isymt].info   =8;
    sh[isymt].link   =istrt;
    sh[isymt].align  =8;
    sh[isymt].entsize=sizeof(elf64_sym);

    sh[ishst].type   =SHT_STRTAB;
    sh[ishst].flags  =0;
    sh[ishst].addr   =0;
    sh[ishst].offset =sinfo[ishst].offs;
    sh[ishst].size   =sinfo[ishst].size;
    sh[ishst].info   =0;
    sh[ishst].link   =0;
    sh[ishst].align  =1;
    sh[ishst].entsize=0;

    sh[istrt].type   =SHT_STRTAB;
    sh[istrt].flags  =0;
    sh[istrt].addr   =0;
    sh[istrt].offset =sinfo[istrt].offs;
    sh[istrt].size   =sinfo[istrt].size;
    sh[istrt].info   =0;
    sh[istrt].link   =0;
    sh[istrt].align  =1;
    sh[istrt].entsize=0;

    gen_section_note( reinterpret_cast<const metadata_t*>(code), cosizes, knames );
    gen_section_text( code, cosizes );
    gen_section_symtab( cosizes );
    gen_section_shstrtab();
    gen_section_strtab( knames );
}

extern "C"
{
generator* create_hsaco_generator( uint32_t arch, const uint8_t* code, const uint32_t* cosizes, const vector<string>& knames )
{
    generator* hsacogen=new generator(arch);
    if(hsacogen==nullptr) return nullptr;
    uint32_t size=hsacogen->required_size( reinterpret_cast<const metadata_t*>(code), cosizes, knames );
    if((hsacogen->hsaco=new uint8_t[size])==nullptr){
        delete hsacogen;
        return nullptr;
    }
    memset( hsacogen->hsaco, 0, size );
    hsacogen->gen( code, cosizes, knames );
    return hsacogen;
}
void destroy_hsaco_generator( generator* p )
{
    if(p!=nullptr){ free(p->hsaco); delete p; }
}
}