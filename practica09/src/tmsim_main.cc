#include <iostream>
#include "../include/turing_machine.h"
#include "../include/tools.h"

/**
 * Función main del programa, inicialmente coge el .tm y el .tape pasado por
 * línea de comandos, después estos pueden ir cambiando según el usuario
 * vaya queriendo haciendo uso de un menú interactivo.
 * 
 * @param argc: número de parámetros pasados por línea de comandos
 * @param argv: vector con dichos parámetros
 * 
 * @return 0 si todo fue bien, 1 si ha habido algún error
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  TuringMachine machine{std::string(argv[1])}; // Leemos y creamos la máquina
  std::ifstream tape_file{argv[2], std::ios_base::in}; // Leemos el .tape
  if (!tape_file.good()) { // Comprobamos que la cinta se leyó correctamente
    std::cout << "[ERROR]: no se puede acceder al archivo, compruebe que exista\n";
    exit(EXIT_FAILURE);
  }
  std::string tape_string;
  getline(tape_file, tape_string);
  if (Contains(tape_string, '\n')) { // Comprobamos que .tape solo tiene una cadena
    std::cout << "[ERROR]: El archivo .tape solo ha de contener una cadena\n";
    exit(EXIT_FAILURE);
  }
  while (true) { // Bucle del menú
    int option{Menu()}; // Opción que introduzca el usuario
    switch (option) {
      case 0: { // Salir
        system("clear");
        exit(EXIT_SUCCESS);
        break;
      }
      case 1: { // Imprimir máquina
        system("clear");
        std::cout << machine;
        break;
      }
      case 2: { // Computación
        system("clear");
        bool accepts{machine.Compute(tape_string)};
        if (accepts) {
          std::cout << "ACEPTADA\n";
        } else {
          std::cout << "RECHAZADA\n";
        }
        break;
      }
      case 3: { // Cambiar máquina de Turing
        system("clear");
        std::cout << "Introduzca el nombre de un nuevo archivo .tm\n";
        std::string new_tm_file;
        std::cin >> new_tm_file;
        system("clear");
        machine = TuringMachine{new_tm_file};
        break;
      }
      case 4: { // Cambiar cadena
        system("clear");
        std::cout << "Introduzca el nombre de un nuevo archivo .tape\n";
        std::string new_tape_file;
        std::cin >> new_tape_file;
        std::ifstream new_file{new_tape_file, std::ios_base::in};
        if (!new_file.good()) {
          std::cout << "[ERROR]: no se puede acceder al archivo, compruebe que exista\n";
          exit(EXIT_FAILURE);
        }
        getline(new_file, tape_string);
        system("clear");
        if (Contains(tape_string, '\n')) {
          std::cout << "[ERROR]: El archivo .tape solo ha de contener una cadena\n";
          exit(EXIT_FAILURE);
        }
        break;
      }
    }
  }
  return 0;
}