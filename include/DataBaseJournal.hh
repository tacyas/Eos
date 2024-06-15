#ifndef DATABASE_JOURNAL_HH
#define DATABASE_JOURNAL_HH

class DataBaseJournal : public DataBase{
private:
	DataBase* index;
	
public:
 DataBaseJournal(char* H,char* P);
 void SetKey(char* PDBcord,char* Residues);
};

#endif /* DATABASE_JOURNAL_HH */ 
