/*
# mrc2hdf : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc2hdf
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <float.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageProjection.h"
#include <hdf5.h>

typedef struct lmrc2hdfInfo {
	int   numFile;
    int   nResolution;
    int flagIn;
    mrcImage* in;
    float inColor[4];
    int flagIn2;
    mrcImage* in2;
    float in2Color[4];
} lmrc2hdfInfo;

typedef enum lmrc2hdfMode {
	a=0,
	b=1
} lmrc2hdfMode;

extern int lmrc2hdfimaris(hid_t* out, mrcImage* in, lmrc2hdfInfo* linfo, int mode);
extern int lmrc2hdf(hid_t* out, mrcImage* in, lmrc2hdfInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrc2hdfInfo info;
    lmrc2hdfInfo linfo;
    mrcImage* in=NULL;
    hid_t   out;
    herr_t  status;

    int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    if(info.flagIn) {
        linfo.numFile = 1;
        linfo.in = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in main");
        mrcFileRead(linfo.in, info.In, "in main", 0);
        linfo.flagIn = 1;
        linfo.flagIn2 = 0;
    } else if(info.flagInList) {
        linfo.numFile = info.flagInList;
        linfo.flagIn = info.flagInList;
        linfo.in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.numFile, "in main");
        for(i=0; i<linfo.numFile; i++) {
            mrcFileRead(&(linfo.in[i]), info.InList[i], "in main", 0);
        }
        linfo.inColor[0] = info.IR;
        linfo.inColor[1] = info.IG;
        linfo.inColor[2] = info.IB;
        linfo.inColor[3] = info.IA;
        if(info.flagInList2) {
            if(linfo.numFile != info.flagInList2) {
                fprintf(stderr, "Different Number between -I and -I2: %ld %ld\n", info.flagInList, info.flagInList2);
                exit(EXIT_FAILURE);
            }
            linfo.flagIn2 = info.flagInList2;
            linfo.in2 = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.numFile, "in main");
            for(i=0; i<linfo.numFile; i++) {
                mrcFileRead(&(linfo.in2[i]), info.InList2[i], "in main", 0);
            }
            linfo.in2Color[0] = info.I2R;
            linfo.in2Color[1] = info.I2G;
            linfo.in2Color[2] = info.I2B;
            linfo.in2Color[3] = info.I2A;
        } else {
            linfo.flagIn2 = 0;
        }
    } else {
        fprintf(stderr, "-i or -I is necessary\n");
        usage(argv[0]);
    }
    linfo.nResolution = info.nResolution;
    //out = H5Fopen(info.Out, H5F_ACC_TRUNC, H5P_DEFAULT);
    out = H5Fcreate(info.Out, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if(out<0) {
        fprintf(stderr, "Not openend:%s\n", info.Out);
        exit(EXIT_FAILURE);
    }

    switch(info.hdf5mode) {
        case 0: { 
            lmrc2hdf(&out, linfo.in, &linfo, info.mode);
            break;
        }
        case 1: {
            lmrc2hdfimaris(&out, linfo.in, &linfo, info.mode);
            break;
        }
        default: {
            fprintf(stderr, "not supported hdf5mode: %ld\n", info.hdf5mode);
            usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    status = H5Fclose(out);
  
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int
lhdfAttributeString(hid_t gIDChannel, char tag[], char* stmp)
{
    hsize_t sdim;
    hid_t attrspaceID, attrID;
    hid_t stringType;
    herr_t status;

    sdim = strlen(stmp);
    attrspaceID = H5Screate_simple(1, &sdim, NULL);   
    stringType = H5Tcopy(H5T_C_S1);
    status = H5Tset_size(stringType, 1);
    status = H5Tset_strpad(stringType, H5T_STR_NULLTERM);
    DEBUGPRINT3("space: %lld type: %lld status: %d \n", attrspaceID, stringType, status);
    attrID = H5Acreate(gIDChannel, tag, stringType, attrspaceID, H5P_DEFAULT, H5P_DEFAULT);
    DEBUGPRINT1("attrID: %lld\n", attrID);
    status = H5Awrite(attrID, stringType, stmp);
    status = H5Aclose(attrID);
    status = H5Sclose(attrspaceID);

    return status;
}

int
lhdfAttributeUInt32(hid_t gIDChannel, char tag[], uint32_t* i, hsize_t num)
{
    hid_t attrspaceID, attrID;
    herr_t status;

    attrspaceID = H5Screate_simple(1, &num, NULL);
    attrID = H5Acreate(gIDChannel, tag, H5T_STD_U32LE, attrspaceID, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Awrite(attrID, H5T_STD_U32LE, i);
    status = H5Aclose(attrID);
    status = H5Sclose(attrspaceID);

    return status;
}

int
lhdfAttributeInt2String(hid_t gIDChannel, char tag[], hsize_t i)
{
    char stmp[1024];
    hsize_t sdim;
    hid_t attrspaceID, attrID;
    hid_t stringType;
    herr_t status;

    sprintf(stmp, "%lld", i); 
    sdim = strlen(stmp);
    attrspaceID = H5Screate_simple(1, &sdim, NULL);   
    stringType = H5Tcopy(H5T_C_S1);
    status = H5Tset_size(stringType, 1);
    status = H5Tset_strpad(stringType, H5T_STR_NULLTERM);
    DEBUGPRINT3("space: %lld type: %lld status: %d \n", attrspaceID, stringType, status);
    attrID = H5Acreate(gIDChannel, tag, stringType, attrspaceID, H5P_DEFAULT, H5P_DEFAULT);
    DEBUGPRINT1("attrID: %lld\n", attrID);
    status = H5Awrite(attrID, stringType, stmp);
    status = H5Aclose(attrID);
    status = H5Sclose(attrspaceID);

    return status;
}

int
lhdfAttributeReal2String(hid_t gIDChannel, char tag[], double f)
{
    char stmp[1024];
    hsize_t sdim;
    hid_t attrspaceID, attrID;
    hid_t stringType;
    herr_t status;

    sprintf(stmp, "%lf", f); 
    sdim = strlen(stmp);
    attrspaceID = H5Screate_simple(1, &sdim, NULL);   
    stringType = H5Tcopy(H5T_C_S1);
    status = H5Tset_size(stringType, 1);
    status = H5Tset_strpad(stringType, H5T_STR_NULLTERM);
    DEBUGPRINT3("space: %lld type: %lld status: %d \n", attrspaceID, stringType, status);
    attrID = H5Acreate(gIDChannel, tag, stringType, attrspaceID, H5P_DEFAULT, H5P_DEFAULT);
    DEBUGPRINT1("attrID: %lld\n", attrID);
    status = H5Awrite(attrID, stringType, stmp);
    status = H5Aclose(attrID);
    status = H5Sclose(attrspaceID);

    return status;
}

int 
lmrc2hdfimaris(hid_t* out, mrcImage* in, lmrc2hdfInfo* linfo, int mode)
{
    // String for tags
    static hsize_t sdim=1024;
    char tmp[sdim];
    char stmp[sdim];
    // Histogram
    static hsize_t nHist1024=1024;
    static hsize_t nHist=256;
    hsize_t iLevel;
    uint64_t hist1024[nHist1024];
    uint64_t hist[nHist];

    // image
    double data;
    float* image;

    hsize_t dims[4];
    hsize_t chunk[4];

    // for hdf5
    herr_t status;
    hid_t datasetID;
    hid_t datasetID2;
    hid_t dataspaceID; 
    hid_t dataspaceID2; 
    hid_t datasetPropertyID;
    hid_t dset; 
    static uint32_t numOfDataSets = 1; 

    int nGroup=4;
    hid_t groupID[4];
    char* groupName[] = {"/DataSet", "/DataSetInfo", "/DataSetTimes", "/Thumbnail"};
    int val;
    int i, ires, itime, ichannel;
    uint64_t i64;
    int nres, ntime, nchannel;
    hid_t dsetID, dspaceID, gIDRes, gIDTime, gIDChannel, attrID, attrspaceID, stringType; 
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal xorg, yorg, zorg;
    int irange, numrange;
    unsigned char* thumbImage;
    double sum, min, max, mean;
    mrcImage tmpImage;
    mrcImage* tmpIn; 
    lmrcImageProjectionInfo lpro;

    DEBUGPRINT("Start lmrc2hdfimaris\n");
    // Top Level Attribute 
    lhdfAttributeString(*out, "DataSetDirectoryName",       "DataSet");
    lhdfAttributeString(*out, "DataSetInfoDirectoryName",   "DataSetInfo");
    lhdfAttributeString(*out, "ImarisDataSet",              "ImarisDataSet");
    lhdfAttributeString(*out, "ImarisVersion",              "5.5.0");
    lhdfAttributeUInt32(*out, "NumberOfDataSets",           &numOfDataSets, 1);
    lhdfAttributeString(*out, "ThumbnailDirectoryName",     "Thumbnail");

    // Top Level Groups
    for(i=0; i<nGroup; i++) {
        DEBUGPRINT2("Group: %s %d\n", groupName[i], i);
        groupID[i] = H5Gcreate2(*out, groupName[i], H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if(groupID[i]<0) {
            fprintf(stderr, "Not create Group: %s\n", groupName[i]);
            exit(EXIT_FAILURE);
        } else {
            DEBUGPRINT1("Success: %d\n", i);
        }
    }

    // DataSet/.../Data
    dims[0] = in[0].HeaderN.z;
    dims[1] = in[0].HeaderN.y;
    dims[2] = in[0].HeaderN.x;

    /*
    chunk[0] = dims[0];
    chunk[1] = dims[1];
    chunk[2] = dims[2];
    */
    chunk[0] = 32;
    chunk[1] = 64;
    chunk[2] = 64;
    
    datasetPropertyID = H5Pcreate(H5P_DATASET_CREATE);
    status = H5Pset_chunk(datasetPropertyID, 3, chunk);

    val = 3;
    status = H5Pset_fill_value(datasetPropertyID, H5T_NATIVE_INT, &val);
    status = H5Pset_alloc_time(datasetPropertyID, H5D_ALLOC_TIME_EARLY);
    status = H5Pclose(datasetPropertyID);
  
    max = FLT_MIN;
    min = FLT_MAX;
    // DataSet 
    nres = linfo->nResolution;
    ntime = linfo->numFile;
    if(0<linfo->flagIn) {
        nchannel = 1;
    }
    if(0<linfo->flagIn2) {
        nchannel = 2;
        if(in[0].HeaderN.x != linfo->in2[0].HeaderN.x
         ||in[0].HeaderN.y != linfo->in2[0].HeaderN.y
         ||in[0].HeaderN.z != linfo->in2[0].HeaderN.z) {
            fprintf(stderr, "Different Size : In (%d %d %d) and I2 (%d, %d, %d)\n", 
                linfo->in[0].HeaderN.x,  linfo->in[0].HeaderN.y,  linfo->in[0].HeaderN.z, 
                linfo->in2[0].HeaderN.x, linfo->in2[0].HeaderN.y, linfo->in2[0].HeaderN.z);
            exit(EXIT_FAILURE);
        }
    }

    // ResolutionLevel
    for(ires=0; ires<nres; ires++) {
        sprintf(tmp, "%s/%s %d", groupName[0], "ResolutionLevel", ires);
        gIDRes = H5Gcreate2(groupID[0], tmp, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        DEBUGPRINT1("%s\n", tmp);
    for(itime=0; itime<ntime; itime++) {
        sprintf(tmp, "%s/%s %d/%s %d", groupName[0], "ResolutionLevel", ires, "TimePoint", itime);
        gIDTime = H5Gcreate2(gIDRes, tmp, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        DEBUGPRINT1("%s\n", tmp);
    for(ichannel=0; ichannel<nchannel; ichannel++) {
        switch(ichannel) {
            case 0: 
                tmpIn = linfo->in;
                break;
            case 1:
                tmpIn = linfo->in2; 
                break;
            default:
                fprintf(stderr, "Not supported ichannel: %d\n", ichannel);
                exit(EXIT_FAILURE);
                break;
        }
        sprintf(tmp, "%s/%s %d/%s %d/%s %d", groupName[0], "ResolutionLevel", ires, "TimePoint", itime, "Channel", ichannel);
        gIDChannel = H5Gcreate2(gIDTime, tmp, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        DEBUGPRINT1("%s\n", tmp);
        // Channel Attribute
        lhdfAttributeInt2String(gIDChannel, "ImageSizeX", dims[2]);
        lhdfAttributeInt2String(gIDChannel, "ImageSizeY", dims[1]);
        lhdfAttributeInt2String(gIDChannel, "ImageSizeZ", dims[0]);

        // TimePoint
        dspaceID = H5Screate_simple(3, dims, NULL);
        sprintf(tmp, "%s/%s %d/%s %d/%s %d/%s", groupName[0], "ResolutionLevel", ires, "TimePoint", itime, "Channel", ichannel, "Data");
        DEBUGPRINT1("%s\n", tmp);
        DEBUGPRINT1("mode: %d\n", tmpIn[0].HeaderMode);
        image = (float*)memoryAllocate(sizeof(float)*dims[0]*dims[1]*dims[2], "in lmrc2hdfimars");

        for(i=0; i<256; i++) hist[i] = 0;
        for(i=0; i<1024; i++) hist1024[i] = 0;
        // image
        DEBUGPRINT("image\n");
        if(tmpIn[itime].HeaderAMax<=tmpIn[itime].HeaderAMin) {
            fprintf(stderr, "Image data is flat\n");
            for(i=0; i<dims[0]*dims[1]*dims[2]; i++) {
                image[i] = tmpIn[itime].HeaderAMin;
                hist[0]++;
                hist1024[0]++;
            }
        } else {
            irange=1<<ires;
            DEBUGPRINT2("res: %d irange %d\n", ires, irange);
            for(z=0; z<dims[0]; z++) { 
                if(0==(((int)(z/(double)(dims[0]-1)*100))%10)) {
                    DEBUGPRINT2("%d/%llu\n", (int)z, dims[0]);
                }
            for(y=0; y<dims[1]; y++) { 
            for(x=0; x<dims[2]; x++) { 
                i64 = (double)x + (double)y*(double)dims[2] + (double)z*(double)dims[2]*(double)dims[1];            
                if(dims[0]*dims[1]*dims[2]<=i64) {
                    DEBUGPRINT1("%f \n", x + (double)y*(double)dims[2] + (double)z*(double)dims[2]*(double)dims[1]);
                    DEBUGPRINT4("%lld %f %f %f\n", i64, x, y, z);
                    DEBUGPRINT4("%lld %lld %lld %lld\n", dims[0]*dims[1]*dims[2], dims[2], dims[1], dims[0]);
                }
                sum = numrange = 0;
                for(zorg=z*irange;zorg<(z+1)*irange; zorg++) { 
                for(yorg=y*irange;yorg<(y+1)*irange; yorg++) { 
                for(xorg=x*irange;xorg<(x+1)*irange; xorg++) { 
                    numrange++;
                    mrcPixelDataGet(&(tmpIn[itime]), xorg, yorg, zorg, &data, mrcPixelRePart, mrcPixelHowNearest);
                    sum+=data;
                } 
                }
                }
                if(0<numrange) {
                    data = sum/numrange;
#undef DEBUG2
#ifdef DEBUG2
                    if(0<data) {
                        DEBUGPRINT4("%llu %f = %f / %d\n", i64, data, sum, numrange);
                    }
#endif
#undef DEBUG2
                } else {
                    //DEBUGPRINT("numrange is zero: Something wrong\n");
                    data = 0;
                }
                image[i64] = (float)data; 
            } // x
            } // y
            } // z
            
            DEBUGPRINT("MIN/MAX\n");
            min= max = image[0];
            for(i64=1; i64<dims[2]*dims[1]*dims[0]; i64++) {
                if(image[i64]<min) min = image[i64];
                if(max<image[i64]) max = image[i64];
            }
            DEBUGPRINT2("%f/%f\n", min, max);
            DEBUGPRINT("HISTGRAM\n");
            for(i64=1; i64<dims[2]*dims[1]*dims[0]; i64++) {
                data = image[i64];
                iLevel = MAX(0,MIN(1023,(int)((data-min)/(max-min)*1023+0.5)));
                hist1024[iLevel]++;
                iLevel = MAX(0,MIN( 255,(int)((data-min)/(max-min)* 255+0.5))); 
                hist[iLevel]++;
            }
        }
        // Image
        DEBUGPRINT("H5Dcreate");
        dsetID = H5Dcreate(gIDChannel, tmp, H5T_IEEE_F32LE, dspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Dwrite(dsetID, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, image);
        DEBUGPRINT3("%s End: dataset %lld status %d\n", tmp, dsetID, status);
        memoryFree(image);
        status = H5Dclose(dsetID);
        status = H5Sclose(dspaceID);
        // Histogram
        lhdfAttributeInt2String(gIDChannel, "HistogramMax", max);
        lhdfAttributeInt2String(gIDChannel, "HistogramMin", min);
        lhdfAttributeInt2String(gIDChannel, "HistogramMax1024", max);
        lhdfAttributeInt2String(gIDChannel, "HistogramMin1024", min);

        // Histogram  
        dspaceID = H5Screate_simple(1, &nHist, NULL);
        sprintf(tmp, "%s/%s %d/%s %d/%s %d/%s", groupName[0], "ResolutionLevel", ires, "TimePoint", itime, "Channel", ichannel, "Histogram");
        dsetID = H5Dcreate(gIDChannel, tmp, H5T_STD_U64LE, dspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Dwrite(dsetID, H5T_STD_U64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, hist);
        status = H5Dclose(dsetID);
        status = H5Sclose(dspaceID);
        
        // Histogram1024  
        dspaceID = H5Screate_simple(1, &nHist1024, NULL);
        sprintf(tmp, "%s/%s %d/%s %d/%s %d/%s", groupName[0], "ResolutionLevel", ires, "TimePoint", itime, "Channel", ichannel, "Histogram1024");
        dsetID = H5Dcreate(gIDChannel, tmp, H5T_STD_U64LE, dspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Dwrite(dsetID, H5T_STD_U64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, hist1024);
        status = H5Dclose(dsetID);
        status = H5Sclose(dspaceID);

        // Group Close
        status = H5Gclose(gIDChannel);
    }
        status = H5Gclose(gIDTime);
    }
        dims[0]/=2;
        dims[1]/=2;
        dims[2]/=2;
        status = H5Gclose(gIDRes);
    }
    // DataSetInfo
    DEBUGPRINT("DataSetInfo\n");
    {
        char* dsiGroupName[] = {"Channel 0", "Image", "Imaris", "ImarisDataSet", "Log", "TImeInfo"};
        int dsiNGroup = 6;
        hid_t dsiGroupID[dsiNGroup];
        hid_t tmpdsiGroupID;

        for(i=0; i<dsiNGroup; i++) {
            sprintf(stmp, "%s/%s", groupName[1], dsiGroupName[i]);
            dsiGroupID[i] = H5Gcreate2(*out, stmp, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        }
        // Channel 0
        if(linfo->flagIn) {
            lhdfAttributeString(dsiGroupID[0], "Name", "No");
            sprintf(stmp, "%f %f %f", linfo->inColor[0], linfo->inColor[1], linfo->inColor[2]);
            lhdfAttributeString(dsiGroupID[0], "Color", stmp);
            lhdfAttributeString(dsiGroupID[0], "ColorMode", "BaseColor");
            lhdfAttributeReal2String(dsiGroupID[0], "ColorOpacity", linfo->inColor[3]);
            lhdfAttributeReal2String(dsiGroupID[0], "Min", in[0].HeaderAMin);
            lhdfAttributeReal2String(dsiGroupID[0], "Max", in[0].HeaderAMax);
        }
        if(linfo->flagIn2) {
            sprintf(stmp, "%s/%s", groupName[1], "Channel 1");
            tmpdsiGroupID = H5Gcreate2(*out, stmp, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            lhdfAttributeString(tmpdsiGroupID, "Name", "No");
            sprintf(stmp, "%f %f %f", linfo->in2Color[0], linfo->in2Color[1], linfo->in2Color[2]);
            lhdfAttributeString(tmpdsiGroupID, "Color", stmp);
            lhdfAttributeString(tmpdsiGroupID, "ColorMode", "BaseColor");
            lhdfAttributeReal2String(tmpdsiGroupID, "ColorOpacity", linfo->in2Color[3]);
            lhdfAttributeReal2String(tmpdsiGroupID, "Min", linfo->in2[0].HeaderAMin);
            lhdfAttributeReal2String(tmpdsiGroupID, "Max", linfo->in2[0].HeaderAMax);
            status = H5Gclose(tmpdsiGroupID);
        }
        // Image
        lhdfAttributeString(dsiGroupID[1], "Description", "No");
        lhdfAttributeString(dsiGroupID[1], "Name", "No");
        lhdfAttributeInt2String(dsiGroupID[1], "Noc", 1);
        /*
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin0", linfo->in[0].HeaderStartN.x*linfo->in[0].HeaderLength.x);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin1", linfo->in[0].HeaderStartN.y*linfo->in[0].HeaderLength.y);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin2", linfo->in[0].HeaderStartN.z*linfo->in[0].HeaderLength.z);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax0", (linfo->in[0].HeaderStartN.x+linfo->in[0].HeaderN.x-1)*linfo->in[0].HeaderLength.x);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax1", (linfo->in[0].HeaderStartN.y+linfo->in[0].HeaderN.y-1)*linfo->in[0].HeaderLength.y);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax2", (linfo->in[0].HeaderStartN.z+linfo->in[0].HeaderN.z-1)*linfo->in[0].HeaderLength.z);
        */
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin0", 0*linfo->in[0].HeaderLength.x);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin1", 0*linfo->in[0].HeaderLength.y);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMin2", 0*linfo->in[0].HeaderLength.z);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax0", (0+linfo->in[0].HeaderN.x-1)*linfo->in[0].HeaderLength.x);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax1", (0+linfo->in[0].HeaderN.y-1)*linfo->in[0].HeaderLength.y);
        lhdfAttributeReal2String(dsiGroupID[1], "ExtMax2", (0+linfo->in[0].HeaderN.z-1)*linfo->in[0].HeaderLength.z);
        if(1<nres) {
            lhdfAttributeString(dsiGroupID[1], "ResampleDimensionX", "true");
            lhdfAttributeString(dsiGroupID[1], "ResampleDimensionY", "true");
            lhdfAttributeString(dsiGroupID[1], "ResampleDimensionZ", "true");
        }
        lhdfAttributeString(dsiGroupID[1], "Unit", "um");
        lhdfAttributeInt2String(dsiGroupID[1], "X", linfo->in[0].HeaderN.x);
        lhdfAttributeInt2String(dsiGroupID[1], "Y", linfo->in[0].HeaderN.y);
        lhdfAttributeInt2String(dsiGroupID[1], "Z", linfo->in[0].HeaderN.z);
        // Imaris 
        lhdfAttributeString(dsiGroupID[2], "Version", "5,5");
        // ImarisDataSet        
        lhdfAttributeString(dsiGroupID[3], "Creator", "lmrc2hdf5imaris");
        lhdfAttributeString(dsiGroupID[3], "NumberOfImages", "1");
        lhdfAttributeString(dsiGroupID[3], "Version", "1.0");

        for(i=dsiNGroup-1; i>=0; i--) {
            status = H5Gclose(dsiGroupID[i]);
        }

    }
    DEBUGPRINT("DataSetTimes\n");
    DEBUGPRINT("Thumbnail\n");
    // Thumbnail
    {
      hsize_t dimsT[4];
      double zoomx, zoomy;
      hsize_t dimsX, dimsY;
      float orgx, orgy, orgz;
      zoomx = zoomy = 1;
      if(in[0].HeaderN.x<in[0].HeaderN.y) {
          zoomx *= in[0].HeaderN.x/(double)in[0].HeaderN.y;
      } else {
          zoomy *= in[0].HeaderN.y/(double)in[0].HeaderN.x; 
      }
      dimsT[0] = dimsX = ((int)(256*zoomx));
      dimsT[1] = ((int)(256*zoomy))*4; // RGBA
      dimsY = dimsT[1]/4;
      dimsT[2]=dimsT[3]=1;
        DEBUGPRINT2("zoom: %f %f\n", zoomx, zoomy);
        DEBUGPRINT4("dimsT: %llu %llu - %llu %llu\n", dimsT[0], dimsT[1], dimsX, dimsY);
        sprintf(tmp, "%s/%s", groupName[3], "Data");
        thumbImage = (unsigned char*) memoryAllocate(sizeof(unsigned char)*dimsT[0]*dimsT[1], "in imaris");
        lpro.mode = 0;
        lmrcImageProjectionMIP(&tmpImage, &in[0], &lpro); 
        {
#ifdef DEBUG2
            mrcFileWrite(&tmpImage, "/tmp/tmpImage.mrc", "in tet", 0);
#endif
        }
        min = FLT_MAX;
        max = FLT_MIN;
        sum = 0;
        for(x=0; x<in[0].HeaderN.x; x++) {
        for(y=0; y<in[0].HeaderN.y; y++) {
            mrcPixelDataGet(&tmpImage, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
            sum += data;
            if(data<min) min = data;
            if(max<data) max = data;
        }
        }
        mean = sum/in[0].HeaderN.x/in[0].HeaderN.y;

        DEBUGPRINT1("min:  %f\n", min);
        DEBUGPRINT1("max:  %f\n", max);
        DEBUGPRINT1("mean: %f\n", mean);
        for(x=0; x<dimsX; x++) {
        for(y=0; y<dimsY; y++) {
            orgx =  x/(dimsX - 1)*(in[0].HeaderN.x-1);
            orgy =  y/(dimsY - 1)*(in[0].HeaderN.y-1);
            mrcPixelDataGet(&tmpImage, orgx, orgy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
            if(max==min) { 
                thumbImage[(int)(y*4+x*dimsT[1])] = 0;
            } else {
                data = (int)(255.0*(data-(mean - (mean - min)/3))/((mean + (max-mean)/3)  - (mean - (mean-min)/3))+0.5);
                if(data<0) data = 0;
                if(255<data) data = 255;
                thumbImage[(int)(y*4+x*dimsT[1])] = data;
            }
            thumbImage[(int)(y*4+1+x*dimsT[1])] = 0;
            thumbImage[(int)(y*4+2+x*dimsT[1])] = 0;
            thumbImage[(int)(y*4+3+x*dimsT[1])] = 255;
        }
        }

        dspaceID = H5Screate_simple(2, &(dimsT[0]), NULL);  // H5S dimension
        sprintf(tmp, "%s/%s", groupName[3], "Data");        // Group Name
        dsetID = H5Dcreate2(groupID[3], tmp, H5T_STD_U8LE, dspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        status = H5Dwrite(dsetID, H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, thumbImage);  // Write
        mrcImageFree(&tmpImage, "in lmrc2hdfimaris");   

        status = H5Dclose(dsetID);
        status = H5Sclose(dspaceID);
    }

    // H5Gclose
    for(i=nGroup-1; i>=0; i--) {
        status = H5Gclose(groupID[i]);
    }

    return 0;
}
int 
lmrc2hdf(hid_t* out, mrcImage* in, lmrc2hdfInfo* linfo, int mode)
{
    char tmp[1024];
    hsize_t dims[4];
    hsize_t chunk[4];
    herr_t status;
    hid_t datasetID;
    hid_t datasetID2;
    hid_t dataspaceID; 
    hid_t dataspaceID2; 
    hid_t datasetPropertyID;
    hid_t dset; 
    hid_t nGroup=4;
    hid_t groupID[4];
    char* groupName[] = {"/DataSet", "/DataSet/ResolutionLevel 0", "/DataSet/ResolutionLevel 0/TimePoint 0", "/DataSet/ResolutionLevel 0/TimePoint 0/Channel 0"};
    //char* groupName[] = {"/DataSet"};
    int val;
    int i;

    nGroup = 1;
    for(i=0; i<nGroup; i++) {
        DEBUGPRINT1("Group: %s\n", groupName[i]);
        groupID[i] = H5Gcreate2(*out, groupName[i], H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if(groupID[i]<0) {
            fprintf(stderr, "Not create Group: %s\n", groupName[i]);
            exit(EXIT_FAILURE);
        } else {
            DEBUGPRINT("Success\n");
        }
    }

    dims[0] = in->HeaderN.x;
    dims[1] = in->HeaderN.y;
    dims[2] = in->HeaderN.z;
    dims[3] = linfo->numFile;

    chunk[0] = dims[0];
    chunk[1] = dims[1];
    chunk[2] = dims[2];
    chunk[3] = dims[3];

    datasetPropertyID = H5Pcreate(H5P_DATASET_CREATE);
    status = H5Pset_chunk(datasetPropertyID, 4, chunk);

    val = 4;
    status = H5Pset_fill_value(datasetPropertyID, H5T_NATIVE_INT, &val);
    status = H5Pset_alloc_time(datasetPropertyID, H5D_ALLOC_TIME_EARLY);
    
    dataspaceID2 = H5Screate_simple(4, dims, NULL);
    //datasetID2 = H5Dcreate(*out, "/prop", H5T_STD_I32LE, dataspaceID2, H5P_DEFAULT, datasetPropertyID, H5P_DEFAULT);
    i=0;
    sprintf(tmp, "%s/%s", groupName[i], "Data");
    datasetID2 = H5Dcreate2(groupID[i], tmp, H5T_STD_I32LE, dataspaceID2, H5P_DEFAULT, datasetPropertyID, H5P_DEFAULT);
    status = H5Pclose(datasetPropertyID);
    status = H5Dclose(datasetID2);
    status = H5Sclose(dataspaceID2);
    

    dataspaceID = H5Screate_simple(4, dims, NULL);
    switch(in->HeaderMode) {
        case mrcCharImage:
            datasetID = H5Dcreate(*out, "/mrc", H5T_STD_U8LE, dataspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            status = H5Dwrite(datasetID, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, in->Image);
            break;
        case mrcShortImage:
            datasetID = H5Dcreate(*out, "/mrc", H5T_STD_I16LE, dataspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            status = H5Dwrite(datasetID, H5T_NATIVE_SHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, in->Image);
            break;
        case mrcUShortImage:
            datasetID = H5Dcreate(*out, "/mrc", H5T_STD_U16LE, dataspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            status = H5Dwrite(datasetID, H5T_NATIVE_USHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, in->Image);
            break;
        case mrcFloatImage:
            datasetID = H5Dcreate(*out, "/mrc", H5T_IEEE_F32LE, dataspaceID, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
            status = H5Dwrite(datasetID, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, in->Image);
            break;
        default:
            fprintf(stderr, "Not supported: %d\n", in->HeaderMode);
            exit(EXIT_FAILURE);
            break;
    }            

    status = H5Dclose(datasetID);
    status = H5Sclose(dataspaceID);

    for(i=nGroup-1; i>=0; i--) {
        status = H5Gclose(groupID[i]);
    }

    return 0;
}
