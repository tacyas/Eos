/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRuby ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRuby 
#%Z% Attention
#%Z%
static char __sccs_id[] = "%Z%mrcImageRuby ver%I%; Date:%D% %Z%";
*/

#include <ruby.h>
#include "mrcImage.h"
#include "Memory.h"
#include "File.h"



static void 
lmrcImageStructFreeForRuby(mrcImage* mrc)
{
	if(mrc) {
		mrcImageFree(mrc, "in lmrcImageStructFreeForRuby");
		free(mrc);
	}
}

static VALUE
lmrcImageStructNewForRuby(VALUE mrcImageClass, int Nx, int Ny, int Nz, mrcImageMode mode)
{
	VALUE obj;
	mrcImage* mrc;

	mrc = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageStructOpenForRuby");
	mrc->HeaderN.x = Nx;
	mrc->HeaderN.y = Ny;
	mrc->HeaderN.z = Nz;
	mrc->HeaderMode = mode;
	mrcInit(mrc, NULL);

	/* Converto the struct on C to the Object on Ruby */
	obj = Data_Wrap_Struct(mrcImageClass, 0, lmrcImageStructFreeForRuby, mrc);

	return obj;
}

static VALUE
lmrcImageStructOpenForRuby(VALUE mrcImageClass, char* mrcImageFileName)
{
	VALUE obj;
	mrcImage* mrc;

	Check_SafeStr(mrcImageFileName);
	
	mrc = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageStructOpenForRuby");
	mrcInit(mrc, mrcImageFileName);

	/* Converto the struct on C to the Object on Ruby */
	obj = Data_Wrap_Struct(mrcImageClass, 0, lmrcImageStructFreeForRuby, mrc);

	return obj;
}

void
Init_mrc() 
{
	VALUE cmrc;

	cmrc = rb_define_class("mrc", rb_cObject); 

	rb_define_singleton_method(cmrc, "new", lmrcImageStructNewForRuby, 4); 
	rb_define_singleton_method(cmrc, "open", lmrcImageStructOpenForRuby, 1); 
}

