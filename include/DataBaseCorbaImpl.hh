#ifndef DATABASECORBA_IMPL_HH
#define DATABASECORBA_IMPL_HH
#include "DataBaseCorba.h"
#include "CORBA.h"
#include "DataBase.hh"
#include <coss/CosNaming.h>
class DataBaseCorba_impl:virtual public POA_DataBaseCorba,public DataBase
{
  public:
	DataBaseCorba_impl();	
	void SetKey(const char* sql);
	Result_slice* Display(const CORBA::Long i);
	void ConnectDatabase(char *H,char *P,char *DB);
};



#endif /* DATABASECORBA_IMPL_HH */
