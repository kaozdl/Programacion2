
# --------------------------------------------------------------------
#  Makefile de tarea 2.

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

# Objetivo predeterminado (no se necesita especificarlo al invocar `make`).
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing


# directorios 
HDIR    = include
CPPDIR  = cpp
ODIR    = obj

TESTDIR = test

MODULOS = utils texto info lista uso_lista

# lista de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.cpp)
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -I$(HDIR)


$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# cada .o depende de su .cpp
# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

# $^ se expande para tranformarse en todas las dependencias 
$(EJECUTABLE): $(ODIR)/$(PRINCIPAL).o $(OS) 
	$(CC) $(CCFLAGS) $^ -o $@

# Ejecutables 
ejemplos_letra:ejemplos_letra.cpp $(OS)
	$(CC) $(CCFLAGS) $^ -o $@

test_info:test_info.cpp  $(ODIR)/utils.o $(ODIR)/texto.o $(ODIR)/info.o
	$(CC) $(CCFLAGS) $^ -o $@

test_lista:test_lista.cpp  $(OS)
	$(CC) $(CCFLAGS) $^ -o $@

test_uso_lista:test_uso_lista.cpp  $(OS)
	$(CC) $(CCFLAGS) $^ -o $@


# obtener las salidas
$(TESTDIR)/ejemplos_letra.sal:ejemplos_letra
	./ejemplos_letra > $@

# $< se expande para transformarse en la primera dependencia
$(TESTDIR)/test_info.sal:$(TESTDIR)/test_info.in test_info
	./test_info < $<  > $@

# correr test_lista
correr_test_lista:test_lista
	./$^

# correr test_lista
correr_test_uso_lista:test_uso_lista
	./$^


# lista de casos de prueba
CASOS = 01 02 03 04 05 06 07 08 09 A1 A2 A3 A4 A5 A6

# lista de archivos, con directorio y extensión
INS=$(CASOS:%=$(TESTDIR)/%.in)
OUTS=$(CASOS:%=$(TESTDIR)/%.out)
SALS=$(CASOS:%=$(TESTDIR)/%.sal)
DIFFS=$(CASOS:%=$(TESTDIR)/%.diff)

$(SALS):$(EJECUTABLE)
$(TESTDIR)/%.sal:$(TESTDIR)/%.in
	./$(EJECUTABLE) < $< > $@ 


# cada .diff depende de su .out y de su .sal
%.diff: %.out %.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior. 
# En el caso de `diff`, si los dos archivos comparados no son iguales, 
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.   




# Test general. Las dependencias son los .diff.
# Con `find` se encuentran los .diff de tamaño > 0 que están en el directorio 
# $(TESTDIR) y lo asigna a $(LST_ERR).
# Si el tamaño de $(LST_ERR) no es cero imprime los casos con error.
# Con `sed` se elimina el nombre de directorio y la extensión. 
testing:$(DIFFS) $(TESTDIR)/ejemplos_letra.diff $(TESTDIR)/test_info.diff
	@LST_ERR=$$(find $(TESTDIR) -name *.diff -size +0c -print);             \
	if [ -n "$${LST_ERR}" ];                                                \
	then                                                                    \
		echo -- CASOS CON ERRORES --;                                   \
		echo "$${LST_ERR}" | sed -e 's/$(TESTDIR)\///g' -e 's/.diff//g';\
	fi

# Genera el entregable. 
ENTREGA=Entrega2.tar.gz 
CPPS_ENTREGA = $(MODULOS:%=%.cpp)
entrega:testing
	@rm -f $(ENTREGA)
	@tar zcf $(ENTREGA) -C cpp $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)


# borra binarios
clean_bin:
	rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS) test_uso_lista test_lista test_info ejemplos_letra

# borra resultados de ejecución y comparación
clean_test:
	rm -f $(TESTDIR)/*.sal $(TESTDIR)/*.diff

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f *~ $(HDIR)/*~ $(CPPDIR)/*~


check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
