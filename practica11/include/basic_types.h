/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos declaraciones y typedefs con los tipos que
*        serán usados en la práctica y algunas sobrecargas de operadores
*/
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include <iomanip>

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#define MAX_SZ 3
#define MAX_PREC 1

namespace emst {
  typedef std::pair<double, double> point;
  typedef std::vector<point> point_vector;
  typedef std::pair<point, point> arch;
  typedef std::pair<double, arch> weighted_arch;
  typedef std::vector<weighted_arch> arch_vector;
  typedef std::set<point> point_collection;
  typedef std::vector<arch> tree;
}

std::ostream& operator<<(std::ostream& output, const emst::point& point);
std::ostream& operator<<(std::ostream& output, const emst::arch& arch);
bool operator==(const emst::point& point_a, const emst::point& point_b);

#endif
