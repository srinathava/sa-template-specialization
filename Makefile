CXXFLAGS = -std=c++11
include Makefile.module

run: $(PROGNAME)
	./$(PROGNAME)
