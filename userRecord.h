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
   Record(string);
   string getName();
   void winGame();
   void loseGame();
   void tieGame();
   float getRatio();
   int getGamesPlayed();

private:
   int gamesWon = 0;
   int gamesLost = 0;
   int gamesPlayed = 0;
   string username;
};

#endif