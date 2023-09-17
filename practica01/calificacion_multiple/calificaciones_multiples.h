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

#include<map>
#include <string>

class Lista {
 public:
  // Constructores
  Lista();
  Lista(std::string nombre_archivo);
  Lista(std::multimap<std::string, double> alumnos);
  // Getters
  std::multimap<std::string, double> GetLista() const { return alumnos_; }
  // Otros métodos
 private:
  std::multimap<std::string, double> alumnos_;
};