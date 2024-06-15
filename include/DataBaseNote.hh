#ifndef DATABASE_NOTE_HH
#define DATABASE_NOTE_HH

#include "DataBase.hh"
#include "Property.hh"

class DataBaseNote : public DataBase{
private:
  Property* Prop;

public:
  DataBaseNote(Property* p);
  void SetKey(char* AtomName, char* ResName , int ResNum);
};

#endif /* DATABASE_NOTE_HH */
