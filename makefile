# Galutinis vykdomasis failas (programa)
program.exe : main.o graph.o
	gcc -std=c99 -o program.exe main.o graph.o

# Pagrindinio failo kompiliavimas (priklauso nuo main.c ir graph.h)
main.o : main.c graph.h
	gcc -c -std=c99 main.c

# Grafo realizacijos kompiliavimas (priklauso nuo graph.c ir graph.h)
graph.o : graph.c graph.h
	gcc -c -std=c99 graph.c
