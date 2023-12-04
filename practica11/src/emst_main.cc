/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo se encuentra la función main del programa emst que nos permite encontrar
*        el árbol generador mínimo euclidiano de un conjunto de puntos
*/

#include <iostream>
#include "../include/basic_types.h"
#include "../include/point_set.h"
#include "../include/sub_tree.h" 

int main(int argc, char* argv[]) {
  emst::point_vector points;
  std::cout << "Introduzca los puntos escribiendo ambas componentes por cada uno, cuando termine escriba \n";
  while (true) {
    double x_component;
    double y_component;
    std::cin >> x_component;
    std::cin >> y_component;
    if (!std::cin) {
      break;
    }
    emst::point new_point{std::make_pair(x_component, y_component)};
    std::cout << "new point: " << new_point << "\n";
    points.emplace_back(new_point);
  }
  emst::PointSet point_set{points};
  point_set.EMST();
  for (const emst::arch& current_arch : point_set.GetTree()) {
    std::cout << current_arch.first << "---" << current_arch.second << "\n";
  }
  return 0;
}