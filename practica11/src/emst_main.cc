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
#include <cstdio>
#include "../include/basic_types.h"
#include "../include/point_set.h"
#include "../include/sub_tree.h" 
#include "../include/tools.h"


/**
 * Función main del programa implementa un menú que permite al usuario ajustar el funcionamiento del programa
 * según requiera
 * 
 * @param argc: contador de argumentos pasados en ejecución
 * @param argv: vector con los argumentos pasados en ejecución
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv); // Comprobamos argumentos pasados por línea de comandos
  bool dot{false};
  if (argc == 2) { // Miramos si se introdujo la opción -d (generar archivo DOT)
    std::string parameter{argv[1]};
    if (parameter == "-d") {
      dot = true;
    }
  }
  emst::point_vector points; // Vector con los puntos introducidos
  emst::tree emst; // Futuro árbol mínimo generador
  while (true) {
    // Mostrar opciones del menú
    int option;
    if (!points.empty()) {
      std::cout << "Puntos en el conjunto: \n";
    }
    for (const auto& point : points) {
      std::cout << point << "\n";
    }
    std::cout << "\n[1]: Introducir nuevo punto\n[2]: Calcular EMST\n";
    if (dot) {
      std::cout << "[3]: Desactivar exportación a archivo DOT\n";
    } else {
      std::cout << "[3]: Activar exportacion a archivo DOT\n";
    }
    std::cout << "[0]: Salir del programa\n";
    if (!emst.empty()) {
      std::cout << " \nÚltimo EMST:\n";
      for (const auto& arch : emst) {
        std::cout << arch;
      }
      std::cout << "\n";
    }
    std::cout << "\nOpcion: ";
    std::cin >> option;
    std::cout << "\n";
    // Comprobar opción introducida y ejecutar
    switch (option) {
      case 0: { // Salir del programa
        system("clear");
        exit(EXIT_SUCCESS);
        break;
      }
      case 1: { // Añadir un punto
        int x_component, y_component;
        system("clear");
        std::cout << "Componente X: ";
        std::cin >> x_component;
        std::cout << "Componente Y: ";
        std::cin >> y_component;
        if (y_component && x_component) {
          emst::point new_point{std::make_pair(x_component, y_component)};
          if (std::find(points.begin(), points.end(), new_point) == points.end()) { // Comprobamos que no existe ya
            std::cout << "new point: " << new_point << "\n";
            points.emplace_back(new_point);
          }
        }
        break;
      }
      case 2: { // Calcular el EMST y guardarlo en emst
        if (points.empty()) {
          break;
        }
        emst::PointSet point_set{points};
        point_set.EMST();
        emst = point_set.GetTree();
        if (dot) {
          std::ofstream file{"out.dot"}; // Salida
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
          break;
        }
        break;
      }
      case 3: { // Alternar la opción -d (archivo DOT)
        if (dot) {
          dot = false;
        } else {
          dot = true;
        }
      }
    }
    system("clear");
  }
  return 0;
}