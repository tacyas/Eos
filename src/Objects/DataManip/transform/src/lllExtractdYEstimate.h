#ifndef LLL_EXTRACT_DY_ESTIMATE_INFO_H
#define LLL_EXTRACT_DY_ESTIMATE_INFO_H

/* struct begin */
typedef struct lllExtractdYEstimateInfo{
	float truePitch;
	float deltadY;
	float mag;
	float PixelSize;
} lllExtractdYEstimateInfo;
/* struct end */

/* prototype begin */
extern int lllExtractdYEstimate(mrcImage* in, lllExtractdYEstimateInfo* dYinfo);
/* prototype end */

#endif /* LLL_EXTRACT_DY_ESTIMATE_INFO_H */
