
# --------------------------------------------------------------------
#  Makefile de tarea 1.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
# 
# Si `objetivo` es un archivo los comandos se ejecutan solo si no está 
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------




# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega


# Objetivo predeterminado (no se necesita especificarlo al invocar `make`).
all: principal

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -Iinclude

obj/utils.o: cpp/utils.cpp include/utils.h
	$(CC) $(CCFLAGS) -c cpp/utils.cpp -o obj/utils.o

obj/texto.o: cpp/texto.cpp include/texto.h include/utils.h
	$(CC) $(CCFLAGS) -c cpp/texto.cpp -o obj/texto.o

obj/principal.o: principal.cpp include/texto.h include/utils.h
	$(CC) $(CCFLAGS) -c principal.cpp -o obj/principal.o

principal: obj/principal.o obj/texto.o obj/utils.o
	$(CC) $(CCFLAGS) obj/principal.o obj/texto.o obj/utils.o -o principal

# borra binarios
clean_bin:
	@rm -f principal obj/*.o

# borra resultados de ejecución y comparación
clean_test:
	@rm -f test/*.sal test/*.diff

# borra binarios, resultados de ejecución y comparación
clean:clean_test clean_bin
	@rm -f *~ include/*~ cpp/*~


# lista de casos de prueba
CASOS = 01 02 03 04 A

# Test del programa. Depende de 'principal'. 
# Antes borra resultado de tests anteriores. 
testing:principal clean_test
	@for caso in $(CASOS); do                                         \
		./principal < test/$$caso.in > test/$$caso.sal;           \
		diff test/$$caso.out test/$$caso.sal > test/$$caso.diff;  \
		if [ $$? -ne 0 ];                                         \
		then                                                      \
			echo ---- ERROR en caso $$caso ----;              \
		else                                                      \
			rm test/$$caso.diff;                              \
		fi;                                                       \
	done
# Con $$? se obtiene el estado de salida del comando anterior. 
# En el caso de `diff`, si los dos archivos comparados no son iguales, 
# el estado de la salida no es 0.   


entrega:
	@rm -f Entrega1.tar.gz
	tar zcvf Entrega1.tar.gz -C cpp utils.cpp texto.cpp
