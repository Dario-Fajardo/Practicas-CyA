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
  // Usage(argc, argv);
  std::string nfa_file_name{argv[1]};
  Automaton nfa{nfa_file_name};
  Automaton dfa{nfa.SubsetConstruction()};
  std::string dfa_file_name{argv[2]};
  std::ofstream dfa_file{dfa_file_name, std::ios_base::out};
  dfa.PrintInFile(dfa_file);
  return 0;
}
