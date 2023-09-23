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

Language::Language() {
  language_strings_ = {};
}

Language::Language(const std::set<std::string>& language_strings) {
  language_strings_ = language_strings;
}

void Language::Insert(const std::string& new_string) {
  language_strings_.insert(new_string);
}

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