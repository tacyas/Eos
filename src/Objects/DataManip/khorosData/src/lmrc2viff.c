/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc2viff ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrc2viff 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrc2viff ver%I%; Date:%D% %Z%";
#include "../inc/khorosData.h"
#include "mrcImage.h"
#define DEBUG
#include "genUtil.h"

int
lmrc2viff(mrcImage* mrc, kobject viff)
{
    char *lib="Eos_proc";
    char *rtn="lmrc2viff";
    int i, j, type, cols, rows, secs, size, num, num2, start, num_regs;
    klist *objlist=NULL;
    double* data = NULL;
    double* tmp_ptr = NULL;
    double tmpdata;

    cols = mrc->HeaderN.x;
    rows = mrc->HeaderN.y;
    secs = mrc->HeaderN.z;
    switch(mrc->HeaderMode) {
        case mrcCharImage: {
            type = KBYTE;
            break;
        }
        case mrcShortImage: {
            type = KSHORT;
            break;
        }
        case mrcLongImage: {
            type = KLONG;
            break;
        }
        case mrcFloatImage: {
            type = KFLOAT;
            break;
        }
        case mrcDoubleImage: {
            type = KDOUBLE;
            break;
        }
        default: {
            fprintf(stderr, "Not supported\n");
			exit(EXIT_FAILURE);
        }
    }

    if(!kpds_query_value(viff)) {
        KCALL(kpds_create_value(viff));
    }
    KCALL(kpds_set_attributes(viff,KPDS_VALUE_SIZE,cols,rows,1,1,1, KPDS_VALUE_DATA_TYPE,type,NULL));
    KCALL((viff = kpds_reference_object(viff)) != KOBJECT_INVALID);
    objlist = klist_add(objlist,viff,"KOBJECT");
    KCALL(kpds_set_attribute(viff,KPDS_VALUE_DATA_TYPE,KDOUBLE));
    KCALL(kpds_set_attribute(viff,KPDS_VALUE_SIZE,cols,1,1,1,1));
    KCALL(kpds_get_attribute(viff,KPDS_VALUE_OPTIMAL_REGION_SIZE,
                                    &num,NULL,NULL,NULL,NULL,NULL));
    KCALL(kpds_set_attributes(viff,KPDS_VALUE_SIZE,cols,rows,secs,1,1,
                                   KPDS_VALUE_REGION_SIZE,num,1,1,1,1,NULL));
    if (num != cols) {
		fprintf(stderr, "start!=num: Not supported in lmrc2viff.\n");
        size=num;
    } else {
        size=cols;
    }       
    if(NULL==(data = (double *)kpds_get_data(viff,KPDS_VALUE_REGION,(kaddr)data))) {
        kerror(lib,rtn,"Failed to allocated work buffer.");
        (void)klist_free(objlist,(kfunc_void)lkcall_free);
        return FALSE;
    }
    objlist = klist_add(objlist,data,"KMALLOC");
    KCALL(kpds_get_attribute(viff,KPDS_VALUE_REGION_INFO, NULL,NULL,NULL,NULL,NULL,&num_regs));
    /*num_regs = rows*cols/start;*/
    for (num=0; num<num_regs; num++) {
        start = (size*num)%cols;
        tmp_ptr = (data+((size*num)%cols));
        if(NULL==tmp_ptr) {
            if((tmp_ptr = (double*)kmalloc(size*sizeof(double))) == NULL) {
                return FALSE;
            }
        }
        for(i=0, j=start; i < size; i++, j++) { 
#ifdef II 
            mrcPixelDataGet(mrc, j, num, 0.0, &tmpdata, mrcPixelRePart, mrcPixelHowNearest);
#else
            mrcPixelDataGet(mrc, j, rows-num-1, 0.0, &tmpdata, mrcPixelRePart, mrcPixelHowNearest);
#endif
            tmp_ptr[i] = tmpdata;
        }
        KCALL(kpds_put_data(viff,KPDS_VALUE_REGION,data));
    }
    (void)klist_free(objlist,(kfunc_void)lkcall_free);
    return TRUE;
}
