#include<stdio.h>
#include"include/gfxcoder.h"
#include"include/hsaco/generator.h"

int main( int argc, char* argv[] )
{
    uint32_t cosizes[1024];
    uint8_t* code=new uint8_t[0x7fffffff];
    gfxcoder* co=new gfxcoder;
    co->gen( code, cosizes );
    generator* hsacogen=create_hsaco_generator( __gfxip__, code, cosizes, co->kernel_names() );
    char* filename=
#if __gfxip__==gfx900
    "hsaco_gfx900.h"
#elif __gfxip__==gfx906
    "hsaco_gfx906.h"
#elif __gfxip__==gfx908
    "hsaco_gfx908.h"
#else
    #error "Invalid arch!"
#endif
    ;
    FILE* fp=fopen( filename, "w" );
    if(fp!=NULL){
        for( uint32_t i=0; i<hsacogen->size(); ++i ){
            uint8_t b=hsacogen->hsaco[i];
            if((i>0)&((i&31)==0)){ fprintf( fp, "\n" ); }
            if(b<16){
                fprintf( fp, "0x0%x", b );
            } else {
                fprintf( fp, "0x%x", b );
            }
            if(i<(hsacogen->size()-1)){ fprintf( fp, "," ); }
        }
        fclose(fp);
	} else {
        printf( "error : file open failed!\n" );
    }

    destroy_hsaco_generator(hsacogen);
    delete co;
    delete[] code;
    return 0;
}