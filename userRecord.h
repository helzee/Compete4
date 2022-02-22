/** @file userRecord.h
 *
 */
#include "constants.h"

#ifndef USER_RECORD_H
#define USER_RECORD_H

using namespace std;

#define MIN_UNAME 4
#define MAX_UNAME 32
#define MIN_PASSWORD 6
#define MAX_PASSWORD 32

class Record
{
public:
   Record(string, int);
   bool checkPassword(int);
   string getName();
   void winGame();
   void loseGame();
   void tieGame();
   float getRatio();
   int getGamesPlayed();
   static bool isUsernameValid(string username);
   static bool isPasswordValid(string password);

private:
   int gamesWon = 0;
   int gamesLost = 0;
   int gamesPlayed = 0;
   string username;
   int encryptedPassword;
};

#endif