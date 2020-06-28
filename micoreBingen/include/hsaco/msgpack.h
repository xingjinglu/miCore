#ifndef __msgpack_h__
#define __msgpack_h__

#include<stdint.h>
#include"../strop.h"

#define REV_BYTES_U16(n) static_cast<uint16_t>((((n)&0xff)<<8)|((n)>>8))
#define REV_BYTES_U32(n) ((((n)&0xff)<<24)|(((n)&0xff00)<<8)|(((n)&0xff0000)>>8)|((n)>>24))

inline uint32_t msgpack_encode_str( uint8_t* dst, const char* str )
{
    uint32_t size=istrlen(str);
    if(dst!=nullptr){
        if(size<32){
            *dst=0xa0|static_cast<uint8_t>(size); ++dst;
        } else {
            *dst=0xd9; *(dst+1)=static_cast<uint8_t>(size); dst+=2;
        }
        istrcpy( reinterpret_cast<char*>(dst), str );
    }
    return (size+(size<32?1:2));
}
inline uint32_t msgpack_encode_uint( uint8_t* dst, uint32_t val )
{
    uint32_t size=1;
    if(dst!=nullptr){
        if(val<128){
            *dst=static_cast<uint8_t>(val);
        } else
        if((val>=128)&&(val<256)){
            *dst=0xcc; *(dst+1)=static_cast<uint8_t>(val);
        } else
        if((val>=256)&&(val<65536)){
            dst[0]=0xcd; *reinterpret_cast<uint16_t*>(&dst[1])=REV_BYTES_U16(val);
        } else {
            dst[0]=0xce; *reinterpret_cast<uint32_t*>(&dst[1])=REV_BYTES_U32(val);
        }
    }
    size+=(val>  127?1:0);
    size+=(val>  255?1:0);
    size+=(val>65535?2:0);
    return size;
}
inline uint32_t msgpack_encode_array( uint8_t* dst, const uint8_t* val, uint32_t n )
{
    if(dst!=nullptr){
        if(n<16){
            *dst=0x90|n; ++dst;
        } else {
            *dst=0xdc; *(reinterpret_cast<uint16_t*>(&dst[1]))=static_cast<uint16_t>(n); dst+=3;
        }
        for( uint32_t i=0; i<n; ++i ){ dst[i]=val[i]; }
    }
    return (n+(n<16?1:3));
}
inline uint32_t msgpack_encode_map( uint8_t* dst, uint32_t n )
{
    if(dst!=nullptr){
        if(n<16){
            *dst=0x80|static_cast<uint8_t>(n);
        } else
        if((n>=16)&&(n<65536)){
            *dst=0xde; *reinterpret_cast<uint16_t*>(&dst[1])=static_cast<uint16_t>(n);
        } else {
            *dst=0xdf; *reinterpret_cast<uint32_t*>(&dst[1])=n;
        }
    }
    return (1+(n>15?2:0)+(n>65535?2:0));
}
inline uint32_t msgpack_encode_arr_prefix( uint8_t* dst, uint32_t n )
{
    if(dst!=nullptr){
        if(n<16){
            *dst=0x90|n;
        } else {
            *dst=0xdc; *(reinterpret_cast<uint16_t*>(&dst[1]))=static_cast<uint16_t>(n);
        }
    }
    return (n<16?1:3);
}
inline uint32_t msgpack_encode_map_prefix( uint8_t* dst, uint32_t n )
{
    if(dst!=nullptr){
        if(n<16){
            *dst=0x80|static_cast<uint8_t>(n);
        } else
        if((n>=16)&&(n<65536)){
            *dst=0xde; *reinterpret_cast<uint16_t*>(&dst[1])=static_cast<uint16_t>(n);
        } else {
            *dst=0xdf; *reinterpret_cast<uint32_t*>(&dst[1])=n;
        }
    }
    return (n<16?1:((n>=16)&&(n<65536)?3:5));
}

#endif
