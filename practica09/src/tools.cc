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
#include "../include/turing_machine.h"

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
        std::cout << "\nEste programa recibe por consola el nombre de dos\n";
        std::cout << "ficheros los cuales contendrán, el primero la\n";
        std::cout << "información sobre una máquina de Turing, el segundo\n";
        std::cout << "la cadena a introucir en la cinta de dicha máquina.\n";
        std::cout << "Al iniciar el programa se abrirá un menú donde se podrán\n";
        std::cout << "realizar varias cosas, con el 1, se imprimirá la\n";
        std::cout << "máquina que introdujo el usuario usando el archivo .tm,\n";
        std::cout << "con el 2 se computa la cadena del archivo .tape, con\n";
        std::cout << "el 3 se cambia el archivo .tm y con el 4, el .tape,\n";
        std::cout << "por último, usando el 0 se sale del programa.\n\n";
        std::cout << "El formato del archivo .tm ha de ser el siguiente:\n";
        std::cout << "5 <- Número de estados de la máquina\n0 <- Estado de ";
        std::cout << "arranque\n3 <- Enteros separados por espacios indicando ";
        std::cout << "estados de aceptación\n11 <- Número de tuplas\n";
        std::cout << "0 a X R 1 <- Líneas sucesivas con la información";
        std::cout << "de las tuplas\n0 $ $ S 3\n0 Y Y R 4\n. . .\n\n";
        std::cout << "El archivo .tape incluye una sola cadena a introducir\n";
        std::cout << "en la cinta de la máquina\n\n";
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "Modo de empleo: ./tmsim machine.tm string.tape\n";
    std::cout << "Pruebe: ./tmsim --help para más información\n";
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

/**
 * Función que implementa la selección de opciones del menú
 * 
 * @return el valor de la opción elegida por el usuario
 */
int Menu() {
  std::cout << "Elija la opción a realizar:\n[1] Imprimir máquina de Turing\n";
  std::cout << "[2] Computar cadena\n[3] Cambiar máquina de Turing\n[4] Cambia";
  std::cout << "r cadena a computar\n[0] Salir del programa\n";
  int option;
  std::cin >> option;
  if (option > 4 || option <= -1) {
    std::cout << "[ERROR]: Opción incorrecta\n";
    exit(EXIT_FAILURE);
  }
  return option;
}