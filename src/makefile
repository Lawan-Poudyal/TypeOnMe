CPPFLAGS = -lraylib -lsqlite3 -Wall -Idb/ -o

login:login db/database.cpp
	g++ login.cpp db/database.cpp $(CPPFLAGS) TypeOnMeLogin

all:main db/database.cpp
	g++ main.cpp db/database.cpp $(CPPFLAGS) TypeOnMe

