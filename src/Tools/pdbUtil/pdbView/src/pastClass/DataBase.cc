#include "./DataBase.hh"


DataBase::DataBase()
{

}


void DataBase::ConnectToDataBase()
{

  con = PQsetdb(host, port, NULL, NULL, dbName);
  printf("DataBaseName = %s", PQdb(con));
    
  if (PQstatus(con) == CONNECTION_BAD) {
    fprintf(stderr, "Connection to database '%s' on %s failed.\n", dbName, host)
      ;
    fprintf(stderr, "%s", PQerrorMessage(con));
    exit(1);
  }else{
    printf("Connect to DataBase!!\n");
  }

}

void DataBase::DisplayAll(PGresult *res)
{
  int i;
  int j;
  for(i = 0 ; i < PQntuples(res); i++)
    {
      for(j = 0; j < PQnfields(res) ; j++)
	{
	  printf("%s\t",PQgetvalue(res, i, j));
	}
      printf("\n");
    }
}



void DataBase::SetDataBaseInfo(char* hostN, char* portN, char* dbN)
{

  host = strdup(hostN);
  port = strdup(portN);
  dbName = strdup(dbN);

  ConnectToDataBase();
}

void DataBase::DropTable(char* TableName)
{
  char dropMemo[100];
  sprintf(dropMemo, "DROP TABLE %s", TableName);
  res = PQexec(con, dropMemo);
  PQclear(res);
}

void DataBase::DeleteTable(char* TableName)
{
  char deleteMemo[100];
  sprintf(deleteMemo, "DELETE FROM %s", TableName);
  res = PQexec(con, deleteMemo);
  PQclear(res);
}

void DataBase::CloseDataBase()
{
  PQclear(res);
  PQfinish(con);
}

