RM_LIST = *.o *.exe compiler *.s
CFLAGS = -c

OBJ = main.o parse.o error.o symtab.o util.o

compiler : $(OBJ)
	gcc -o $@ $(OBJ)

parse.o   : parse.c
	gcc $(CFLAGS) parse.c 
main.o    : main.c
	gcc $(CFLAGS) main.c

util.o   : util.c 
	gcc $(CFLAGS) util.c
symtab.o : symtab.c
	gcc $(CFLAGS) symtab.c

clean:
	$(RM) $(RM_LIST)
