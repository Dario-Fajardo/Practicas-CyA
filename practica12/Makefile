# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# 2º Curso en Grado en Ingeniería Informática
# Computabilidad y Algoritmia
# Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
#
# @author Dario Fajardo alu0101564630@ull.edu.es
# @date 2 Dic 2023
# @brief Makefile del proyecto, permite compilar facilmente y hacer make clean
#		 para borrar los binarios de la carpeta después

CXX = g++
CXXFLAGS = -std=c++17
######################################
files = src/*cc
######################################
all: programa

programa: $(files)
	@echo "======================================================"
	@echo "chambeando..."
	@echo "======================================================"
	@$(CXX) $(CXXFLAGS) -o bin/quickhull $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm bin/quickhull
######################################