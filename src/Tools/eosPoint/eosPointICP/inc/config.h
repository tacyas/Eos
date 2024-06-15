#ifndef CONFIG_H
#define CONFIG_H

#include "eosPointICP.h"
#include "genUtil.h"
#include "eosString.h"
#include "eosPoint.h"
#include "Matrix3D.h"
#include "Random.h"

typedef struct eosPointIcpResult{
    eosPoint resultP;
    Matrix3D matrix;
    double score;
}eosPointIcpResult;

#endif /* CONFIG_H */
