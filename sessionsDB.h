
#ifndef SESSIONSDB_H
#define SESSIONSDB_H
#include "constants.h"

class MenuManager;
class RecordDB;
class Session;
class GameSessionDB;

using namespace std;

class SessionDB
{
public:
   SessionDB();
   Session* makeSession(int);
   bool removeSession(int);

   Session* getSession(int);
   void close(Session* session);

private:
   MenuManager* menuManager;
   RecordDB* recordDB;
   GameSessionDB* gameSessionDB;
   unordered_map<int, void*> sessionMap;
   int sessionCounter;
};

#endif