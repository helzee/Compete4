


server:
	g++ -pthread server.cpp commandParser.cpp session.cpp sessionsDB.cpp -o server

client:
	g++ client.cpp -o client

clean:
	rm server client