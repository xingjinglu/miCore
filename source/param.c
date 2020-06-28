#include"../include/param.h"

static uint32_t choose_optimal_routine_ufconv( uint32_t m, uint32_t n, uint32_t k, int dir )
{
    uint32_t s=(n+31)>>5;
    uint32_t t=(n+15)>>4;
    uint32_t mode=((m&1)^1)+((m&3)==0?1:0);
    uint32_t id=1+((s&3)==0?((k&15)==0?2:1):((s&1)^1));
    if((t&1)!=0&&n<=112) id=0;
    if((dir!=0)&&(id!=0)){ id=(n&3)!=0?((n&1)!=0?1:2):id; }
    return ((mode<<16)|id);
}
static uint32_t choose_optimal_routine_conv( uint32_t n, uint32_t k )
{
    uint32_t s=(n+31u)>>5;
    uint32_t id=(s&3u)==0u?((k&15u)==0u?2u:1u):((s&1u)^1u);
    return id;
}
static uint32_t choose_optimal_cell_id( uint32_t anx, uint32_t any, uint32_t bnx, uint32_t bny )
{
    uint32_t id, n=0x7fffffff;
    for( int i=1; i>=0; --i ){
        uint32_t cell_size=1<<(4+i);
        uint32_t tile_x=cell_size-bnx+1;
        uint32_t tile_y=cell_size-bny+1;
        uint32_t grid_x=(anx+tile_x-bnx)/tile_x;
        uint32_t grid_y=(any+tile_y-bny)/tile_y;
        uint32_t size=grid_x*grid_y*cell_size*((cell_size>>1)+1);
        if(size<n){ id=i; n=size; }
    }
    return id;
}
__local_func int build_param_ufconv( param_ufconv_t* p, const tensorshape_t* sa, const tensorshape_filter_t* sb, uint32_t ng, int dir )
{
    static const uint32_t selx=0x924924u;
    static const uint32_t sely=0x500000u;
    uint32_t alignment, id, sx, sy;
    p->m=sa->nx*sa->ny;
    p->n=dir==0?sb->qnc:sb->pnc;
    p->k=dir==0?sb->pnc:sb->qnc;
    p->id=choose_optimal_routine_ufconv( p->m, p->n, p->k, dir );
    alignment=(p->id&0xffff)>0&&(p->id&0xffff)<3?255:127;
    p->ng=ng;
    p->dimx=p->m*sa->bs;
    p->ntidx=PSIZE(p->dimx,alignment);
    id=(p->id&0xffff)*3+(p->id>>16);
    sx=(selx>>(id<<1))&0x3;
    sy=(sely>>(id<<1))&0x3;
    p->amag=idiv_magic(p->ntidx>>sx,p->m>>sx);
    if(sx!=sy){
        p->cmag=idiv_magic(p->ntidx>>sy,p->m>>sy);
    }
    return istatus_success;
}
__local_func int build_param_fconv( param_conv_t* p, const tensorshape_t* sa, const tensorshape_filter_t* sb, const tensorshape_t* sc, uint32_t pad, uint32_t str, uint32_t dla, uint32_t ng )
{
    uint32_t temp, pad_l, pad_r, pad_t, pad_b, su, sv, du, dv, pk;
    pad_l=0;
    pad_r=0;
    pad_t=0;
    pad_b=0;
    if(pad!=0){
        pad_l=(pad>> 0)&0xff;
        pad_r=(pad>> 8)&0xff;
        pad_t=(pad>>16)&0xff;
        pad_b=(pad>>24)&0xff;
    }
    if((pad_l>=sb->nx)||(pad_r>=sb->nx)||(pad_t>=sb->ny)||(pad_b>=sb->ny))
        return istatus_invalid_value;
    p->pnx=sa->nx+pad_l+pad_r;
    p->pny=sa->ny+pad_t+pad_b;
    su=((str>>0)&0x3f)+1;
    sv=((str>>6)&0x3f)+1;
    du=((dla>>0)&0x3f)+1;
    dv=((dla>>6)&0x3f)+1;
    if((((p->pnx-du*(sb->nx-1)-1)/su+1)!=sc->nx)||(((p->pny-dv*(sb->ny-1)-1)/sv+1)!=sc->ny))
        return istatus_invalid_value;
    p->inc=sb->pnc;
    p->k=sb->nx*sb->ny*sb->pnc;
    p->n=sb->qnc;
    p->ng=ng;
    p->pad=(pad_b<<24)|(pad_t<<16)|(pad_r<<8)|pad_l;
    p->sd=(dv<<18)|(du<<12)|(sv<<6)|su;
    p->anx=sa->nx;
    p->any=sa->ny;
    p->cnx=sc->nx;
    p->cny=sc->ny;
    p->bs =sc->bs;
    p->bnx=sb->nx;
    p->bny=sb->ny;
    p->ldc=p->cnx*p->cny;
    p->m=p->ldc*p->bs;
    p->id=choose_optimal_routine_conv(p->n,p->k);
    if((p->k&7)!=0){ p->id=0; } else { p->id+=1; }
    temp=p->id<3?255:127;
    p->ntidx=PSIZE(p->m,temp);
    p->lda=p->pnx*p->pny;
    if(p->pad!=0){
        p->lda*=p->bs;
        if(p->lda>1024){
            temp=(p->lda+63)>>6;
            p->lda=(temp+(1^(temp&1)))<<6;
        }
    }
    pk=PSIZE(p->k,7);
    p->ags=p->lda*p->inc;
    p->spad=(ng<<2)*p->ags;
    p->sidx=(p->ntidx<<3)+(pk<<2)+128;
    p->spad=p->pad!=0?p->spad:0;
    p->sperm=0;
    return 0;
}
__local_func int build_param_bconv( param_conv_t* p, const tensorshape_t* sa, const tensorshape_filter_t* sb, const tensorshape_t* sc, uint32_t pad, uint32_t str, uint32_t dla, uint32_t ng )
{
    uint32_t temp, pad_l, pad_r, pad_t, pad_b, su, sv, du, dv, pk;
    pad_l=(pad>> 0)&0xff;
    pad_r=(pad>> 8)&0xff;
    pad_t=(pad>>16)&0xff;
    pad_b=(pad>>24)&0xff;
    if((pad_l>=sb->nx)||(pad_r>=sb->nx)||(pad_t>=sb->ny)||(pad_b>=sb->ny))
        return istatus_invalid_value;
    pad_l=sb->nx-pad_l-1;
    pad_r=sb->nx-pad_r-1;
    pad_t=sb->ny-pad_t-1;
    pad_b=sb->ny-pad_b-1;
    p->pnx=sa->nx+pad_l+pad_r;
    p->pny=sa->ny+pad_t+pad_b;
    if(((p->pnx-sb->nx+1)!=sc->nx)||((p->pny-sb->ny+1)!=sc->ny))
        return istatus_invalid_value;
    su=((str>>0)&0x3f)+1;
    sv=((str>>6)&0x3f)+1;
    du=((dla>>0)&0x3f)+1;
    dv=((dla>>6)&0x3f)+1;
    p->inc=sb->qnc;
    p->k=sb->nx*sb->ny*p->inc;
    p->n=sb->pnc;
    p->ng=ng;
    p->pad=(pad_b<<24)|(pad_t<<16)|(pad_r<<8)|pad_l;
    p->sd=(dv<<18)|(du<<12)|(sv<<6)|su;
    p->anx=sa->nx;
    p->any=sa->ny;
    p->cnx=sc->nx;
    p->cny=sc->ny;
    p->bs =sc->bs;
    p->bnx=sb->nx;
    p->bny=sb->ny;
    p->ldc=p->cnx*p->cny;
    p->m=p->ldc*p->bs;
    p->id=choose_optimal_routine_conv(p->n,p->k);
    temp=p->id<2?255:127;
    p->ntidx=PSIZE(p->m,temp);
    p->lda=p->pnx*p->pny;
    if(p->pad!=0){
        p->lda*=p->bs;
        if(p->lda>1024){
            temp=(p->lda+63)>>6;
            p->lda=(temp+(1^(temp&1)))<<6;
        }
    }
    pk=PSIZE(p->k,7);
    p->ags=p->lda*p->inc;
    p->spad=(ng<<2)*p->ags;
    p->sidx=(p->ntidx<<3)+(pk<<2)+128;
    p->spad=p->pad!=0?p->spad:0;
    p->sperm=(ng<<2)*pk*PSIZE(p->n,3);
    return 0;
}
__local_func int build_param_cellconv( param_cellconv_t* p, const tensorshape_t* sp, const tensorshape_t* sq, uint32_t pad, uint32_t ng, uint32_t dir )
{
    uint32_t pad_l, pad_r, pad_t, pad_b, nx, ny, pm, grid;
    const tensorshape_t* sa=dir==0?sp:sq;
    const tensorshape_t* sc=dir==0?sq:sp;
    if((sa->nc&7)!=0) return istatus_invalid_value;
    pad_l=(pad>> 0)&0xff;
    pad_r=(pad>> 8)&0xff;
    pad_t=(pad>>16)&0xff;
    pad_b=(pad>>24)&0xff;
    if((pad_l>2)||(pad_r>2)||(pad_t>2)||(pad_b>2)) return istatus_invalid_value;
    if(dir!=0){
        pad_l=2-pad_l;
        pad_r=2-pad_r;
        pad_t=2-pad_t;
        pad_b=2-pad_b;
    }
    nx=sa->nx+pad_l+pad_r;
    ny=sa->ny+pad_t+pad_b;
    p->grid_x=(nx+3)/6;
    p->grid_y=(ny+3)/6;
    p->pad=(pad_t<<2)|pad_l;
    p->anx=sa->nx;
    p->any=sa->ny;
    p->cnx=sc->nx;
    p->cny=sc->ny;
    p->bs =sc->bs;
    p->ng =ng;
    p->m=p->bs*p->grid_x*p->grid_y;
    p->n=sc->nc;
    p->k=sa->nc;
    pm=PSIZE(p->m,63);
    grid=p->grid_x*p->grid_y;
    p->xmag=idiv_magic(pm,grid);
    p->ymag=idiv_magic(grid,p->grid_x);
    p->lda=pm;
    p->ldb=PSIZE(p->n,63);
    p->abks=p->lda*p->k;
    p->bbks=p->ldb*p->k;
    p->cbks=p->lda*p->n;
    p->abks=PSIZE(p->abks,63)>>6;
    p->bbks=PSIZE(p->bbks,63)>>6;
    p->cbks=PSIZE(p->cbks,63);
    p->abks=(p->abks+(1^(p->abks&1)))<<6;
    p->bbks=(p->bbks+(1^(p->bbks&1)))<<6;
    return istatus_success;
}
__local_func int build_param_fftconv( param_fftconv_t* p, const tensorshape_t* sp, const tensorshape_filter_t* sb, const tensorshape_t* sq, uint32_t pad, uint32_t dir )
{
    uint32_t pnx, pny, cell, ek;
    const tensorshape_t* sa=dir==0?sp:sq;
    const tensorshape_t* sc=dir==0?sq:sp;
    p->pad_l=0;
    p->pad_r=0;
    p->pad_t=0;
    p->pad_b=0;
    if(pad!=0){
        p->pad_l=(pad>> 0)&0xff;
        p->pad_r=(pad>> 8)&0xff;
        p->pad_t=(pad>>16)&0xff;
        p->pad_b=(pad>>24)&0xff;
    }
    if((p->pad_l>=sb->nx)||(p->pad_r>=sb->nx)||(p->pad_t>=sb->ny)||(p->pad_b>=sb->ny))
        return istatus_invalid_value;
    if(dir!=0){
        p->pad_l=sb->nx-p->pad_l-1;
        p->pad_r=sb->nx-p->pad_r-1;
        p->pad_t=sb->ny-p->pad_t-1;
        p->pad_b=sb->ny-p->pad_b-1;
    }
    pnx=sa->nx+p->pad_l+p->pad_r;
    pny=sa->ny+p->pad_t+p->pad_b;
    p->id=choose_optimal_cell_id( pnx, pny, sb->nx, sb->ny );
    cell=1<<(4+p->id);
    p->nbanks=cell*((cell>>1)+1);
    p->tile_x=cell-sb->nx+1;
    p->tile_y=cell-sb->ny+1;
    p->grid_x=(pnx+p->tile_x-sb->nx)/p->tile_x;
    p->grid_y=(pny+p->tile_y-sb->ny)/p->tile_y;
    if(((p->grid_x|p->grid_y)>0xffff)||((sb->nx|sb->ny)>=cell))
        return istatus_invalid_value;
    p->m=sa->bs*p->grid_x*p->grid_y;
    p->n=dir==0?sb->qnc:sb->pnc;
    p->k=dir==0?sb->pnc:sb->qnc;
    ek=PSIZE(p->k,7);
    p->lda=PSIZE(p->m,31)>>5;
    p->ldb=PSIZE(p->n,31)>>5;
    p->lda=(p->lda+(1^(p->lda&1)))<<5;
    p->ldb=(p->ldb+(1^(p->ldb&1)))<<5;
    p->abks=p->lda*ek+16;
    p->bbks=p->ldb*ek+16;
    p->cbks=p->lda*p->n+16;
    p->aldy=sa->nx*sa->ny;
    p->cldy=sc->nx*sc->ny;
    p->bldy=sb->nx*sb->ny;
    p->aldx=sa->nc*p->aldy;
    p->cldx=sc->nc*p->cldy;
    p->bldx=(dir==0?sb->pnc:1)*p->bldy;
    p->bldy=(dir==0?1:sb->pnc)*p->bldy;
    p->anx=sa->nx;
    p->any=sa->ny;
    p->cnx=sc->nx;
    p->cny=sc->ny;
    p->bnx=sb->nx;
    p->bny=sb->ny;
    if((p->grid_x|p->grid_y)!=1){
        uint32_t pm=PSIZE(p->m,15);
        uint32_t reso=p->grid_x*p->grid_y;
        p->xmag=idiv_magic(pm,reso);
        p->ymag=idiv_magic(reso,p->grid_x);
    }
    return istatus_success;
}
__local_func int build_param_fftconv_grad( param_fftconv_t* p, const tensorshape_t* sa, const tensorshape_t* sb, const tensorshape_filter_t* sc, uint32_t pad )
{
    uint32_t pnx, pny, cell, ek;
    p->pad_l=0;
    p->pad_r=0;
    p->pad_t=0;
    p->pad_b=0;
    pnx=sa->nx;
    pny=sa->ny;
    if(pad!=0){
        p->pad_l=(pad>> 0)&0xff;
        p->pad_r=(pad>> 8)&0xff;
        p->pad_t=(pad>>16)&0xff;
        p->pad_b=(pad>>24)&0xff;
        pnx+=p->pad_l+p->pad_r;
        pny+=p->pad_t+p->pad_b;
    }
    p->id=choose_optimal_cell_id( pnx, pny, sc->nx, sc->ny );
    cell=1<<(4+p->id);
    p->nbanks=cell*((cell>>1)+1);
    p->tile_x=cell-sc->nx+1;
    p->tile_y=cell-sc->ny+1;
    p->grid_x=(pnx+p->tile_x-sc->nx)/p->tile_x;
    p->grid_y=(pny+p->tile_y-sc->ny)/p->tile_y;
    if(((p->grid_x|p->grid_y)>0xffff)||((sc->nx|sc->ny)>=cell))
        return istatus_invalid_value;
    p->m=sc->pnc;
    p->n=sc->qnc;
    p->k=sa->bs*p->grid_x*p->grid_y;
    ek=PSIZE(p->k,7);
    p->lda=PSIZE(p->m,31)>>5;
    p->ldb=PSIZE(p->n,31)>>5;
    p->lda=(p->lda+(1^(p->lda&1)))<<5;
    p->ldb=(p->ldb+(1^(p->ldb&1)))<<5;
    p->abks=p->lda*ek+16;
    p->bbks=p->ldb*ek+16;
    p->cbks=p->lda*p->n+16;
    p->aldx=sa->nx*sa->ny;
    p->bldx=sb->nx*sb->ny;
    p->cldx=sc->nx*sc->ny;
    p->aldy=p->m*p->aldx;
    p->bldy=p->n*p->bldx;
    p->cldy=p->m*p->cldx;
    p->anx=sa->nx;
    p->any=sa->ny;
    p->bnx=sb->nx;
    p->bny=sb->ny;
    p->cnx=sc->nx;
    p->cny=sc->ny;
    if((p->grid_x|p->grid_y)!=1){
        uint32_t xk=PSIZE(p->k,15);
        uint32_t reso=p->grid_x*p->grid_y;
        p->xmag=idiv_magic(xk,reso);
        p->ymag=idiv_magic(reso,p->grid_x);
    }
    return istatus_success;
}