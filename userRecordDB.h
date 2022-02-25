
#ifndef RECORDSDB_H
#define RECORDSDB_H
#include "constants.h"
#include <pthread.h>
#include <string>
using namespace std;

class Record;

#define RECORDFILE "data/records.dat"

class RecordDB
{
public:
   RecordDB();
   Record* makeRecord(string, int);
   int getRecordFromDisk();
   int saveRecordToDisk();
   bool deleteRecord(string);

   Record* getRecord(string, string);

   bool checkIfRecord(string);

   unsigned int turnToInt(string password);
   Record* makeRecord(string username, string password);

private:
   unordered_map<string, void*> recordMap;
   int encrypt(string password);

   // lock for record map
   pthread_rwlock_t rwLock;

   // lock for record map file
   pthread_rwlock_t fileLock;

   // to prevent deadlock(when writing/read file): file is always locked first,
   // then map is locked within file lock
};

#endif