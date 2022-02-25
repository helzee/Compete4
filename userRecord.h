/** @file userRecord.h
 *
 */
#include "constants.h"
#include <iostream>

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
   Record(istream&);
   int toFile(ofstream&);
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
   int gamesWon;
   int gamesLost;
   int gamesPlayed;
   string username;
   int encryptedPassword;
};

#endif