/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 9: Implementación de un simulador de máquinas de Turing
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 14 Nov 2023
 * @brief Este archivo contiene varias funciones que podrían ser útiles para
 *        varios programas
 */

#include "../include/tools.h"

/**
 * Función que comprueba los parámetros de entrada del main para saber si se
 * han introducido correctamente, además permite incluir una función --help
 * que le dará al usuario información detallada del uso de la aplicación al 
 * usuario
 * 
 * @param argc: número de parámetros pasados al programa
 * @param argv: todos los valores introducidos por línea de comandos
 */
void Usage(int argc, char *argv[]) {
  if (argc >= 1 && argc < 3) {
    if (argc == 2) {
      std::string parameter{argv[1]};
      if (parameter == "--help" || parameter == "-h") {
        std::cout << "\nEste programa calcula el árbol generador mínimo euclidiano de un conjunto\n";
        std::cout << "para ello se han de meter por entrada estándar los puntos de dicho conjunto\n";
        std::cout << "a partir de sus cordenadas (x, y), cuando se ejecuta el programa, este esperara\n";
        std::cout << "por entrada estándar pares de números, por cada uno de ellos de creará un punto\n";
        std::cout << "un ejemplo sería:\n\n1 1 2.5 4.3 4 5 6 7\n\nEsto crearía los puntos (1, 1), (2.5, 4,3)";
        std::cout << "(4, 5) y (6, 7) Sobre los que se calculará el árbol generador minimizando la distancia.\n";
        std::cout << "Cuando el programa calcula el emst, hay dos maneras de obtener el resultado, si no\n";
        std::cout << "se indica nada en ejecución mediante argumentos, se imprimirán las aristas por consola\n";
        std::cout << "de manera normal, en caso de dar la opción -d se creará un archivo .dot para visualizar\n";
        std::cout << "con Graphviz.\n\n";
        exit(EXIT_SUCCESS);
      }
    }
  } else {
    std::cout << "Modo de empleo: ./emst [[-h | --help] | -d]\n";
    std::cout << "Pruebe: ./emst --help para más información\n";
    exit(EXIT_FAILURE);
  }
}

/**
  * Permite buscar un caracter dentro de un std::string
  * 
  * @param string: la cadena en la que se va a buscar
  * @param character: el caracter a encontrar
  * 
  * @return true si se encuentra, false si no
  */
bool Contains(std::string string, char character) {
  for (const auto& actual_character : string) {
    if (actual_character == character) {
      return true;
    }
  }
  return false;
}

// /**
//  * Función que implementa la selección de opciones del menú
//  * 
//  * @return el valor de la opción elegida por el usuario
//  */
// int Menu() {
//   std::cout << "Elija la opción a realizar:\n[1] Imprimir máquina de Turing\n";
//   std::cout << "[2] Computar cadena\n[3] Cambiar máquina de Turing\n[4] Cambia";
//   std::cout << "r cadena a computar\n[0] Salir del programa\n";
//   int option;
//   std::cin >> option;
//   if (option > 4 || option <= -1) {
//     std::cout << "[ERROR]: Opción incorrecta\n";
//     exit(EXIT_FAILURE);
//   }
//   return option;
// }