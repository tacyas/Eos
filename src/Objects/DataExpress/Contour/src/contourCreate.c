/*
# contourCreate.c  1.3
# The latest update : 06/15/96 at 14:59:38
#
#@(#) contourCreate ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : contourCreate 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)contourCreate ver1.3; Date:96/06/15 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Contour.h"
#include "Memory.h"

contourFlag flagContour;

/* search contour lines in a boxel */
void createContourALine(contourLine* ls, contourArgs c)
{
    double c0, c1, c2, c3;
    double xc, yc;
    double xc1, yc1;
    double xc2, yc2;
    double fcx00x10, fcy00y01, fcx01x11, fcy10y11, fc;
    double x00x10, x01x11, y00y01, y10y11;
    contourArgs ctmp;

    if(c.f00==0.0) {
        c.f00 = CONTOUR_ACCURACY;
    }
    if(c.f01==0.0) {
        c.f01 = CONTOUR_ACCURACY;
    }
    if(c.f11==0.0) {
        c.f11 = CONTOUR_ACCURACY;
    }
    if(c.f10==0.0) {
        c.f10 = CONTOUR_ACCURACY;
    }
    if(c.f00*c.f01<0.0) { /* -+** */
        y00y01 = (c.y*c.f01 - (c.y+c.dy)*c.f00)/(c.f01-c.f00);
    } else {
		y00y01 = 0.0;
	}
    if(c.f01*c.f11<0.0) { /* *-+* */
        x01x11 = (c.x*c.f11 - (c.x+c.dx)*c.f01)/(c.f11-c.f01);
    } else {
		x01x11 = 0.0;
    } 
    if(c.f11*c.f10<0.0) { /* **-+ */
        y10y11 = (c.y*c.f11 - (c.y+c.dy)*c.f10)/(c.f11-c.f10);
    } else {
		y10y11 = 0.0;
    }
    if(c.f10*c.f00<0.0) { /* -***+ */
        x00x10 = (c.x*c.f10 - (c.x+c.dx)*c.f00)/(c.f10-c.f00);
    } else {
		x00x10 = 0.0;
	}
    if((c.f00>0 && c.f01<0 && c.f11>0 && c.f10<0)    /* +-+- */
    || (c.f00<0 && c.f01>0 && c.f11<0 && c.f10>0)) { /* -+-+ */
        c0 = c.f00 - c.f01 + c.f11 - c.f10;
        c1 = c.f10 - c.f00;
        c2 = c.f01 - c.f00;
        c3 = c.f00;
        fc = (c0*c3 - c1*c2)/c0;
        if(fc==0.0) {
            fc = CONTOUR_ACCURACY;
        }
    } else {
		fc = CONTOUR_ACCURACY;
	}
    if(c.f00>0 && c.f01>0 && c.f11>0 && c.f10>0) {        /* ++++ */
    } else if(c.f00<0 && c.f01<0 && c.f11<0 && c.f10<0) { /* ---- */
    } else if(c.f00<0 && c.f01>0 && c.f11>0 && c.f10>0) { /* -+++ */
        appendContourLine0(ls, x00x10, c.y, c.x, y00y01, c.z);
    } else if(c.f00>0 && c.f01<0 && c.f11>0 && c.f10>0) { 
        appendContourLine0(ls, c.x, y00y01, x01x11, c.y+c.dy, c.z);
    } else if(c.f00>0 && c.f01>0 && c.f11<0 && c.f10>0) {
        appendContourLine0(ls, x01x11, c.y+c.dy, c.x+c.dx, y10y11, c.z);
    } else if(c.f00>0 && c.f01>0 && c.f11>0 && c.f10<0) {
        appendContourLine0(ls, c.x+c.dx, y10y11, x00x10, c.y, c.z);
    } else if(c.f00>0 && c.f01>0 && c.f11<0 && c.f10<0) { /* --++ */
        appendContourLine0(ls, x01x11, c.y+c.dy, x00x10, c.y, c.z);
    } else if(c.f00<0 && c.f01>0 && c.f11>0 && c.f10<0) {
        appendContourLine0(ls, c.x+c.dx, y10y11, c.x, y00y01, c.z);
    } else if(c.f00<0 && c.f01<0 && c.f11>0 && c.f10>0) {
        appendContourLine0(ls, x00x10, c.y, x01x11, c.y+c.dy, c.z);
    } else if(c.f00>0 && c.f01<0 && c.f11<0 && c.f10>0) {
        appendContourLine0(ls, c.x, y00y01, c.x+c.dx, y10y11, c.z);
    } else if(c.f00>0 && c.f01<0 && c.f11>0 && c.f10<0) { /* +-+- */
        if(fc>=0) {
            appendContourLine0(ls, c.x+c.dx, y10y11, x00x10, c.y,      c.z);
            appendContourLine0(ls, c.x,      y00y01, x01x11, c.y+c.dy, c.z);
        } else {
            appendContourLine0(ls, c.x,      y00y01, x00x10, c.y,      c.z);
            appendContourLine0(ls, c.x+c.dx, y10y11, x01x11, c.y+c.dy, c.z);
        }
    } else if(c.f00<0 && c.f01>0 && c.f11<0 && c.f10>0) { /* -+-+ */
        if(fc>=0) {
            appendContourLine0(ls, x00x10, c.y,      c.x,      y00y01, c.z);
            appendContourLine0(ls, x01x11, c.y+c.dy, c.x+c.dx, y10y11, c.z);
        } else {
            appendContourLine0(ls, x00x10, c.y,      c.x+c.dx, y10y11, c.z);
            appendContourLine0(ls, x01x11, c.y+c.dy, c.x,      y00y01, c.z);
        }
    } else if(c.f00>0 && c.f01<0 && c.f11<0 && c.f10<0) { /* ---+ */
        appendContourLine0(ls, c.x, y00y01, x00x10, c.y, c.z);
    } else if(c.f00<0 && c.f01>0 && c.f11<0 && c.f10<0) {
        appendContourLine0(ls, x01x11, c.y+c.dy, c.x, y00y01, c.z);
    } else if(c.f00<0 && c.f01<0 && c.f11>0 && c.f10<0) {
        appendContourLine0(ls, c.x+c.dx, y10y11, x01x11, c.y + c.dy, c.z);
    } else if(c.f00<0 && c.f01<0 && c.f11<0 && c.f10>0) {
        appendContourLine0(ls, x00x10, c.y, c.x+c.dx, y10y11, c.z);
    } else {
        fprintf(stderr, "Something Wrong in createContourLine:%f,%f,%f,%f\n", c.f00, c.f01, c.f10, c.f11);
    }
}

