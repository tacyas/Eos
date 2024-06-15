#ifndef DATA_BASE_HH
#define DATA_BASE_HH

#include <pgsql/libpq-fe.h>
#include <pgsql/postgres_ext.h>

class DataBase{
protected:
  PGconn *con;
  PGresult *res;
  char* host;
  char* port;
  char* dbName;
public:

  DataBase();
  void ConnectToDataBase();
  void SetDataBaseInfo(char* hostN, char* portN, char* dbN);
  void DisplayAll(PGresult *res);
  void DropTable(char* TableName);
  void DeleteTable(char* TableName);
  void CloseDataBase();
  void Exec(char* sql);
  void ResClear();

};






#endif /* DATA_BASE_HH */
