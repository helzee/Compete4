#include "constants.h"
#include "session.cpp"
#include <vector>

using namespace std;

vector<Session> sessions = new vector<Session>;

Session* makeSession()
{
   Session* newSession = new Session();
   sessions.push_back(newSession);
   return newSession;
}