void
appendContourLine0(contourLine* l, contourParaTypeReal xc1, contourParaTypeReal yc1, contourParaTypeReal xc2, contourParaTypeReal yc2, contourParaTypeReal z)
{
    contourALine* pl;

    if(l->top==NULL) {
        if(NULL==(l->top = (contourALine*)malloc(sizeof(contourALine)))) {
            fprintf(stderr, "Not Allocate contourLine\n");
            exit(EXIT_FAILURE);
        }
        l->current = l->top;
        l->current->before = NULL;
        l->n = 1;
    } else {
        if(NULL==(pl = (contourALine*)malloc(sizeof(contourALine)))) {
            fprintf(stderr, "Not Allocate contourLine\n");
            exit(EXIT_FAILURE);
        }
        l->current->next = pl;
        l->current->next->before = l->current;
        l->current = pl;
        l->n++;
    }
    switch(flagContour) {
        case contourFlagXSection: {
            l->current->p0.x = z;
            l->current->p0.y = xc1;
            l->current->p0.z = yc1;
            l->current->p1.x = z;
            l->current->p1.y = xc2;
            l->current->p1.z = yc2;
            break;
        }
        case contourFlagYSection: {
            l->current->p0.x = yc1;
            l->current->p0.y = z;
            l->current->p0.z = xc1;
            l->current->p1.x = yc2;
            l->current->p1.y = z;
            l->current->p1.z = xc2;
            break;
        }
        case contourFlagZSection: {
            l->current->p0.x = xc1;
            l->current->p0.y = yc1;
            l->current->p0.z = z;
            l->current->p1.x = xc2;
            l->current->p1.y = yc2;
            l->current->p1.z = z;
            break;
        }
    }
    l->current->next = NULL;
#ifdef DEBUG
    fprintf(stderr, "%5d)%10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n", l->n, xc1, yc1, z, xc2, yc2, z);
    fprintf(stderr, "%5d)%10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n", l->n, l->current->p0.x, l->current->p0.y, l->current->p0.z, l->current->p1.x, l->current->p1.y, l->current->p1.z);
#endif
}


