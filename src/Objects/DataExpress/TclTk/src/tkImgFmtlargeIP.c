/*
 * tkImgFmtIP.c --
 *
 *	A photo image file handler for mrcImage files.
 *
 */

static char sccsid[] = "";

#include "tk.h"
#undef DEBUG
#include "genUtil.h"
#include "largeIP.h"
#include <stdio.h>
#include <stdlib.h>

/*
static largeIPImageInfo info;
*/
/*
 * The maximum amount of memory to allocate for data read from the
 * file.  If we need more than this, we do it in pieces.
 */

#define MAX_MEMORY	10000		/* don't allocate > 10KB */

/*
 * Define LARGEIP, i.e. gray images and color images.
 */
#define IP 1

/*
 * The format record for the IP file format:
 */

static int		tkIPFileMatch _ANSI_ARGS_((FILE *f, char *fileName,
			    char *formatString, int *widthPtr,
			    int *heightPtr));
static int		tkIPFileRead _ANSI_ARGS_((Tcl_Interp *interp,
			    FILE *f, char *fileName, char *formatString,
			    Tk_PhotoHandle imageHandle, int destX, int destY,
			    int width, int height, int srcX, int srcY));
static int		tkIPFileWrite _ANSI_ARGS_((Tcl_Interp *interp,
			    char *fileName, char *formatString,
			    Tk_PhotoImageBlock *blockPtr));

Tk_PhotoImageFormat tkImgFmtIP = {
    "IP",			/* name */
    tkIPFileMatch,		/* fileMatchProc */
    NULL,			/* stringMatchProc */
    tkIPFileRead,		/* fileReadProc */
    NULL,			/* stringReadProc */
    tkIPFileWrite,		/* fileWriteProc */
    NULL,			/* stringWriteProc */
};


/*
 *----------------------------------------------------------------------
 *
 * tkIPFileMatch --
 *
 *	This procedure is invoked by the photo image type to see if
 *	a file contains image data in IP format.
 *
 * Results:
 *	The return value is 1 when data is mrc-formatted, and 0 otherwise.
 *
 *----------------------------------------------------------------------
 */

static int
tkIPFileMatch(f, fileName, formatString, widthPtr, heightPtr)
    FILE *f;			/* The image file, open for reading. */
    char *fileName;		/* The name of the image file. */
    char *formatString;		/* User-specified format string, or NULL. */
    int *widthPtr, *heightPtr;	/* The dimensions of the image are
				 * returned here if the file is a valid
				 * raw IP file. */
{
	largeIP ip;

	DEBUGPRINT("MATCH\n");
	if(0!=strcmp("IP", formatString)) {
		return 0;
	}
    largeIPHeaderRead(&ip, f, 0);
	*widthPtr = 1024;
	*heightPtr = 1024;
	return 1;
}


int
tkIPFileReadInfoSetCmd(ClientData clientData, Tcl_Interp* interp, int argc, char* argv[])
{
	return TCL_OK;
}
/*
 *----------------------------------------------------------------------
 *
 * tkIPFileRead--
 *
 *	This procedure is called by the photo image type to read
 *	IP format data from a file and write it into a given
 *	photo image.
 *
 * Results:
 *	A standard TCL completion code.  If TCL_ERROR is returned
 *	then an error message is left in interp->result.
 *
 * Side effects:
 *	The access position in file f is changed, and new data is
 *	added to the image given by imageHandle.
 *
 *----------------------------------------------------------------------
 */

static int
tkIPFileRead(interp, f, fileName, formatString, imageHandle, destX, destY,
	width, height, srcX, srcY)
    Tcl_Interp *interp;		/* Interpreter to use for reporting errors. */
    FILE *f;			/* The image file, open for reading. */
    char *fileName;		/* The name of the image file. */
    char *formatString;		/* User-specified format string, or NULL. */
    Tk_PhotoHandle imageHandle;	/* The photo image to write into. */
    int destX, destY;		/* Coordinates of top-left pixel in
				 * photo image to be written to. */
    int width, height;		/* Dimensions of block of photo image to
				 * be written to. */
    int srcX, srcY;		/* Coordinates of top-left pixel to be used
				 * in image being read. */
{
    int fileWidth, fileHeight;
    int nLines, nBytes, h, w;
    unsigned char *pixelPtr;
    Tk_PhotoImageBlock block;
	largeIP ip;
	double data;

	DEBUGPRINT("FileRead\n");
	DEBUGPRINT6("dest(%d,%d) Dim(%d,%d) src(%d,%d)\n", destX, destY, width, height, srcX, srcY);	
	/*
	info.start.x = srcX;  info.start.y = srcY;
	info.length.x = width; info.length.y = height;
	info.step.x  = 4;     info.step.y  = 4;
    largeIPRead(&ip, f, &info, 0);
	*/
	fileWidth  = width;
	fileHeight = height;
    if ((fileWidth <= 0) || (fileHeight <= 0)) {
		Tcl_AppendResult(interp, "IP image file \"", fileName,
		"\" has dimension(s) <= 0", (char *) NULL);
		return TCL_ERROR;
    }

    if ((srcX + width) > fileWidth) {
		width = fileWidth - srcX;
    }
    if ((srcY + height) > fileHeight) {
		height = fileHeight - srcY;
    }
    if ((width <= 0) || (height <= 0) || (srcX >= fileWidth) || (srcY >= fileHeight)) {
		return TCL_OK;
    }

    block.pixelSize = 1;
    block.offset[0] = 0;
	block.offset[1] = 0;
	block.offset[2] = 0;
    block.width = width;
	block.height = 1;
    block.pitch = block.pixelSize * fileWidth;

    Tk_PhotoExpand(interp, imageHandle, destX + width, destY + height);

	nLines = 1;
	nBytes = nLines*block.pitch;
    pixelPtr = (unsigned char *) ckalloc((unsigned) nBytes);
    block.pixelPtr = pixelPtr + srcX * block.pixelSize;

    for (h = height; h > 0; h --) {
		if(h<nLines) {
			nLines = h;
			nBytes = nLines*block.pitch;
		}
		block.height = 1;
		for(w=srcX; w<fileWidth ; w++) {
			DEBUGPRINT2("%d, %d\n", w, h);
			data = (double)ip.Image[w][h-1];
			data = data/65535.0*255.0;	
			block.pixelPtr[w] = (unsigned char)data;
		}
		Tk_PhotoPutBlock(interp, imageHandle, &block, destX, destY, width, 1, TK_PHOTO_COMPOSITE_SET);
		destY ++;
    }
    ckfree((char *) pixelPtr);
	largeIPFree(&ip);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * tkIPFileWrite--
 *
 *	This procedure is invoked to write image data to a file in IP 
 *	format.
 *
 * Results:
 *	A standard TCL completion code.  If TCL_ERROR is returned
 *	then an error message is left in interp->result.
 *
 * Side effects:
 *	Data is written to the file given by "fileName".
 *
 *----------------------------------------------------------------------
 */

static int
tkIPFileWrite(interp, fileName, formatString, blockPtr)
    Tcl_Interp *interp;
    char *fileName;
    char *formatString;
    Tk_PhotoImageBlock *blockPtr;
{
	return TCL_OK;
}
