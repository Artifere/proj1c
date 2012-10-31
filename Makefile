SRC=main.c cities.c bst.c edge.c heap.c prim.c test.c tsp.c
DEP= ${SRC:.c=.dep}
OBJ= ${SRC:.c=.o}
CXX	 = gcc
LFLAGS   = 
CXXFLAGS = -Wall -Wextra -Wshadow -Wmissing-prototypes -Wunreachable-code -Winline -O0 -g


all: depend exe Makefile

exe: $(OBJ) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJ) $(LFLAGS)  $(LIB)

clean: 
	rm -f $(OBJ) $(DEP)

destroy: clean
	rm -f exe 

depend: ${DEP}

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

%.dep: %.c
	$(CXX) $(CXXFLAGS) -MM -MF $@ $<

-include ${DEP}
