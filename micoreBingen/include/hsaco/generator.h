#ifndef __generator_h__
#define __generator_h__

#include<vector>
#include<string>
#include"hsaco.h"

using namespace std;

class generator
{
public:
    generator( uint32_t flag ):eflag(flag){}

public:
    uint32_t required_size( const metadata_t*, const uint32_t*, const vector<string>& );
    void gen( const uint8_t*, const uint32_t*, const vector<string>& );
    inline const uint32_t size() const { return nbytes; }

private:
    uint32_t metadata_get_args_size( const metadata_t* ) const;
    uint32_t metadata_encode_args( uint8_t*, const metadata_t* );
    uint32_t get_section_offset_note() const;
    uint32_t get_section_offset_rodata() const;
    uint32_t get_section_offset_text() const;
    uint32_t get_section_size_note( const metadata_t*, const uint32_t*, const vector<string>& ) const;
    uint32_t get_section_size_rodata() const;
    uint32_t get_section_size_text( const uint32_t* ) const;
    uint32_t get_section_size_symtab() const;
    uint32_t get_section_size_shstrtab() const;
    uint32_t get_section_size_strtab( const vector<string>& ) const;
    void     gen_elf_header();
    void     gen_program_headers();
    void     gen_section_note( const metadata_t*, const uint32_t*, const vector<string>& );
    void     gen_section_text( const uint8_t*, const uint32_t* );
    void     gen_section_symtab( const uint32_t* );
    void     gen_section_shstrtab();
    void     gen_section_strtab( const vector<string>& );

public:
    uint8_t* hsaco;
private:
    struct{ uint32_t offs, size; } sinfo[7];
    uint32_t eflag;
    uint32_t nbytes;
    uint32_t nkern;

    static const int inull=0;
    static const int inote=1;
    static const int irodt=2;
    static const int itext=3;
    static const int isymt=4;
    static const int ishst=5;
    static const int istrt=6;
    static const char k_note_name[];
    static const uint8_t k_amdhsa_version[];
    static const char* k_kind[];
    static const char* k_type[];
};

extern "C"
{
generator* create_hsaco_generator( uint32_t, const uint8_t*, const uint32_t*, const vector<string>& );
void destroy_hsaco_generator( generator* );
}

#endif