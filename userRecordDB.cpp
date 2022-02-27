#include "userRecordDB.h"
#include "openssl/sha.h"
#include "userRecord.h"
#include <filesystem>
#include <fstream>
#include <pthread.h>
#include <sstream>

RecordDB::RecordDB()
{
   pthread_rwlock_init(&rwLock, NULL);
   pthread_rwlock_init(&fileLock, NULL);
   getRecordFromDisk();
}

int RecordDB::saveRecordToDisk()
{
   // to prevent deadlock: file is always locked first, then map is locked
   // within file lock
   // lock file write first
   pthread_rwlock_wrlock(&fileLock);
   ofstream file(RECORDFILE);
   // lock map read second
   pthread_rwlock_rdlock(&rwLock);
   for (auto it = recordMap.begin(); it != recordMap.end(); it++) {
      Record* rec = (Record*)it->second;
      rec->toFile(file);
   }
   // unlock map first
   pthread_rwlock_unlock(&rwLock);
   file.close();
   // then unlock file
   pthread_rwlock_unlock(&fileLock);

   return 0;
}

int RecordDB::getRecordFromDisk()
{
   // file read lock
   pthread_rwlock_rdlock(&fileLock);
   ifstream file(RECORDFILE);
   string line;

   while (file) {
      getline(file, line);
      if (line.empty()) {
         pthread_rwlock_unlock(&fileLock);
         return 0;
      }
      stringstream lineStream(line);

      Record* rec = new Record(lineStream);

      // record map write lock
      pthread_rwlock_wrlock(&rwLock);
      recordMap.insert({rec->getName(), (void*)rec});
      pthread_rwlock_unlock(&rwLock);
   }
   file.close();
   pthread_rwlock_unlock(&fileLock);

   return 0;
}

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

/**
 * @brief calls the original makeRecord() function, but allows the caller
 * to use the unencrypted password for calling. This function then encrypts the
 * password and calls the actual makeRecord() function
 *
 * @param username
 * @param password
 * @return Record* the record that was made or nullptr if it already exists or
 * an error occured
 */
Record* RecordDB::makeRecord(string username, string password)
{
   return makeRecord(username, encrypt(password));
}

/**
 * @brief Makes a record from a username and encrypted password pair if that
 * username does not already have a record tied to it
 *
 * NOTE: this function provides synchronizes read and write access to the
 * recordDB, thus it can be used by multiple callers in parallel or concurrently
 *
 * @param username
 * @param encryptedPassword
 * @return Record* a new record. If a record with the same username already
 * exists in the recordDB, then it returns nullptr
 */
Record* RecordDB::makeRecord(string username, int encryptedPassword)
{
   // blocking wait to read
   pthread_rwlock_rdlock(&rwLock);
   if (recordMap.find(username) != recordMap.end()) {
      pthread_rwlock_unlock(&rwLock); // finished read
      return nullptr;
   }
   pthread_rwlock_unlock(&rwLock); // finished read

   Record* newRecord = new Record(username, encryptedPassword);

   pthread_rwlock_wrlock(&rwLock); // block wait to write
   recordMap.insert({username, newRecord});
   pthread_rwlock_unlock(&rwLock); // finished write

   return newRecord;
}

bool RecordDB::deleteRecord(string username)
{
   pthread_rwlock_wrlock(&rwLock); // block wait to write
   bool retval = recordMap.erase(username) == 1;
   pthread_rwlock_unlock(&rwLock); // finished write
   return retval;
}

Record* RecordDB::getRecord(string username, string password)
{
   int encryptedPassword = encrypt(password);
   // blocking wait to read
   pthread_rwlock_rdlock(&rwLock);
   auto recordHolder = recordMap.find(username);
   if (recordHolder == recordMap.end()) {
      pthread_rwlock_unlock(&rwLock); // finished read
      return nullptr;
   }
   pthread_rwlock_unlock(&rwLock); // finished read

   Record* record = (Record*)recordHolder->second;
   if (record->checkPassword(encryptedPassword))
      return record;
   else
      return nullptr;

   return nullptr;
}

bool RecordDB::checkIfRecord(string username)
{
   // blocking wait to read
   pthread_rwlock_rdlock(&rwLock);
   bool retval = recordMap.find(username) != recordMap.end();
   pthread_rwlock_unlock(&rwLock); // finished read
   return retval;
}