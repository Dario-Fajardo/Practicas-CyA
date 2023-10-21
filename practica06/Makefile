# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# 2º Curso en Grado en Ingeniería Informática
# Computabilidad y Algoritmia
# Práctica 5: Simulador Autómatas Finitos
#
# @author Dario Fajardo alu0101564630@ull.edu.es
# @date 12 Oct 2023
# @brief Makefile del proyecto, permite compilar facilmente y hacer make clean
#		 para borrar los binarios de la carpeta después

CXX = g++
CXXFLAGS = -std=c++17
######################################
files = src/*cc
######################################
all: programa

programa: $(files)
	@echo "compiling..."
	@echo "======================================================"
	@echo
	@$(CXX) $(CXXFLAGS) -o p05_simulador_af $(files)

######################################
.PHONY: clean
######################################
clean:
	@echo "cleaning up the directory..."
	@rm p05_simulador_af
######################################
