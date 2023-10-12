/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
 * @brief Este programa es capaz de recibir por parámetros en nombre de un
 *        archivo y de el obtener una serie de cadenas de las cuales se podrá
 *        obtener información como su alfabeto, longitud, etc.
 */
#include "string.h"
#include "tools.h"
#include <fstream>

/**
 * Se obtienen como argumento un archivo de entrada, otro de salida y un opcode
 * en el primero hay una serie de cadenas, de estas se obtendrá cierta 
 * información que será escrita en el archivo de salida, el opcode le indica
 * al programa que información es la que escribir
 * 
 * @param argc: número de argumentos del programa
 * @param argv: todos los parámetros introducidos por línea de comandos
 */
int main(int argc, char *argv[]) {
  Usage(argc, argv);
  std::string input_file_name{argv[1]};
  std::ifstream input_file{input_file_name, std::ios_base::in};
  std::string output_file_name{argv[2]};
  std::ofstream output_file{output_file_name, std::ios_base::out};
  std::string entry_line;
  switch (atoi(argv[3])) {
    case 1: {
      while(getline(input_file, entry_line)) {
      String file_string{entry_line};
      output_file << file_string.GetAlphabet() << std::endl;
      }
      break;
    }
    case 2: {
      while(getline(input_file, entry_line)) {
      String file_string{entry_line};
      output_file << file_string.Length() << std::endl;
      }
      break;
    }
    case 3: {
      while(getline(input_file, entry_line)) {
      String file_string{entry_line};
      output_file << file_string.Reverse() << std::endl;
      }
      break;
    }
    case 4: {
      while(getline(input_file, entry_line)) {
      String file_string{entry_line};
      output_file << file_string.Prefixes() << std::endl;
      }
      break;
    }
    case 5: {
      while(getline(input_file, entry_line)) {
      String file_string{entry_line};
      output_file << file_string.Sufixes() << std::endl;
      }        
      break;
    }
    case 6: {
      std::string second_input_file_name{argv[4]};
      std::ifstream second_input_file{second_input_file_name, std::ios_base::in};
      std::string second_entry_line;
      while (getline(input_file, entry_line) && getline(second_input_file, second_entry_line)) {
        String first_string{entry_line};
        String second_string{second_entry_line};
        output_file << first_string * second_string << std::endl;
      }
      break;
    }
    default: {
      std::cout << "Ese opcode no corresponde con ninguna función del programa\n";
      exit(EXIT_FAILURE);
    }
  }
}