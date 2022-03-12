#include "globalFuncs.h"

// sends param message via socket descriptor param
void send(string message, int sd)
{
   while (write(sd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;
}

// returns recieved string on socked descriptor passed via param
string receive(int sd)
{
   char rcvBuffer[MAX_MSG_SIZE];

   int nRead = 0;
   int nReadTemp = 0;
   while (nRead < MAX_MSG_SIZE) {
      nReadTemp = read(sd, rcvBuffer, MAX_MSG_SIZE - nRead);
      nRead += nReadTemp;
      if (nReadTemp == 0)
         break;
   }

   if (nRead == 0)
      return "exit";
   string command(rcvBuffer);
   return command;
}

// simple string comparison method, returns true if param a and b are equal
bool cmp(string a, string b) { return a.compare(b) == 0; }
