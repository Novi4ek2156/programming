all: main.o func.o libMY_LOG.a
	gcc main.o -L. -lMY_LOG -o static_exe  
main.o: src/main.c include/main.h
	gcc -c src/main.c -I./src
func.o: src/func.c include/main.h
	gcc -c src/func.c  -I./src
libMY_LOG.a: func.o
	ar r libMY_LOG.a func.o
clean:
	rm -rf *.o main main.h.gch