/* create contour lines : chane trace */
void 
createContourLine(contourLines* ls, contourLine* l)
{
    contourLine* pl;
    contourParaTypeInteger flag;
    
    flag = 0;
    while(l->n>0) {
        l->current = l->top;
        if(flag==0) {
            if(ls->top==NULL) {
                ls->top=(contourLine*)memoryAllocate(sizeof(contourALine), "Not Allcate contourLine in createContourLine.\n");
                ls->current = ls->top;
                ls->n = 1;
            } else {
                pl=(contourLine*)memoryAllocate(sizeof(contourALine), "Not Allocate contourLine in createContourLine.\n");
                ls->current->next = pl;
                ls->current = pl;
                ls->n++;
            }
            ls->current->current = ls->current->top = NULL;
            appendContourLine1(ls->current, l);
            ls->next = NULL;
            flag = 1;
        } else {
            while(l->current!=NULL) {
                if(fabs((double)(l->current->p0.x - ls->current->current->p1.x)) < CONTOUR_ACCURACY*10
                 &&fabs((double)(l->current->p0.y - ls->current->current->p1.y)) < CONTOUR_ACCURACY*10
                 &&fabs((double)(l->current->p0.z - ls->current->current->p1.z)) < CONTOUR_ACCURACY*10) {
                    appendContourLine1(ls->current, l);
                    flag = 1;
                    break;
                } 
                l->current = l->current->next;
            }
            if(l->current==NULL) {
                flag = 0;
            }
        }
    }
}

void
appendContourLine1(contourLine* l, contourLine* als)
{
    contourALine* pl;

    if(l->top==NULL) {
        l->top = (contourALine*)memoryAllocate(sizeof(contourALine), "Not Allocate contourLine\n");
        l->current = l->top;
        l->current->before = NULL;
        l->n = 1;
    } else {
        pl = (contourALine*)memoryAllocate(sizeof(contourALine), "Not Allocate contourLine\n");
        l->current->next = pl;
        l->current->next->before = l->current;
        l->current = pl;
        l->n++;
    }
    l->current->p0.x = als->current->p0.x;
    l->current->p0.y = als->current->p0.y;
    l->current->p0.z = als->current->p0.z;
    l->current->p1.x = als->current->p1.x;
    l->current->p1.y = als->current->p1.y;
    l->current->p1.z = als->current->p1.z;
    l->current->next = NULL;
    if(als->current->before==NULL) {
        als->top         = als->current->next;
        als->top->before = NULL;
    } else {
        als->current->before->next = als->current->next;
    }
    als->n--;
}

/* craete contourLines at each section */
void 
createContourLines(contourLines* ls, contourImage ci)
{
    contourLine* al;
    contourParaTypeInteger iw, ih, is;
    contourParaTypeReal     w,  h,  s;
    contourArgs             arg;                            


    if(NULL==(al=(contourLine*)malloc(sizeof(contourLine)))) {
        fprintf(stderr, "Not Allocate contourLine al in createContourLines\n");
        exit(EXIT_FAILURE); 
    }
    al->current = al->top = NULL;
    ls->current = ls->top = NULL;
    arg.dx = ci.w.d; arg.dy = ci.h.d;
    arg.z  = ci.section;
    for(iw=0, w=ci.w.Min; iw<ci.w.n; iw++, w+=ci.w.d) {
        for(ih=0, h=ci.h.Min; ih<ci.h.n; ih++, h+=ci.h.d) {
            arg.f00 = ci.image2[ iw   %ci.w.n  +(ih  )%ci.h.n*ci.w.n];
            arg.f01 = ci.image2[ iw   %ci.w.n  +(ih+1)%ci.h.n*ci.w.n];
            arg.f11 = ci.image2[(iw+1)%ci.w.n  +(ih+1)%ci.h.n*ci.w.n];
            arg.f10 = ci.image2[(iw+1)%ci.w.n  +(ih  )%ci.h.n*ci.w.n];
            arg.x  = w; arg.y = h;
            createContourALine(al, arg);
        }
    }
    if(al->top==NULL) {
        return;
    } else {
        createContourLine(ls, al);
    }
}

