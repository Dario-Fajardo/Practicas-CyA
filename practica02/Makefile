# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# 2º Curso en Grado en Ingeniería Informática
# Computabilidad y Algoritmia
# Práctica 1: Contenedores Asociativos
#
# @author Dario Fajardo alu0101564630@ull.edu.es
# @date 23 Sept 2023
# @brief Makefile del proyecto, permite compilar facilmente y hacer make clean
#		 para borrar los binarios de la carpeta después

CXX = g++
CXXFLAGS = -std=c++17 -v
######################################
files = *cc
######################################
all: programa

programa: $(files)
	@echo "compiling..."
	@$(CXX) $(CXXFLAGS) -o p02_cadenas $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm -rf *.o *gch *.out programa p02_cadenas
######################################