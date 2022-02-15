/** @file userRecord.h
 *
 */
#include "constants.h"

#ifndef USER_RECORD_H
#define USER_RECORD_H

using namespace std;

class Record
{
public:
   int gamesWon = 0;
   int gamesPlayer = 0;
   string username;

   Record(int);
   Record(int, string);
   int getID();

private:
   int id;
};

#endif