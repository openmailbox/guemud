CXX = g++
EXE = guemud

SRCDIR = ./src
NETWORKINGDIR = $(SRCDIR)/networking
COMMANDSDIR = $(SRCDIR)/commands

CFLAGS = -std=c++11 -g -Wall -Wextra -Werror

main: networking commands libs
	$(CXX) $(CFLAGS) $(SRCDIR)/*.o $(NETWORKINGDIR)/*.o $(COMMANDSDIR)/*.o -o $(EXE)

libs: $(SRCDIR)/$(wildcard *.cc)
	cd $(SRCDIR) && $(CXX) $(CFLAGS) *.cc -c;

networking: $(NETWORKINGDIR)/$(wildcard *.cc)
	cd $(NETWORKINGDIR) && $(CXX) $(CFLAGS) *.cc -c;

commands: $(COMMANDSDIR)/$(wildcard *.cc)
	cd $(COMMANDSDIR) && $(CXX) $(CFLAGS) *.cc -c;

clean:
	rm $(EXE) $(NETWORKINGDIR)/*.o $(SRCDIR)/*.o; $(COMMANDSDIR)/*.o
