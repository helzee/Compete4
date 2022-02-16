#include "userRecordDB.h"

unordered_map<string, void*> recordMap;

Record* makeRecord(string username, string encryptedPassword)
{
   if (recordMap.find(username) != recordMap.end())
      return nullptr;

   Record* newRecord = new Record(username, encryptedPassword);
   recordMap.insert({username, newRecord});
   return newRecord;
}

bool deleteRecord(string username) { return recordMap.erase(username) == 1; }

Record* getRecord(string username, string encryptedPassword)
{
   auto recordHolder = recordMap.find(username);
   if (recordHolder == recordMap.end())
      return nullptr;

   Record* record = (Record*)recordHolder->second;
   if (record->checkPassword(encryptedPassword))
      return record;
   else
      return nullptr;
}

bool checkIfRecord(string username)
{
   return recordMap.find(username) != recordMap.end();
}