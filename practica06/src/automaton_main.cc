/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 5: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 13 Oct 2023
 * @brief Este es el archivo main de la aplicación, implementa el funcionamiento
 *        principal del simulador de autómatas finitos
 */

#include "../include/automaton.h"

/**
 * Función main del programa. Creamos un autómata y probamos si acepta diversas
 * cadenas introducidas por un archivo de texto, luego esta información es 
 * mostrada en pantalla
 * 
 * @param argc: contador de argumentos pasados por línea de comandos
 * @param argv: valores de los argumentos
 * 
 * @return 0 si el funcionamiento del programa ha sido correcto
 */
int main(int argc, char *argv[]) {
  Usage(argc, argv);
  std::string automaton_file_name{argv[1]};
  Automaton main_automaton{automaton_file_name};
  std::ifstream string_file{argv[2], std::ios_base::in};
  std::string line;
  while (getline(string_file, line)) {
    String current_string{line};
    if (main_automaton.Accept(main_automaton.Evaluate(current_string))) {
      std::cout << current_string << " --- Accepted\n";
    } else {
      std::cout << current_string << " --- Rejected\n";
    }
  }
  return 0;
}
