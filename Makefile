CXX = g++
EXE = guemud

SRCDIR = ./src

CFLAGS = -std=c++11 -Wall -Wextra -Werror

main: libs
	$(CXX) $(CFLAGS) $(SRCDIR)/*.o -o $(EXE)

libs: $(SRCDIR)/$(wildcard *.cc)
	cd $(SRCDIR) && $(CXX) $(CFLAGS) *.cc -c;

clean:
	rm $(EXE) $(SRCDIR)/*.o;
