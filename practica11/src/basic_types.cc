/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos definicion de operadores y demás funciones para los tipos
*        del namespace emst
*/

#include "../include/basic_types.h"

std::ostream& operator<<(std::ostream& output, const emst::point& point_out) {
  output << "(" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point_out.first << ", ";
  output << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point_out.second << ")";
  return output;
}

std::ostream& operator<<(std::ostream& output, const emst::arch& arch) {
  output << arch.first << "----" << arch.second << "\n";
  return output;
}