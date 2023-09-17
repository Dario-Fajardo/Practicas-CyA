# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# 2º Curso en Grado en Ingeniería Informática
# Computabilidad y Algoritmia
# Práctica 1: Contenedores Asociativos
#
# @author Dario Fajardo alu0101564630@ull.edu.es
# @date 16 Sept 2023
# @brief Makefile del proyecto, permite compilar facilmente y hacer make clean
#		 para borrar los binarios de la carpeta después

CXX = g++
CXXFLAGS = -Wall -std=c++17
######################################
files = *cc
######################################
all: programa

programa: $(files)
	@echo "compiling..."
	@$(CXX) $(CXXFLAGS) -o calificaciones_multiples $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm -rf *.o *gch *.out programa calificaciones_multiples
######################################
