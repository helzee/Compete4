
#ifndef RECORDSDB_H
#define RECORDSDB_H
#include "constants.h"
#include <string>
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

private:
   unordered_map<string, void*> recordMap;
   int encrypt(string password);
};



#endif