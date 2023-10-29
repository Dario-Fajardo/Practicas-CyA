/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 7: Gramáticas en Forma Normal de Chomsky
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 29 Oct 2023
 * @brief Archivo que contiene la función main del programa, en este se cogen 
 *        los nombres del archivo de entrada de la gramática y se obtiene la
 *        gramática original que posteriormente se pasará a forma normal de
 *        Chomsky
 */

#include "../include/grammar.h"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string input_file_name{argv[1]};
  Grammar initial_grammar{input_file_name};
  std::cout << "initial grammar:\n" << initial_grammar << "==================\n";
  Grammar normalized_grammar{initial_grammar.ChomskyNormalForm()};
  std::string output_file_name{argv[2]};
  std::ofstream output_file{output_file_name, std::ios_base::out};
  output_file << normalized_grammar;
  std::cout << normalized_grammar;
  return 0;
}