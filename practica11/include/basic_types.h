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

namespace emst {
  typedef std::pair<double, double> point;
  typedef std::vector<point> point_vector;
  typedef std::pair<point, point> arch;
  typedef std::pair<double, point> weighted_arch;
  typedef std::vector<weighted_arch> arch_vector;
  typedef std::set<point> point_collection;
  typedef std::vector<arch> tree;
}

// Definir operadores << y >> para estos tipos según vayan haciendo falta