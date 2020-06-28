#ifndef __fft_h__
#define __fft_h__

#include<cstdint>

typedef struct{
    uint32_t x;
    uint32_t y;
} uint2;

#define CPTR(c) ((uint32_t*)&c[0].x)

#define VZERO8(r){        \
    v_mov_b32((r)+0,zero);\
    v_mov_b32((r)+1,zero);\
    v_mov_b32((r)+2,zero);\
    v_mov_b32((r)+3,zero);\
    v_mov_b32((r)+4,zero);\
    v_mov_b32((r)+5,zero);\
    v_mov_b32((r)+6,zero);\
    v_mov_b32((r)+7,zero);\
}

#define VZERO16(r){\
    VZERO8((r)+0); \
    VZERO8((r)+8); \
}

#define VZERO32(r){ \
    VZERO16((r)+ 0);\
    VZERO16((r)+16);\
}

#define LDS_B32x9(d,addr,n,e){       \
    lsld_b32((d)[0]##e,addr,0*4*(n));\
    lsld_b32((d)[1]##e,addr,1*4*(n));\
    lsld_b32((d)[2]##e,addr,2*4*(n));\
    lsld_b32((d)[3]##e,addr,3*4*(n));\
    lsld_b32((d)[4]##e,addr,4*4*(n));\
    lsld_b32((d)[5]##e,addr,5*4*(n));\
    lsld_b32((d)[6]##e,addr,6*4*(n));\
    lsld_b32((d)[7]##e,addr,7*4*(n));\
    lsld_b32((d)[8]##e,addr,8*4*(n));\
}

#define LDS_B32x17(d,addr,n,e){            \
    lsld_b32((d)[0x00]##e,addr,0x00*4*(n));\
    lsld_b32((d)[0x01]##e,addr,0x01*4*(n));\
    lsld_b32((d)[0x02]##e,addr,0x02*4*(n));\
    lsld_b32((d)[0x03]##e,addr,0x03*4*(n));\
    lsld_b32((d)[0x04]##e,addr,0x04*4*(n));\
    lsld_b32((d)[0x05]##e,addr,0x05*4*(n));\
    lsld_b32((d)[0x06]##e,addr,0x06*4*(n));\
    lsld_b32((d)[0x07]##e,addr,0x07*4*(n));\
    lsld_b32((d)[0x08]##e,addr,0x08*4*(n));\
    lsld_b32((d)[0x09]##e,addr,0x09*4*(n));\
    lsld_b32((d)[0x0a]##e,addr,0x0a*4*(n));\
    lsld_b32((d)[0x0b]##e,addr,0x0b*4*(n));\
    lsld_b32((d)[0x0c]##e,addr,0x0c*4*(n));\
    lsld_b32((d)[0x0d]##e,addr,0x0d*4*(n));\
    lsld_b32((d)[0x0e]##e,addr,0x0e*4*(n));\
    lsld_b32((d)[0x0f]##e,addr,0x0f*4*(n));\
    lsld_b32((d)[0x10]##e,addr,0x10*4*(n));\
}

#define STS_B32x9(addr,n,s,e){       \
    lsst_b32(addr,0*4*(n),(s)[0]##e);\
    lsst_b32(addr,1*4*(n),(s)[1]##e);\
    lsst_b32(addr,2*4*(n),(s)[2]##e);\
    lsst_b32(addr,3*4*(n),(s)[3]##e);\
    lsst_b32(addr,4*4*(n),(s)[4]##e);\
    lsst_b32(addr,5*4*(n),(s)[5]##e);\
    lsst_b32(addr,6*4*(n),(s)[6]##e);\
    lsst_b32(addr,7*4*(n),(s)[7]##e);\
    lsst_b32(addr,8*4*(n),(s)[8]##e);\
}

#define STS_B32x17(addr,n,s,e){            \
    lsst_b32(addr,0x00*4*(n),(s)[0x00]##e);\
    lsst_b32(addr,0x01*4*(n),(s)[0x01]##e);\
    lsst_b32(addr,0x02*4*(n),(s)[0x02]##e);\
    lsst_b32(addr,0x03*4*(n),(s)[0x03]##e);\
    lsst_b32(addr,0x04*4*(n),(s)[0x04]##e);\
    lsst_b32(addr,0x05*4*(n),(s)[0x05]##e);\
    lsst_b32(addr,0x06*4*(n),(s)[0x06]##e);\
    lsst_b32(addr,0x07*4*(n),(s)[0x07]##e);\
    lsst_b32(addr,0x08*4*(n),(s)[0x08]##e);\
    lsst_b32(addr,0x09*4*(n),(s)[0x09]##e);\
    lsst_b32(addr,0x0a*4*(n),(s)[0x0a]##e);\
    lsst_b32(addr,0x0b*4*(n),(s)[0x0b]##e);\
    lsst_b32(addr,0x0c*4*(n),(s)[0x0c]##e);\
    lsst_b32(addr,0x0d*4*(n),(s)[0x0d]##e);\
    lsst_b32(addr,0x0e*4*(n),(s)[0x0e]##e);\
    lsst_b32(addr,0x0f*4*(n),(s)[0x0f]##e);\
    lsst_b32(addr,0x10*4*(n),(s)[0x10]##e);\
}

#define CALC_SPLIT_IDX(__imap,__icell_y,__icell,__grid_x,__xmag,__ymag,stemp){\
    s_mul_i32(stemp,__grid_x,__grid_x+1);         \
    V_MDM_U32(__imap,__icell,stemp,__xmag);       \
    V_MDM_U32(__icell_y,__imap+1,__grid_x,__ymag);\
}

#define S_CALC_SPLIT_IDX(__imap,__icell_y,__icell,__grid_x,__xmag,__ymag,stemp){\
    s_mul_i32(stemp,__grid_x,__grid_x+1);         \
    S_MDM_U32(__imap,__icell,stemp,__xmag);       \
    S_MDM_U32(__icell_y,__imap+1,__grid_x,__ymag);\
}

static const int ga_brev3[]={0,4,2,6,1,5,3,7};
static const int ga_brev4[]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

#endif
