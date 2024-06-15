/*
# rigakuImage.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : rigakuImage.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef RIGAKU_IMAGE_H
#define RIGAKU_IMAGE_H

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct riggkuTag rigakuTag;

struct rigakuTag {
    char* tag;
    char* content;
    rigakuTag* next;
}

typedef struct rigakuImage {
    int   HeaderBytes;
    char* HeaderAll; 
    rigakuTag*  startHeader; 
    rigakuTag*  currentHeader; 

    int dim;
    int size1;
    int size2;
    int size3;
    int dataType;
    
    void*  Image;
    unsigned char*    integer1Image;
    unsigned short*   integer2Image;
    int*    integer4Image;
    float*  real4Image;
    double* real8Image;

} rigakuImgae;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */



/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
