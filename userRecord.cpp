#include "userRecord.h"

Record::Record(int id)
{
   this->id = id;
   username = "G: Default Name";
}

Record::Record(int id, string username)
{
   this->id = id;
   this->username = username;
}

int Record::getID() { return id; }