#include "constants.h"
#include <string>
#ifndef RECORDSDB_H
#define RECORDSDB_H

using namespace std;

class Record;
Record* makeRecord(string, int);

bool deleteRecord(string);

Record* getRecord(string, int);

bool checkIfRecord(string);

#endif