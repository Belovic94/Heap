CC = gcc
C_FLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
DEFAULT = TPHeap
HEAP = heap
PILA = pila
VECTOR = vector_dinamico
TESTING  = testing
OBJS =  $(HEAP).o $(VECTOR).o $(TESTING).o $(PILA).o
VALGRIND = valgrind
V_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

all: clean $(DEFAULT)

$(DEFAULT): clean  $(OBJS)
		$(CC) $(C_FLAGS) main.c $(OBJS) pruebas_alumnos.c  -o $(DEFAULT)

%.o : %.c %.h
	$(CC) $(C_FLAGS) $< -c

run: $(DEFAULT)
		$(VALGRIND) $(V_FLAGS) ./$(DEFAULT)

clean_obj:
		rm -f *.o

clean: clean_obj
		rm -f $(DEFAULT)
