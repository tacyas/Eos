#ifndef DATABASE_NOTE_HH
#define DATABASE_NOTE_HH

#include "DataBase.hh"

class DataBaseNote : public DataBase{
private:

public:
  DataBaseNote();
  void SetKey(char* AtomName, char* ResName , int ResNum);
};

#endif /* DATABASE_NOTE_HH */
