/*
# molvieDefault.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : molvieDefault.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef MOLVIEDEFAULT_H
#define MOLVIEDEFAULT_H

#include <stdlib.h>
#include "eosOpenGL.h"
#include "lmolvie.h"

#define WIN_WIDTH  (600)
#define WIN_HEIGHT (600)
#define WIN_POSX   (0)
#define WIN_POSY   (0)
#define WIN_NAME   "molvieProjection ver. 1.00"

#define SUBWIN_WIDTH  (256)
#define SUBWIN_HEIGHT (256)
#define SUBWIN_POSX   (610)
#define SUBWIN_POSY   (0)
#define SUBWIN_NAME   "Ortho"

extern int main(int argc, char* argv[]);
extern void lmolvieProjectionKeyboard(unsigned char pushkey, int x, int y);

#endif /* MOLVIEDEFAULT_H */
