


server:
	g++ -pthread server.cpp commandParser.cpp session.cpp \
	sessionsDB.cpp globalFuncs.cpp userRecord.cpp userRecordDB.cpp \
	commandLexer.cpp \
	loginCommands.cpp -o server -g

client:
	g++ -pthread client.cpp globalFuncs.cpp -o client

clean:
	rm server client