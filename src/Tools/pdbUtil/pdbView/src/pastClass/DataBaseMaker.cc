#include "./DataBaseMaker.hh"
#include "./DataBase.hh"

DataBaseMaker::DataBaseMaker(FILE* TabFile, pdbFile* pdb)
{
  strcpy(TabFileName,"pdbText.dat");
  TabFile = fopen(TabFileName,"w");
  pdbFileTableWrite(TabFile,pdb);
  fclose(TabFile);
  InputToDataBase(TabFile);
}

DataBaseMaker::DataBaseMaker(FILE* TabFile)
{
  /*
  strcpy(host,"pc17");
  strcpy(port,"7777");
  strcpy(dbName,"test");
  */
  InputToDataBase(TabFile);
}


void DataBaseMaker::InputToDataBase(FILE* TabFile)
{

  char* tmp0 = strdup("pc17");
  char* tmp1 = strdup("7777");
  char* tmp2 = strdup("test");

  DataBase::SetDataBaseInfo(tmp0,tmp1,tmp2);

   char sql[256]; 


  char TableName[20] = "TempPDB";
  strcpy(TabFileName,"pdbText.dat");

  char createTable[500];


  sprintf(createTable, "CREATE TABLE %s ( Atom TEXT,AtomSerialNumber INTEGER,AtomName TEXT,LocationIndicator TEXT,ResidueName TEXT,ChainIdentifier TEXT,ResidueSequenceNumber INTEGER,InsertionCode TEXT,X FLOAT,Y FLOAT,Z FLOAT,Occupancy TEXT,TemperatureFactor TEXT,FootnoteNumber INTEGER,Footnote TEXT) " , TableName);

  res = PQexec(con,createTable);

  /*

    res = PQexec(con, "CREATE TABLE testpdb(
                       Atom TEXT,
                       AtomSerialNumber INTEGER,
                       AtomName TEXT,
                       LocationIndicator TEXT,
                       ResidueName TEXT,
                       ChainIdentifier TEXT,
                       ResidueSequenceNumber INTEGER,
                       InsertionCode TEXT,
                       X FLOAT,
                       Y FLOAT,
                       Z FLOAT,
                       Occupancy TEXT,
                       TemperatureFactor TEXT,
                       FootnoteNumber INTEGER,
                       Footnote TEXT) ");

  */

    //TESTPDB->MOJIRETU NI HENKAN SURUKOTO!!!

  char tmp[100];
  sprintf(tmp, "copy %s from stdin", TableName);
  res = PQexec(con, tmp);

  //res = PQexec(con, "copy testpdb from stdin");
  if (PQresultStatus(res) != PGRES_COPY_IN){
    fprintf(stderr, "%s", PQerrorMessage(con));
    exit(1);
  }

  //PQclear(res);

  if((TabFile = fopen (TabFileName,"r")) == NULL){
    fprintf(stderr,"Can't open the file!\n");
    exit(1);
  }

  while ( (fgets(sql,256,TabFile) ) != NULL){
    //printf("%s\n",sql);
      if ( PQputline(con,sql) ){
        fprintf(stderr, "PQputline failed\n");
        exit(1);
      }
    }

  if (PQputline(con,"\\.\n")){
    fprintf(stderr,"very Last PQputline failed");
    exit(1);
  }


  if (PQendcopy(con)){
    fprintf(stderr, "PQendcopy failed\n");
    exit(1);
  }
  fclose(TabFile);

  res = PQexec(con, "SELECT * FROM testpdb WHERE atomserialnumber < 15");

  for(int i = 0; i < PQntuples(res) ; i++){
    for(int j = 0; j < PQnfields(res) ; j++){
      printf("%s\t", PQgetvalue(res, i, j));
    }
    printf("\n");
  }


  PQclear(res);

  //DataBase::DeleteTable(TableName);

  //DataBase::DropTable(TableName);
  //DataBase::CloseDataBase();

}

