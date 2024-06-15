/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2003 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __DATABASECORBA_H__
#define __DATABASECORBA_H__




class DataBaseCorba;
typedef DataBaseCorba *DataBaseCorba_ptr;
typedef DataBaseCorba_ptr DataBaseCorbaRef;
typedef ObjVar< DataBaseCorba > DataBaseCorba_var;
typedef ObjOut< DataBaseCorba > DataBaseCorba_out;



typedef CORBA::String_var Result[ 10 ][ 100 ];
typedef CORBA::String_var Result_slice[ 100 ];
typedef ArrayVarVar< CORBA::String_var,Result_slice,Result,1000 > Result_var;
typedef ArrayVarOut < CORBA::String_var,Result_slice,Result,1000 > Result_out;
enum _dummy_Result { _dummy_Result_0 };
typedef ArrayVarForAny < CORBA::String_var,Result_slice,Result,1000,_dummy_Result> Result_forany;
#undef MICO_ARRAY_ARG
#define MICO_ARRAY_ARG CORBA::String_var
DECLARE_ARRAY_ALLOC(Result,MICO_ARRAY_ARG,Result_slice,1000)
DECLARE_ARRAY_DUP(Result,MICO_ARRAY_ARG,Result_slice,1000)
DECLARE_ARRAY_FREE(Result,MICO_ARRAY_ARG,Result_slice,1000)
DECLARE_ARRAY_COPY(Result,MICO_ARRAY_ARG,Result_slice,1000)

/*
 * Base class and common definitions for interface DataBaseCorba
 */

class DataBaseCorba : 
  virtual public CORBA::Object
{
  public:
    virtual ~DataBaseCorba();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef DataBaseCorba_ptr _ptr_type;
    typedef DataBaseCorba_var _var_type;
    #endif

    static DataBaseCorba_ptr _narrow( CORBA::Object_ptr obj );
    static DataBaseCorba_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static DataBaseCorba_ptr _duplicate( DataBaseCorba_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static DataBaseCorba_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

    virtual void SetKey( const char* sql ) = 0;
    virtual ::Result_slice* Display( CORBA::Long i ) = 0;

  protected:
    DataBaseCorba() {};
  private:
    DataBaseCorba( const DataBaseCorba& );
    void operator=( const DataBaseCorba& );
};

// Stub for interface DataBaseCorba
class DataBaseCorba_stub:
  virtual public DataBaseCorba
{
  public:
    virtual ~DataBaseCorba_stub();
    void SetKey( const char* sql );
    ::Result_slice* Display( CORBA::Long i );

  private:
    void operator=( const DataBaseCorba_stub& );
};

#ifndef MICO_CONF_NO_POA

class DataBaseCorba_stub_clp :
  virtual public DataBaseCorba_stub,
  virtual public PortableServer::StubBase
{
  public:
    DataBaseCorba_stub_clp (PortableServer::POA_ptr, CORBA::Object_ptr);
    virtual ~DataBaseCorba_stub_clp ();
    void SetKey( const char* sql );
    ::Result_slice* Display( CORBA::Long i );

  protected:
    DataBaseCorba_stub_clp ();
  private:
    void operator=( const DataBaseCorba_stub_clp & );
};

#endif // MICO_CONF_NO_POA

#ifndef MICO_CONF_NO_POA

class POA_DataBaseCorba : virtual public PortableServer::StaticImplementation
{
  public:
    virtual ~POA_DataBaseCorba ();
    DataBaseCorba_ptr _this ();
    bool dispatch (CORBA::StaticServerRequest_ptr);
    virtual void invoke (CORBA::StaticServerRequest_ptr);
    virtual CORBA::Boolean _is_a (const char *);
    virtual CORBA::InterfaceDef_ptr _get_interface ();
    virtual CORBA::RepositoryId _primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr);

    virtual void * _narrow_helper (const char *);
    static POA_DataBaseCorba * _narrow (PortableServer::Servant);
    virtual CORBA::Object_ptr _make_stub (PortableServer::POA_ptr, CORBA::Object_ptr);

    virtual void SetKey( const char* sql ) = 0;
    virtual ::Result_slice* Display( CORBA::Long i ) = 0;

  protected:
    POA_DataBaseCorba () {};

  private:
    POA_DataBaseCorba (const POA_DataBaseCorba &);
    void operator= (const POA_DataBaseCorba &);
};

#endif // MICO_CONF_NO_POA

extern CORBA::StaticTypeInfo *_marshaller_DataBaseCorba;

extern CORBA::StaticTypeInfo *_marshaller__a10__a100_string;

extern CORBA::StaticTypeInfo *_marshaller__a100_string;

#endif
