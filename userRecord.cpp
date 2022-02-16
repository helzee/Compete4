#include "userRecord.h"

Record::Record(string username, int encryptedPassword)
{
   this->username = username;
   this->encryptedPassword = encryptedPassword;
}

bool Record::checkPassword(int encryptedPassword)
{
   return this->encryptedPassword == encryptedPassword;
}

string Record::getName() { return username; }

void Record::winGame()
{
   gamesWon++;
   gamesPlayed++;
}

void Record::loseGame()
{
   gamesLost++;
   gamesPlayed++;
}

void Record::tieGame() { gamesPlayed++; }

float Record::getRatio() { return ((float)gamesWon) / gamesLost; }

int Record::getGamesPlayed() { return gamesPlayed; }