CC = gcc
C_FLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
DEFAULT = TPHeap
HEAP= heap
VECTOR = vector_dinamico
TESTING  = testing
OBJS =  $(HEAP).o $(VECTOR).o $(TESTING).o
VALGRIND = valgrind
V_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

all: $(DEFAULT)

$(DEFAULT): clean  $(OBJS)
		$(CC) $(C_FLAGS) main.c $(OBJS) pruebas_alumnos.c  -o $(DEFAULT)

$(HEAP).o: $(HEAP).c $(HEAP).h
		$(CC) $(C_FLAGS) $(HEAP).c -c

$(VECTOR).o: $(VECTOR).c $(VECTOR).h
		$(CC) $(C_FLAGS) $(VECTOR).c -c

$(TESTING).o: $(TESTING).c $(TESTING).h
		$(CC) $(C_FLAGS) $(TESTING).c -c

run: $(DEFAULT)
		$(VALGRIND) $(V_FLAGS) ./$(DEFAULT)

clean_obj:
		rm -f *.o

clean: clean_obj
		rm -f $(DEFAULT)
