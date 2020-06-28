#ifndef __sop1_h__
#define __sop1_h__

#define encoding_sop1 0xbe800000u

#define sop1_mov_b32       ( 0u<<8)
#define sop1_mov_b64       ( 1u<<8)
#define sop1_cmov_b32      ( 2u<<8)
#define sop1_cmov_b64      ( 3u<<8)
#define sop1_not_b32       ( 4u<<8)
#define sop1_not_b64       ( 5u<<8)
#define sop1_bfz_b32       (14u<<8)
#define sop1_bfz_b64       (15u<<8)
#define sop1_bfs_b32       (16u<<8)
#define sop1_bfs_b64       (17u<<8)
#define sop1_andexec_b64   (32u<<8)
#define sop1_andnexec_b64  (35u<<8)
#define sop1_nandexec_b64  (37u<<8)
#define sop1_andn1exec_b64 (51u<<8)

#endif