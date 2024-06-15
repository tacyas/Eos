#ifndef LARGE_IP_H
#define LARGE_IP_H

/* constant begin */
#define LARGE_IP_IMAGE_WIDTH (4000)
#define LARGE_IP_IMAGE_HEIGHT (8192)
/* constant end */ 

/* struct begin */
typedef unsigned short largeIPImageType;
typedef long  largeIPParaTypeInteger;
typedef float largeIPParaTypeReal;

typedef struct largeIPParaTypeIntCoord {
	largeIPParaTypeInteger x;
	largeIPParaTypeInteger y;
} largeIPParaTypeIntCoord;

typedef struct largeIPImageInfo {
	largeIPParaTypeIntCoord start;
	largeIPParaTypeIntCoord step;
	largeIPParaTypeIntCoord length;
} largeIPSubImageInfo;

#ifdef M68
typedef struct largeIP {
        char    name[10];
        char    vers[10];
        char    crnm[20];       /* Sample name */
        char    crsy[12];
        float   alng;
        float   blng;
        float   clng;
        float   alfa;
        float   beta;
        float   gamm;
        char    spgr[12];
        float   mosc;
        char    memo[80];       /* Film Cassette type */
        char    res1[84];

        char    date[12];
        char    opnm[20];       /* Operator */
        char    trgt[4];        /* X-ray source */
        float   wlng;           /* Wave length */
        char    mcro[20];       /* Monochromator */
        float   m2ta;
        char    colm[20];       /* Collimator */
        char    filt[4];
        float   camr;           /* Camera length */
        float   vltg;           /* Acceralation */
        float   crnt;           /* Ring current */
        char    focs[12];       /* Beam line */
        char    optc[80];
        int             cyld;
        float   weis;           /* Coupling constant */
        char    res2[56];

        char    mnax[4];
        char    bmax[4];
        float   phi0;           /* Speed of omega */
        float   phis;           /* Omega start */
        float   phie;           /* Omega end   */
        long    oscn;           /* Number of oscillations */
        float   fext;           /* Exposure time */
        float   drtx;           /* Beam position Y */
        float   drtz;           /* Beam position Z */
        float   omga;
        float   fkai;
        float   thta;
        float   mu;                     /* Mu */
        char    res3[204];

        long    xpxl;           /* Number of pixel (drum scanning direction) */
        long    zpxl;           /* Number of pixel (drum axis direction) */
        float   xsiz;           /* Pixel size */
        float   zsiz;           /* pixel size */
        long    rlng;           /* Record length of drum scanning direction */
        long    rnum;           /* Number of record == Read Line */
        long    ipst;           /* Start line */
        long    ipnm;           /* IP number */
        float   rato;
        float   ft_1;
        float   ft_2;
        char    host[10];
        char    ip[10];
        int             dr_x;
        int             dr_z;
        int             drxz;
        char    res4[180];

        char    file[16];
        char    cmnt[20];
        char    smpl[20];
        int             iext;
        int             reso;
        int             save;
        long    dint;
        int             byte;
        int             init;
        int             ipus;
        int             dexp;
        char    res5[936];
        char    res6[2048];
} largeIPHeader;
#else
typedef struct largeIPHeader {
        char    name[10];
        char    vers[10];
        char    crnm[20];       /* Sample name */
        char    crsy[12];
        unsigned char    alng[4]; /* float */
        unsigned char    blng[4]; /* float */                           
        unsigned char    clng[4]; /* float */
		unsigned char    alfa[4]; /* float */
        unsigned char    beta[4]; /* float */
		unsigned char    gamm[4]; /* float */
        char    spgr[12];
		unsigned char    mosc[4]; /* float */
        char    memo[80];       /* Film Cassette type */
        char    res1[84];

        char    date[12];
        char    opnm[20];       /* Operator */
        char    trgt[4];        /* X-ray source */
        unsigned char    wlng[4];        /* Wave length */   /* float */
        char    mcro[20];       /* Monochromator */
        unsigned char    m2ta[4]; /* float */
        char    colm[20];       /* Collimator */
        char    filt[4];
        unsigned char    camr[4];        /* Camera length */ /* float */
        unsigned char    vltg[4];        /* Acceralation */ /* float */
        unsigned char    crnt[4];        /* Ring current */ /* float */
        char    focs[12];       /* Beam line */
        char    optc[80];
        unsigned char    cyld[4]; /* int */
        unsigned char    weis[4];        /* Coupling constant */ /* float */
        char    res2[56];

        char    mnax[4];
        char    bmax[4];
        unsigned char    phi0[4];        /* Speed of omega */ /* float */
        unsigned char    phis[4];        /* Omega start */ /* float */
        unsigned char    phie[4];        /* Omega end   */ /* float */
        unsigned char    oscn[4];        /* Number of oscillations */ /* int (alpha) */
        unsigned char    fext[4];        /* Exposure time */ /* float */
        unsigned char    drtx[4];        /* Beam position Y */ /* float */
        unsigned char    drtz[4];        /* Beam position Z */ /* float */
		unsigned char    omga[4]; /* float */
        unsigned char    fkai[4]; /* float */
        unsigned char    thta[4]; /* float */
        unsigned char    mu[4];          /* Mu */ /* float */
        char    res3[204];

        unsigned char    xpxl[4];        /* Number of pixel (drum scanning direction) */ /* int (alpha) */
        unsigned char    zpxl[4];        /* Number of pixel (drum axis direction) */ /* int (alpha) */
        unsigned char    xsiz[4];        /* Pixel size */ /* float */
		unsigned char    zsiz[4];        /* pixel size */ /* float */
		unsigned char    rlng[4];        /* Record length of drum scanning direction */ /* int (alpha) */
		unsigned char    rnum[4];        /* Number of record == Read Line */ /* int (alpha) */
        unsigned char    ipst[4];        /* Start line */ /* int (alpha) */
        unsigned char    ipnm[4];        /* IP number */ /* int (alpha) */
        unsigned char    rato[4]; /* float */
        unsigned char    ft_1[4]; /* float */
        unsigned char    ft_2[4]; /* float */
        char    host[10];
        char    ip[10];
        unsigned char    dr_x[4]; /* int */
        unsigned char    dr_z[4]; /* int */
        unsigned char    drxz[4]; /* int */
        char    res4[180];

        char    file[16];
        char    cmnt[20];
        char    smpl[20];
        unsigned char   iext[4]; /* int */
        unsigned char   reso[4]; /* int */
        unsigned char   save[4]; /* int */
        unsigned char   dint[4]; /* int (alpha) */
        unsigned char   byte[4]; /* int */
        unsigned char   init[4]; /* int */
        unsigned char   ipus[4]; /* int */
        unsigned char   dexp[4]; /* int */
        char    res5[936];
        char    res6[2048];
} largeIPHeader;
#endif
 
typedef struct {
	largeIPHeader Header;
	unsigned short** Image;
} largeIP;
/* struct end */

/* prototype begin */
extern void largeIPRead(largeIP* ip, FILE* fpt, largeIPSubImageInfo* info, long mode);
extern void largeIPImageRead(largeIP* ip, FILE* fpt, largeIPSubImageInfo* info, long mode);
extern void largeIPHeaderRead(largeIP* ip, FILE* fpt, long mode);
extern void largeIPInit(largeIP* ip, largeIPSubImageInfo* info, long mode);
extern void largeIPFree(largeIP* ip);
/* prototype end */
#endif
