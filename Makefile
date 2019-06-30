CXX=g++ -std=c++17 -g
OBJDIR=./obj/
SRCDIR=./src/
INCDIR=./inc/

all: clean dir tradutor

tradutor:$(OBJDIR)tradutor.o $(OBJDIR)utils.o $(OBJDIR)pre_processador.o
	$(CXX) $^ -o $@

$(OBJDIR)tradutor.o:$(SRCDIR)tradutor.cpp $(SRCDIR)pre_processador.cpp $(INCDIR)pre_processador.hpp $(SRCDIR)utils.cpp $(INCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)tradutor.o		

$(OBJDIR)pre_processador.o:$(SRCDIR)pre_processador.cpp $(INCDIR)pre_processador.hpp $(SRCDIR)utils.cpp $(INCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)pre_processador.o

$(OBJDIR)utils.o:$(SRCDIR)utils.cpp $(INCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)utils.o					

dir:
	if test -d obj; then echo obj exists; else mkdir obj;fi

clean:
	rm -f $(OBJDIR)*.o *.pre *.obj tradutor
