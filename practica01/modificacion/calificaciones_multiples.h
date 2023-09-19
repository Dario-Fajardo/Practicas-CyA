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
#include <set>

class Lista {
 public:
  // Constructores
  Lista();
  Lista(std::string nombre_archivo);
  // Getters
  std::map<std::string, std::multiset<double>> GetLista() const { return alumnos_; }
  // Otros métodos
  void ImprimirLista();
  void InsertarCalificacion();
 private:
  std::set<std::string> identificadores_;
  std::map<std::string, std::multiset<double>> alumnos_;
};

void Usage(int agrc, char *argv[]);
void Menu(Lista& lista_de_alumnos);