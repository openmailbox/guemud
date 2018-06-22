CXX = g++
EXE = guemud

SRCDIR = ./src
NETWORKINGDIR = $(SRCDIR)/networking

CFLAGS = -std=c++11 -Wall -Wextra -Werror

main: networking libs
	$(CXX) $(CFLAGS) $(SRCDIR)/*.o $(NETWORKINGDIR)/*.o -o $(EXE)

libs: $(SRCDIR)/$(wildcard *.cc)
	cd $(SRCDIR) && $(CXX) $(CFLAGS) *.cc -c;

networking: $(NETWORKINGDIR)/$(wildcard *.cc)
	cd $(NETWORKINGDIR) && $(CXX) $(CFLAGS) *.cc -c;

clean:
	rm $(EXE) $(NETWORKINGDIR)/*.o $(SRCDIR)/*.o;
