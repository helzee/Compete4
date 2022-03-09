#include "userRecord.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// create a brand new record
Record::Record(string username, int encryptedPassword)
{
   this->username = username;
   this->encryptedPassword = encryptedPassword;
   inUse = false;
   gamesWon = gamesLost = gamesPlayed = 0;
}

// restore a record from disk
Record::Record(istream& file)
{

   file >> username >> encryptedPassword >> gamesPlayed >> gamesWon >>
       gamesLost;
}

// save record to disk
int Record::toFile(ofstream& file)
{

   file << username << " " << encryptedPassword << " " << gamesPlayed << " "
        << gamesWon << " " << gamesLost << endl;

   return 0;
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

float Record::getRatio()
{
   if (gamesLost == 0)
      return -1.0f;
   return ((float)gamesWon) / gamesLost;
}

int Record::getGamesWon() { return gamesWon; }

int Record::getGamesLost() { return gamesLost; }

int Record::getGamesPlayed() { return gamesPlayed; }

bool Record::isUsernameValid(string username)
{
   // first, check validity
   const char* lexeme = username.c_str();
   int size = 0;

   while (*lexeme != '\0') {
      size++;
      lexeme++;
   }

   if (size < MIN_UNAME || size > MAX_UNAME)
      return false;

   // Cannot be formatted like a guest account
   if (lexeme[0] == 'G' && lexeme[1] == ':' && lexeme[2] == ' ')
      return false;

   return true;
}

bool Record::isPasswordValid(string password)
{
   return password.length() >= MIN_PASSWORD;
}
