/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 16 Sept 2023
 * @brief Este programa lee un fichero con diversas notas para varios alumnos y
 *        muestra la más alta para cada uno, además, en ejecución, permite hacer
 *        cambios en estas notas.
 */
#include <map>
#include <set>
#include <string>

std::map<std::string, double> LeerCalificaciones(const std::string& nombre_archivo);
void ImprimirCalificaciones(const std::map<std::string, double>& lista);
void InsertarCalificacion(std::map<std::string, double>& lista);
void Usage(int argc, char *argv[]);
void Menu(std::map<std::string, double>& lista);