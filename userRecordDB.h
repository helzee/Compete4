
#ifndef RECORDSDB_H
#define RECORDSDB_H
#include "constants.h"
#include <string>
#include <pthread.h>
using namespace std;

class Record;



class RecordDB
{
public:
   RecordDB();
   Record* makeRecord(string, int);

   bool deleteRecord(string);

   Record* getRecord(string, string);

   bool checkIfRecord(string);

   unsigned int turnToInt(string password);
   Record* makeRecord(string username, string password);

private:
   unordered_map<string, void*> recordMap;
   int encrypt(string password);
   pthread_rwlock_t rwLock;
};

#endif