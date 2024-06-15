#include "./DataBase.hh"
#include "./DataBaseNote.hh"
#include <pgsql/libpq-fe.h>
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

DataBaseNote::DataBaseNote()
{
  char* tmp0 = strdup("pc17");
  char* tmp1 = strdup("7777");
  char* tmp2 = strdup("test");
  DataBase::SetDataBaseInfo(tmp0, tmp1, tmp2);
}

void DataBaseNote::SetKey(char* AtomName, char* ResName , int ResNum)
{
  
  char TableName[] = "note";
  char* sql;
  sql = (char*)memoryAllocate(sizeof(char)*300, "Homology::SetKey");
  char* memo;
  memo = (char*)memoryAllocate(sizeof(char)*300, "Homology::SetKey");
  
  sprintf(sql, "SELECT key FROM %s WHERE atomname ~ '%s' and resname ~ '%s' and resnum = %d",
  	  TableName,AtomName,ResName,ResNum);
  res = PQexec(con, sql);
  
    if((PQgetvalue(res,PQntuples(res)-1 , PQnfields(res)-1))==NULL){
      //Create
      
      PQclear(res);
      printf("Please Write Your Memo!!\n");
      scanf("%s",memo);
      sprintf(sql, "INSERT INTO %s VALUES('%s','%s',%d,'NOW','%s',1)",
	      TableName,AtomName,ResName,ResNum,memo);
      res = PQexec(con, sql);
      PQclear(res);

    }else{

      sprintf(sql, "SELECT atomname,resname,resnum,date,memo FROM %s WHERE atomname ~ '%s' and resname ~ '%s' and resnum = %d",TableName,AtomName,ResName,ResNum);
      
      res = PQexec(con, sql);    
      printf("Atom\tResNeme\tResNum\twrittenDate\tmemo\n");
      DataBase::DisplayAll(res);
      PQclear(res);
    }
}
