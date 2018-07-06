CXX = g++
EXE = guemud

SRCDIR = ./src
NETWORKINGDIR = $(SRCDIR)/networking
COMMANDSDIR = $(SRCDIR)/commands
HANDLERSDIR = $(SRCDIR)/handlers
DATABASEDIR = $(SRCDIR)/database

CFLAGS = -std=c++11 -g -Wall -Wextra -Werror
LIBS = -lpthread -ldl

main: networking commands database handlers sqlite libs
	$(CXX) $(CFLAGS) $(SRCDIR)/*.o $(NETWORKINGDIR)/*.o $(COMMANDSDIR)/*.o $(DATABASEDIR)/*.o $(HANDLERSDIR)/*.o -o $(EXE) $(LIBS)

libs: $(SRCDIR)/$(wildcard *.cc)
	cd $(SRCDIR) && $(CXX) $(CFLAGS) *.cc -c;

networking: $(NETWORKINGDIR)/$(wildcard *.cc)
	cd $(NETWORKINGDIR) && $(CXX) $(CFLAGS) *.cc -c;

commands: $(COMMANDSDIR)/$(wildcard *.cc)
	cd $(COMMANDSDIR) && $(CXX) $(CFLAGS) *.cc -c;

handlers: $(HANDLERSDIR)/$(wildcard *.cc)
	cd $(HANDLERSDIR) && $(CXX) $(CFLAGS) *.cc -c;

database: $(DATABASEDIR)/$(wildcard *.cc)
	cd $(DATABASEDIR) && $(CXX) $(CFLAGS) *.cc -c;

sqlite: $(DATABASEDIR)/sqlite3.c
	cd $(DATABASEDIR) && gcc -g sqlite3.c -c;

clean:
	rm $(EXE) $(NETWORKINGDIR)/*.o $(SRCDIR)/*.o $(COMMANDSDIR)/*.o $(DATABASEDIR)/*.o $(HANDLERSDIR)/*.o
