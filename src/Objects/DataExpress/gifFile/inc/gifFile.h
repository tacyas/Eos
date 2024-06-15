#ifndef GIF_FILE_H
#define GIF_FILE_H

#include "gif_lib.h"

/* struct begin */

typedef struct gifFileHeader {
	char sig[3];
	char ver[3];
} gifFileHeader;
/* struct end */

/* constant begin */
#define scdGCT     (0x80)
#define scdGCTcres (0x70)
#define scdGCTsort (0x08)
#define scdGCTsize (0x07)
/* constant end */

/* struct begin */
typedef struct gifFileScreenDesc {
	unsigned short scwidth;
	unsigned short scheight;
	unsigned char  flags;
	unsigned char  bgclr;
	unsigned char  pixasp;
} gifFileScreenDesc;
/* struct end */

/* constant begin */
#define imdLCT       (0x80)
#define imdInterlace (0x40)
#define imdLCTsort   (0x20)
#define imdRESV      (0x18)
#define imdLCTsize   (0x07)
/* constant end */

/* struct begin */
typedef struct gifFileImageDesc {
	unsigned char id;
	unsigned short xleft;
	unsigned short ytop;
	unsigned short imwidth;
	unsigned short imheight;
	unsigned char  flags;
} gifFileImageDesc;

typedef struct gifFileColorTable {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} gifFileColorTable;

typedef struct gifFileImageDefinition {
	gifFileImageDesc   Desc;
	gifFileColorTable* LCT; 
} gifFileImageDefinition;

typedef struct gifFileCtrlExtensions {
	unsigned char  id;
	unsigned char  label; 
	unsigned char  size;
	unsigned char  flags; 
	unsigned short delay;
	unsigned char  trcrl; 
} gifFileCtrlExtensions;

typedef struct gifFileCommentExtensions {
	unsigned char id;
	unsigned char label;
} gifFileCommentExtensions;

typedef struct gifFileTextExtensions {
	unsigned char  id;
	unsigned char  label; 
	unsigned char  size;
	unsigned char  xleft; 
	unsigned short ytop;
	unsigned char  txwidth; 
	unsigned char  txheight;
	unsigned char  cewidth; 
	unsigned char  ceheight;
	unsigned char  fgclr; 
	unsigned short bgclr;
} gifFileTextExtensions;

typedef struct gifFileApplicationExtensions {
	unsigned char  id;
	unsigned char  label; 
	unsigned char  size;
	char           apname[8];
	char           apcode[3];
} gifFileApplicationExtensions;


typedef struct gifFile {
	gifFileHeader     		Header;
	gifFileScreenDesc 		ScrDesc;
	gifFileColorTable*   	GCT;
	long nImage;
	gifFileImageDefinition* ImageDef;
	char                	Tailer;
} gifFile;

/* struct end */

/* constant begin */
#define OUT_OF_MEMORY -10
#define BAD_CODE_SIZE -20
#define READ_ERROR -1
#define WRITE_ERROR -2
#define OPEN_ERROR -3
#define CREATE_ERROR -4
/* constant end */

/* struct begin */
#define LOCAL static
#define IMPORT extern

#define FAST register

typedef short WORD;
typedef unsigned short UWORD;
typedef char TEXT;
typedef unsigned char UTINY;
typedef long LONG;
typedef unsigned long ULONG;
typedef int INT;
/* struct end */


#include "mrcImage.h"
/* prototype begin */
extern int lmrc2gif(char* out, mrcImage* in, ColorMapObject* ColorMap, long mode);
extern int lmrc2gifColor(char* out, mrcImage* r, mrcImage* g, mrcImage* b, ColorMapObject* ColorMap, int n, int nr, int ng, int nb, long mode);

extern ColorMapObject* gifColorMapInit(int n, long mode);
extern ColorMapObject* gifColorMapGrey(ColorMapObject* ColorMap, int n);
extern ColorMapObject* gifColorMapColor(ColorMapObject* ColorMap, int n, int nr, int ng, int nb);
/* prototype end */

#endif /* GIF_FILE_H */