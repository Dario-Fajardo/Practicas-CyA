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

/**
 * Sobrecarga del operador << para poder imprimir en la consola o en archivos datos del tipo emst::point
 * 
 * @param output: canal de salida para dicho punto
 * @param point_out: punto a imprimir
 * 
 * @return el canal modificado con los nuevos datos
 */
std::ostream& operator<<(std::ostream& output, const emst::point& point_out) {
  output << "(" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point_out.first << ", ";
  output << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << point_out.second << ")";
  return output;
}

/**
 * Sobrecarga del operador << para imprimir arcos por consola
 * 
 * @param output: canal de salida
 * @param arch: arco a imprimir
 * 
 * @return el canal modificado con los nuevos datos
 */
std::ostream& operator<<(std::ostream& output, const emst::arch& arch) {
  output << arch.first << "----" << arch.second << "\n";
  return output;
}

/**
 * Sobrecarga del operador == para comparar si dos puntos son iguales o no
 * 
 * @param point_a, point_b: puntos a ser comparados
 * 
 * @return true si son iguales, false si no
 */
bool operator==(const emst::point& point_a, const emst::point& point_b) {
  if (point_a.first == point_b.first && point_a.second == point_b.second) {
    return true;
  } 
  return false;
}