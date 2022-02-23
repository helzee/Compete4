
#ifndef SESSIONSDB_H
#define SESSIONSDB_H
#include "constants.h"

class MenuManager;
class RecordDB;
class Session;

using namespace std;

class SessionDB
{
public:
   SessionDB(const MenuManager*, RecordDB*);
   Session* makeSession(int);
   bool removeSession(int);

   Session* getSession(int);

private:
   const MenuManager* menuManager;
   RecordDB* recordDB;
   unordered_map<int, void*> sessionMap;
   int sessionCounter;
};

#endif