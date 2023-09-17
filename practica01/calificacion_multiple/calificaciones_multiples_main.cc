/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 17 Sept 2023
 * @brief Este programa lee un fichero con diversas notas para varios alumnos y
 *        muestra todas ellas para cada uno, además, en ejecución, permite hacer
 *        cambios en estas notas.
 */
#include "calificaciones_multiples.h"

int main(int argc, char *argv[]) {
  Usage(argc, argv);
  Lista lista_de_alumnos{argv[1]};
  while (true) {
    Menu(lista_de_alumnos);
  }
}