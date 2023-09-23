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
#include "string.h"
#include <algorithm>

String::String() {
  symbols_ = {};
  alphabet_symbols_ = {};
}

String::String(const std::string& symbols) {
  symbols_ = symbols;
  for (const auto& symbol : symbols) {
    if (symbol != '&') {
      alphabet_symbols_.Include(symbol);
    }
  }
}

int String::Length() const {
  if (symbols_ != "&") {
    return symbols_.size();
  } else {
    return 0;
  }
}

String String::Reverse() {
  String reverse_string;
  reverse_string.symbols_ = symbols_;
  std::reverse(reverse_string.symbols_.begin(), reverse_string.symbols_.end());
  reverse_string.alphabet_symbols_ = alphabet_symbols_;
  return reverse_string;
}

Language String::Prefixes() {
  Language prefixes;
  String empty_string{"&"};
  String aux_string;
  prefixes.Insert(empty_string.symbols_);
  for (const auto& symbol : symbols_) {
    aux_string.symbols_ += symbol;
    prefixes.Insert(aux_string.symbols_);
  }
  return prefixes;
}

Language String::Sufixes() {
  Language sufixes;
  String empty_string{"&"};
  String aux_string;
  String symbols{this->Reverse()};
  sufixes.Insert(empty_string.symbols_);
  for (const auto& symbol : symbols.symbols_) {
    aux_string.symbols_ += symbol;
    sufixes.Insert(aux_string.Reverse().symbols_);
  }
  return sufixes;
}

bool String::operator<(const String& string) const {
  return (Length() < string.Length() ? true : false); 
}

std::ostream& operator<<(std::ostream& output, const String& string) {
  for (const auto& symbol : string.symbols_) {
    output << symbol;
  }
  return output;
}