/* create contourLines at all sections */
void 
createContour(contourLinesSet* lsset, contourImage ci, contourParaTypeReal level, contourFlag flag)
{
    contourParaTypeInteger ix, iy, iz;
    contourParaTypeReal     x,  y,  z;
    contourLines* pl;
             
    flagContour = flag;
    switch(flag) {
        case contourFlagXSection: {
            if(NULL==(ci.image2=(contourParaTypeReal*)malloc(sizeof(contourParaTypeReal)*ci.y.n*ci.z.n))) {
                fprintf(stderr, "Not Allocate Memory in createContour.\n");
                exit(EXIT_FAILURE);
            }
            for(ix=0, x=ci.x.Min; ix<ci.x.n; ix++, x+=ci.x.d) {
                for(iy=0, y=ci.y.Min; iy<ci.y.n; iy++, y+=ci.y.d) {
                    for(iz=0, z=ci.z.Min; iz<ci.z.n; iz++, z+=ci.z.d) {
                        ci.image2[iy+iz*ci.y.n] = ci.image[ix+iy*ci.x.n+iz*ci.x.n*ci.y.n] - level;
                    }
                }
                if(lsset->top==NULL) {
                    if(NULL==(lsset->top = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLine\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current = lsset->top;
                    lsset->n=0;
                } else {
                    if(NULL==(pl = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLines\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current->next = pl;
                    lsset->current = pl;
                    lsset->n++;
                }
                ci.w = ci.y;
                ci.h = ci.z;
                ci.section = x;
                createContourLines(lsset->current, ci);
            }
            free(ci.image2);
            break;
        }
        case contourFlagYSection: {
            if(NULL==(ci.image2=(contourParaTypeReal*)malloc(sizeof(contourParaTypeReal)*ci.z.n*ci.x.n))) {
                fprintf(stderr, "Not Allocate Memory in createContour.\n");
                exit(EXIT_FAILURE);
            }
            for(iy=0, y=ci.y.Min; iy<ci.y.n; iy++, y+=ci.y.d) {
                for(iz=0, z=ci.z.Min; iz<ci.z.n; iz++, z+=ci.z.d) {
                    for(ix=0, x=ci.x.Min; ix<ci.x.n; ix++, x+=ci.x.d) {
                        ci.image2[iz+ix*ci.z.n] = ci.image[ix+iy*ci.x.n+iz*ci.x.n*ci.y.n] - level;
                    }
                }
                if(lsset->top==NULL) {
                    if(NULL==(lsset->top = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLine\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current = lsset->top;
                    lsset->n=0;
                } else {
                    if(NULL==(pl = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLines\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current->next = pl;
                    lsset->current = pl;
                    lsset->n++;
                }
                ci.w = ci.z;
                ci.h = ci.x;
                ci.section = y;
                createContourLines(lsset->current, ci);
            }
            free(ci.image2);
            break;
        }
        case contourFlagZSection: {
            if(NULL==(ci.image2=(contourParaTypeReal*)malloc(sizeof(contourParaTypeReal)*ci.x.n*ci.y.n))) {
                fprintf(stderr, "Not Allocate Memory in createContour.\n");
                exit(EXIT_FAILURE);
            }
            for(iz=0, z=ci.z.Min; iz<ci.z.n; iz++, z+=ci.z.d) {
                for(ix=0, x=ci.x.Min; ix<ci.x.n; ix++, x+=ci.x.d) {
                    for(iy=0, y=ci.y.Min; iy<ci.y.n; iy++, y+=ci.y.d) {
                        ci.image2[ix+iy*ci.x.n] = ci.image[ix+iy*ci.x.n+iz*ci.x.n*ci.y.n] - level;
                    }
                }
                if(lsset->top==NULL) {
                    if(NULL==(lsset->top = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLine\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current = lsset->top;
                    lsset->n=0;
                } else {
                    if(NULL==(pl = (contourLines*)malloc(sizeof(contourLines)))) {
                        fprintf(stderr, "Not Allocate contourLines\n");
                        exit(EXIT_FAILURE);
                    }
                    lsset->current->next = pl;
                    lsset->current = pl;
                    lsset->n++;
                }
                ci.w = ci.x;
                ci.h = ci.y;
                ci.section = z;
                createContourLines(lsset->current, ci);
            }
            free(ci.image2);
            break;
        }
        default: {
            fprintf(stderr, "Not Supported contourFlag %d in createContour\n", flag);
            exit(EXIT_FAILURE);
        }
    }
}
