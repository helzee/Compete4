#include "globalFuncs.h"

void send(string message, int sd)
{
   while (write(sd, message.c_str(), MAX_MSG_SIZE) != message.length())
      ;
}

string recieve(int sd)
{
   char rcvBuffer[MAX_MSG_SIZE];

   int nRead = 0;
   int nReadTemp = 0;
   while (nRead < MAX_MSG_SIZE) {
      nReadTemp = read(data->sd, rcvBuffer, MAX_MSG_SIZE - nRead);
      nRead += nReadTemp;
      if (nReadTemp == 0)
         break;
   }

   string command(rcvBuffer);
   return command;
}

bool cmp(string a, string b) { return a.compare(b) == 0; }