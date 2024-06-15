#include "./HomologyStore.hh"
#include "./FunctionMode.hh"

#include "./DataBase.hh"
#include <pgsql/libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

HomologyStore::HomologyStore()
{
  char* tmp0 = strdup("pc17");
  char* tmp1 = strdup("7777");
  char* tmp2 = strdup("test");
  DataBase::SetDataBaseInfo(tmp0, tmp1, tmp2);
}

void HomologyStore::SetKey(int ResNum,char* ResName, char* PdbCode, HomologyMode Mode)
{

  char TableName[] = "memo";
  
  char* sql;
  sql = (char*)memoryAllocate(sizeof(char)*200, "Homology::SetKey");
  char* Retu;
  Retu = (char*)memoryAllocate(sizeof(char)*100, "Homology::SetKey");
  sprintf(Retu,"r%d",ResNum);

  printf("Selected---Amino:%s  ResNumber:%d  PdbCode:%s\n",ResName,ResNum,PdbCode);
  
  switch(Mode){
  case AllData:
    printf("HomologyMode...AllData\n");
    sprintf(sql, "SELECT pdbcode,r%d FROM %s",ResNum,TableName);
    res = PQexec(con, sql);
    printf("pdbcode\tResNum\t\n");
    DataBase::DisplayAll(res);
    break;
    
    
  case Percentage:
    sprintf(sql,"SELECT COUNT(*) FROM %s WHERE %s ='%s' GROUP BY %s",
	    TableName,Retu,ResName,Retu);
    res = PQexec(con, sql);
    int top;
    top = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));

    PQclear(res);
    
    sprintf(sql,"SELECT COUNT(%s) FROM %s",Retu,TableName);
    res = PQexec(con, sql);
    int low;
    low = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
    
    double per;
    per = (double)top/(double)low*100;
    
    printf("%s --- %d / %d = percent:%f\n",ResName,top,low,per);
    break;
    
    
    
  case EachData:

    printf("Amino\tcount\n");
    sprintf(sql,"SELECT %s,COUNT(*) FROM %s GROUP BY %s",
    	    Retu,TableName,Retu);
    res = PQexec(con, sql);
    DataBase::DisplayAll(res);
    break;
        
  case Color:
    break;
    
    
  }
  
}
