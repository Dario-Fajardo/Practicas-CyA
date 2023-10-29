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
#include "../include/tools.h"
#include <iostream>

/**
 * Función principal del programa, lee por línea de comandos dos nombres de 
 * archivo y crea una gramática a partir del primero, esta gramática es 
 * convertida a forma normal de Chomsky gracias al método ChomskyNormalForm()
 * de la clase Grammar y se imprime en el segundo archivo
 * 
 * @param argc: cuenta el número de parámetros introducidos por línea de comandos
 *              si no son suficientes o son demasiados el programa fallará
 * @param argv: un vector con todos los parámetros, de aquí se obtiene lo que
 *              el usuario pase por línea de comandos
 * 
 * @return un 0 si todo funciona correctamente
 */
int main(int argc, char *argv[]) {
  Usage(argc, argv);
  std::string input_file_name{argv[1]};
  Grammar initial_grammar{input_file_name};
  Grammar normalized_grammar{initial_grammar.ChomskyNormalForm()};
  std::string output_file_name{argv[2]};
  std::ofstream output_file{output_file_name, std::ios_base::out};
  output_file << normalized_grammar;
  std::cout << normalized_grammar;
  return 0;
}