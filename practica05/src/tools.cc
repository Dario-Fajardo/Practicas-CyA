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
        std::cout << "Este programa sirve para simular un autómata finito, para\n";
        std::cout << "ello, recibe 2 parámetros por línea de comandos, el\n";
        std::cout << "primero un archivo de texto que define un autómata, su\n";
        std::cout << "primera línea ha de tener los símbolos del alfabeto\n";
        std::cout << "separados por espacio, la siguiente el número de estados\n";
        std::cout << "luego, cuál es el estado de arranque del autómata\n";
        std::cout << "después de esas líneas el archivo tendrá una línea\n";
        std::cout << "para cada estado, incluyendo, su número identificador,\n";
        std::cout << "si se trata de un estado de acpetación o no,\n";
        std::cout << "su número de transiciones y por último por cada una de\n";
        std::cout << "estas, el símbolo y el estado destino\n\nEl archivo debería";
        std::cout << "tener un formato similar al siguiente:\n\n";
        std::cout << "0 1\n3\n0\n0 0 2 0 2 1 1\n1 1 2 0 1 1 1\n2 0 2 0 1 1 3\n";
        std::cout << "\nEl segundo ha de contener las cadenas que se van a \n";
        std::cout << "comprobar separadas por un retorno de carro tal que así\n";
        std::cout << "\n10011011\n11111\n0101101\n111\n&\n\n";
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "Modo de empleo: ./p05_simulador_af automata.af cadenas.txt\n";
    std::cout << "Pruebe: ./p05_simulador_af --help para más información\n";
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