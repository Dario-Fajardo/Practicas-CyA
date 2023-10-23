/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Oct 2023
 * @brief Este es el archivo main de la aplicación, implementa la conversión de
 *        NFA a DFA usando el método SubsetConstruction() de la clase Automaton
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
  std::string nfa_file_name{argv[1]};
  Automaton nfa{nfa_file_name};
  Automaton dfa{nfa.SubsetConstruction()};
  std::string dfa_file_name{argv[2]};
  std::ofstream dfa_file{dfa_file_name, std::ios_base::out};
  dfa.PrintInFile(dfa_file);
  return 0;
}
