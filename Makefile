all: main ejecutar clean

main: main.o funciones.o proceso.o
	g++ main.o funciones.o proceso.o -o programa

main.o: main.cpp
	g++ -c main.cpp 

funciones.o: funciones/funciones.h funciones/funciones.cpp
	g++ -c funciones/funciones.cpp

proceso.o: proceso/proceso.h proceso/proceso.cpp
	g++ -c proceso/proceso.cpp

ejecutar: main
	./programa

clean:
	rm *.o programa
