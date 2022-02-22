
#ifndef RECORDSDB_H
#define RECORDSDB_H
#include "constants.h"
#include <string>
using namespace std;

class Record;

class RecordDB
{
public:
   static Record* makeRecord(string, int);

   static bool deleteRecord(string);

   static Record* getRecord(string, string);

   static bool checkIfRecord(string);

   static unsigned int turnToInt(string password);

private:
   static unordered_map<string, void*> recordMap;
   static int encrypt(string password);
};



#endif