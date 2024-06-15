#include "./HomologyStore.hh"
#include "./FunctionMode.hh"

#include "./DataBase.hh"
#include <libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

#include "ActorMaker.hh"

HomologyStore::HomologyStore(Property* p)
{
  Prop = p;
  DataBase::SetDataBaseInfo(Prop->GetHostName(),Prop->GetPortName(),Prop->GetdbName());
}

/*
HomologyStore::HomologyStore(char* host, char* port, char* dbName)
{
  DataBase::SetDataBaseInfo(host, port, dbName);
}

*/



void HomologyStore::SetKey(int ResNum,char* ResName, vtkActor* actor)
{  
  char* sql;
  sql = (char*)memoryAllocate(sizeof(char)*200, "Homology::SetKey");
  
  double per;
  
  printf("Selected---Amino:%s  ResNumber:%d  PdbCode:%s\n",ResName,ResNum,Prop->GetPdbCode());
  
  switch(Prop->GetHomologyMode()){
  case AllData:
    printf("HomologyMode...AllData\n");
    sprintf(sql, "SELECT pdbcode,r%d FROM %s",ResNum,Prop->GetHomoTableName());
    res = PQexec(con, sql);
    printf("pdbcode\tResNum\t\n");
    DataBase::DisplayAll(res);
    break;
    
  case Percentage:
    per = GetPercent(ResNum,ResName);
    break;
    
  case EachData:

    printf("Amino\tcount\n");
    sprintf(sql,"SELECT r%d,COUNT(*) FROM %s GROUP BY r%d",
    	    ResNum,Prop->GetHomoTableName(),ResNum);
    res = PQexec(con, sql);
    DataBase::DisplayAll(res);
    break;

  case ChangeColor:
    per = GetPercent(ResNum,ResName);
    
    ActorMaker* actorMaker;
    actorMaker = new ActorMaker();
    actorMaker->SetActor(actor);
    actorMaker->SetHomoColor(per/100);
    delete actorMaker;
    
    break;
    
    
  }
  
}



double HomologyStore::GetPercent(int ResNum, char* ResName)
{
  double per;
  char* sql;
  sql = (char*)memoryAllocate(sizeof(char)*200, "Homology::SetKey");
  printf("%d---%s\n",ResNum,ResName);

  if(ResNum!=0 && ResName!=NULL){
    sprintf(sql,"SELECT COUNT(*) FROM %s WHERE r%d ='%s'",
	    Prop->GetHomoTableName(),ResNum,ResName);
    res = PQexec(con, sql);
    int top;
    top = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
    
    PQclear(res);
    
    sprintf(sql,"SELECT COUNT(r%d) FROM %s",ResNum,Prop->GetHomoTableName());
    res = PQexec(con, sql);
    int low;
    low = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
    
    per = (double)top/(double)low*100;
    
    printf("%s --- %d / %d = percent:%f\n",ResName,top,low,per);
  }else{
    printf("Error! ResidueNumber=0 or ResidueName = NULL!!\n");
    per = 0;
  }
  return per;
}


/*
void HomologyStore::ChangeColor(int ResNum, char* ResName, DataStore* dataStore)
{
  int top;
  int low;
  double perMax;
  double perMin;

  int i;

  char* sql;
  sql = (char*)memoryAllocate(sizeof(char)*200, "Homology::SetKey");
  
  printf("Here!!");
  
  sprintf(sql,"SELECT COUNT(*) FROM %s WHERE r%d ='%s' GROUP BY r%d",
	  Prop->GetHomoTableName(),i,ResName,i);
  res = PQexec(con, sql);
  top = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
  
  PQclear(res);
  
  sprintf(sql,"SELECT COUNT(r%d) FROM %s",i,Prop->GetHomoTableName());
  res = PQexec(con, sql);
  low = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
  
  per[i] = (double)top/(double)low*100;
  if(per[i]>perMax)
    {perMax = per[i];}
  if(per[i]<perMin)
    {perMin = per[i];}
  sprintf(sql,"SELECT * FROM %s",Prop->GetHomoTableName());
  res = PQexec(con, sql);
  int Max = PQnfields(res);

  double per[1000];

  printf("Here!!");

  //double* per;
  //per = new double*[Max];

  for(i = 1; i <= Max ;i++){
  printf("Loop!");
    sprintf(sql,"SELECT COUNT(*) FROM %s WHERE r%d ='%s' GROUP BY r%d",
	    Prop->GetHomoTableName(),i,ResName,i);
    res = PQexec(con, sql);
    top = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
    
    PQclear(res);
    
    sprintf(sql,"SELECT COUNT(r%d) FROM %s",i,Prop->GetHomoTableName());
    res = PQexec(con, sql);
    low = atoi(PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1));
    
    per[i] = (double)top/(double)low*100;
    if(per[i]>perMax)
      {perMax = per[i];}
    if(per[i]<perMin)
      {perMin = per[i];}

    printf("%s --- %d / %d = percent:%f\n",ResName,top,low,per);
  }
  
  
  ActorMaker* actorMaker;
  actorMaker = new ActorMaker();

  i = 1;
  int j = 1;
  
  while( j < dataStore->GetAllNumber()){
    if(dataStore->GetPdb(j)->ResidueSequenceNumber == i){
      actorMaker->SetActor(dataStore->GetActor(j));
      actorMaker->SetHomoColor(per[i]);
      j = j + 1;
    }else{
      i = i + 1;
    }
  }
  delete actorMaker;

}
*/
