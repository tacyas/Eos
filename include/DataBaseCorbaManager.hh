#ifndef DATABASECORBA_MANAGER_HH
#define DATABASECORBA_MANAGER_HH

#include "CORBA.h"
#include "DataBaseCorba.h"
#include "DataBaseCorbaImpl.hh"
#include "DataBaseCorbaBank.hh"

class DataBaseCorbaManager : public virtual POA_PortableServer::ServantActivator
{
public:
 PortableServer::Servant incarnate (const PortableServer::ObjectId &,PortableServer::POA_ptr);
 void etherealize (const PortableServer::ObjectId &, PortableServer::POA_ptr, PortableServer::Servant, CORBA::Boolean,CORBA::Boolean);

};

#endif /* DATABASECORBA_MANAGER_HH */
