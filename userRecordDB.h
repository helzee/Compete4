#include "constants.h"
#include "userRecord.h"
#ifndef RECORDSDB_H
#define RECORDSDB_H

Record* makeRecord(string, string);

bool deleteRecord(string);

Record* getRecord(string, string);

bool checkIfRecord(string);

#endif