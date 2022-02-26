


server:
	g++ -pthread server.cpp commandParser.cpp session.cpp \
	sessionsDB.cpp globalFuncs.cpp userRecord.cpp userRecordDB.cpp \
	commandLexer.cpp gameSession.cpp gameSessionDB.cpp \
	menus/*.cpp board.cpp -o server -g

client:
	g++ -pthread client.cpp globalFuncs.cpp -o client

clean:
	rm server client