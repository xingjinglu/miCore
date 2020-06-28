#ifndef __sopk_h__
#define __sopk_h__

#define encoding_sopk 0xb0000000u

#define sopk_movk_b32   (0x00<<23)
#define sopk_cmovk_b32  (0x01<<23)
#define sopk_addk_i32   (0x0e<<23)
#define sopk_mulk_i32   (0x0f<<23)
#define sopk_getreg_b32 (0x11<<23)

#endif