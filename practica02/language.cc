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
#include "language.h"

/**
 * Constructor por defecto por si se crea un objeto sin indicar ningún valor
 */
Language::Language() {
  language_strings_ = {};
}

/**
 * Se construye el lenguaje a partir de un std::set de cadenas
 */
Language::Language(const std::set<std::string>& language_strings) {
  language_strings_ = language_strings;
}

/**
 * Método para editar un lenguaje sin tener acceso a sus atributos
 */
void Language::Insert(const std::string& new_string) {
  language_strings_.insert(new_string);
}

/**
 * Se imprime el lenguaje como un conjunto cualquiera, entre {} y con sus
 * elementos separados por coma y espacio
 * 
 * @param output: la salida por la que se imprimirá
 * @param alphabet: el lenguaje a imprimir
 */
std::ostream& operator<<(std::ostream& output, const Language& language) {
  int iterator{1};
  output << "{";
  for (const String& actual_string : language.GetLanguageStrings()) {
    output << actual_string;
    if (iterator != language.GetLanguageStrings().size()) {
      output << ", ";
    }
    iterator++;
  }
  output << "}";
  return output;
}