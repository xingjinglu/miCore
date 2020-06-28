#ifndef __cast_h__
#define __cast_h__

#include<cstdint>

inline uint32_t float_as_uint( float n ){ return *reinterpret_cast<uint32_t*>(&n); }
inline uint32_t int_as_uint( int32_t n ){ return *reinterpret_cast<uint32_t*>(&n); }
inline uint16_t int16_as_uint16( int16_t n ){ return *reinterpret_cast<uint16_t*>(&n); }

#endif