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
#include <fstream>
#include <map>
#include "../include/basic_types.h"
#include "../include/point_set.h"
#include "../include/sub_tree.h" 
#include "../include/tools.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  bool dot{false};
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "-d") {
      dot = true;
    }
  }
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
  if (dot) {
    std::ofstream file{"out.dot"};
    std::map<emst::point, char> point_naming;
    file << "graph {\n";
    char point_id{'a'};
    for (const auto& point : point_set.GetPoints()) {
      point_naming.insert(std::make_pair(point, point_id));
      file << "  " << point_id << "[pos=\"" << point.first << "," << point.second << "!\"]\n";
      point_id++;
    }
    for (const auto& naming : point_naming) {
      char origin{naming.second};
      for (const auto& arch : point_set.GetTree()) {
        if (arch.first == naming.first) {
          file << "  " << naming.second << "--" << point_naming[arch.second] << "\n";
        }
      }
    }
    file << "}";
  } else {
    for (const emst::arch& current_arch : point_set.GetTree()) {
      std::cout << current_arch.first << "---" << current_arch.second << "\n";
    }
  }
  return 0;
}