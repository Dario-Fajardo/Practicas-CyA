/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
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
  if (argc != 3) {
    if (argc == 2) {
      std::string parameter{argv[1]};
      if (parameter == "--help" || parameter == "-h") {
        std::cout << "Este programa sirve para convertir un NFA en un DFA \n";
        std::cout << "usando el algoritmo de construcción de subconjuntos,\n";
        std::cout << "para ello el programa necesita que se introduzca un \n";
        std::cout << "primer archivo que defina el NFA y el nombre de un \n";
        std::cout << "segundo archivo en el que se introducirá la información\n";
        std::cout << "en el mismo formato que necesita el archivo de entrada.\n";
        std::cout << "Dicho formato se define a continuación:\n\n";
        std::cout << "Línea 1: Símbolos del alfabeto separados por espacios.\n";
        std::cout << "Línea 2: Número total de estados del autómata\n";
        std::cout << "Línea 3: Estado de arranque del autómata\n";
        std::cout << "Después de estás se define una línea para cada estado:\n";
        std::cout << "   - ID del estado\n";
        std::cout << "   - 1 si es de aceptación 0 si no\n";
        std::cout << "   - Número de transiciones del estado\n";
        std::cout << "   Por último, en la misma línea, se definen las ";
        std::cout << " transiciones del estado de la siguiente manera\n";
        std::cout << "      - Símbolo de la transición (&) si es una épsilon-";
        std::cout << "transición\n";
        std::cout << "      - Estado destino de dicha transición\n\n";
        std::cout << "Teniendo todo eso en cuenta, el archivo deberia tener un";
        std::cout << " formato similar al siguiente:\n\n";
        std::cout << "0 1\n3\n0\n0 0 2 0 2 1 1\n1 1 2 0 1 1 1\n2 0 2 0 1 1 3\n";
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "Modo de empleo: ./p06_const_sub entrada.nfa salida.dfa\n";
    std::cout << "Pruebe: ./p06_const_sub --help para más información\n";
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