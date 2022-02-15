#include "userRecordDB.h"

unordered_map<string, void*> recordMap;

Record* makeRecord(string username)
{
   if (recordMap.find(username) != recordMap.end())
      return nullptr;

   Record* newRecord = new Record(username);
   recordMap.insert({username, newRecord});
   return newRecord;
}

bool deleteRecord(string username) { return recordMap.erase(username) == 1; }

Record* getRecord(string username)
{
   auto record = recordMap.find(username);
   if (record == recordMap.end())
      return nullptr;
   return (Record*)record->second;
}