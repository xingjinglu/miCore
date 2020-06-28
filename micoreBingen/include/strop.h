#ifndef __strop_h__
#define __strop_h__


inline int istrcat( char* __restrict p_dst, const char* __restrict p_src )
{
    char* p_start=p_dst;
    while(*p_dst++=*p_src++);
    return ((int)(p_dst-p_start-1));
}
inline int istrcmp( const char* __restrict src, const char* __restrict dst )
{
    int c=0;
    while(!(c=*(unsigned char*)src-*(unsigned char*)dst)&&*dst&&*src){ ++src, ++dst; }
    return c;
}
inline int istrlen( const char* src )
{
    char* p=(char*)src;
    while(*p++);
    return ((int)(p-src)-1);
}
inline int istrcpy( char* __restrict dst, const char* __restrict src )
{
    char* p=(char*)src;
    while(*p){ *dst++=*p++; }
    return ((int)(p-src));
}
inline void iccpy( char* __restrict dst, const char* __restrict src, int n )
{
    for( int i=0; i<n; ++i ){ *dst++=*src++; }
}

#endif