#ifndef DATABASECORBABANK_IMPL_HH
#define DATABASECORBABANK_IMPL_HH
#include "DataBaseCorba.h"
#include "CORBA.h"
#include "DataBaseCorbaImpl.hh"

class Bank_impl : virtual public POA_Bank,public DataBase
{
public:
// Bank_impl (PortableServer::POA_ptr);
 DataBaseCorba_ptr create ();
	void ConnectDatabase(char* host, char* port, char* database);
private:
 PortableServer::POA_var mypoa;
};


#endif /* DATABASECORBABANK_IMPL_HH */ 
