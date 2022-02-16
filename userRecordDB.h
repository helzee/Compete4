#include "constants.h"
#include "userRecord.h"
#ifndef RECORDSDB_H
#define RECORDSDB_H

Record* makeRecord(string, int);

bool deleteRecord(string);

Record* getRecord(string, int);

bool checkIfRecord(string);

#endif