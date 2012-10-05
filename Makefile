SRC=main.c cities.c bst.c
DEP= ${SRC:.c=.dep}
OBJ= ${SRC:.c=.o}
CXX	 = gcc
LFLAGS   = 
CXXFLAGS = -Wall -Wextra -O0 -g


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
