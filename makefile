


server:
	g++ -pthread server.cpp commandParser.cpp session.cpp sessionsDB.cpp globalFuncs.cpp userRecord.cpp -o server

client:
	g++ client.cpp globalFuncs.cpp -o client

clean:
	rm server client