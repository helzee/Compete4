#include "userRecordDB.h"
#include "userRecord.h"
#include "openssl/sha.h"


RecordDB::RecordDB() {}

// Uses basic Rabin Function
int RecordDB::encrypt(string password)
{
   // Cast the password into an unsigned int
   // Then turn it into a long unsigned int, therefore making upper-half empty
   auto number = (long unsigned int)turnToInt(password);

   // Square the number
   number = number * number;
   return (int)(number % HASH_NUMBER);
}

unsigned int RecordDB::turnToInt(string password)
{
   unsigned int toReturn = 0;
   unsigned int toXOR;
   unsigned short int letter;

   for (int i = 0; i < password.length(); i++) {
      letter = (unsigned short int)password[i];

      // toXOR = (letter^2 + letter)^2 + letter
      // toXOR will be at most 32 bits long: an unsigned int
      toXOR = letter + letter * letter;
      toXOR = toXOR * toXOR + letter;

      // toReturn = (toReturn * 2) XOR toXOR
      toReturn *= 2;
      toReturn = toReturn ^ toXOR;
   }

   return toReturn;
}

Record* RecordDB::makeRecord(string username, string password) {
   return makeRecord(username, encrypt(password));
}

Record* RecordDB::makeRecord(string username, int encryptedPassword)
{
   if (recordMap.find(username) != recordMap.end())
      return nullptr;

   Record* newRecord = new Record(username, encryptedPassword);
   recordMap.insert({username, newRecord});
   return newRecord;
   return nullptr;
}

bool RecordDB::deleteRecord(string username) { 
   return recordMap.erase(username) == 1;
   return true;
}

Record* RecordDB::getRecord(string username, string password)
{
   int encryptedPassword = encrypt(password);
   auto recordHolder = recordMap.find(username);
   if (recordHolder == recordMap.end())
      return nullptr;

   Record* record = (Record*)recordHolder->second;
   if (record->checkPassword(encryptedPassword))
      return record;
   else
      return nullptr;

  
   return nullptr;
}

bool RecordDB::checkIfRecord(string username)
{
   return recordMap.find(username) != recordMap.end();
   return true;
}