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

bool Record::isUsernameValid(string username) {
   //first, check validity
   const char* lexeme = username.c_str();
   int size = 0;
   
   while (*lexeme != '\0') {
      size++;
      lexeme++;
   }
   if (size < MIN_UNAME || size > MAX_UNAME) {
      return false;
   }
   return true;
}

bool Record::isPasswordValid(string password) { return password.length() >= MIN_PASSWORD; }
