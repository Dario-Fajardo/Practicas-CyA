/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
 * @brief Este programa es capaz de recibir por parámetros en nombre de un
 *        archivo y de el obtener una serie de cadenas de las cuales se podrá
 *        obtener información como su alfabeto, longitud, etc.
 */
#include "../include/string.h"

String EMPTY_STRING{"&"};

/**
 * Constructor por defecto por si se crea un objeto sin indicar ningún valor
 */
String::String() {
  symbols_ = {};
  alphabet_symbols_ = {};
}

/**
 * Se construye la cadena a partir de un std::string que contiene los símbolos
 * de la ya nombrada, se comprueba que no es la cadena vacía y se añaden todos 
 * sus símbolos también al atributo que representa su alfabeto.
 * 
 * @param symbols: std::string con todos los símbolos de la cadena
 */
String::String(const std::string& symbols) {
  symbols_ = symbols;
  for (const auto& symbol : symbols) {
    if (symbol != '&') {
      alphabet_symbols_.Include(symbol);
    }
  }
}

/**
 * Se obtiene la longitud de la cadena a partir del método size() de la clase
 * std::string usada para implementar la clase String de este programa
 * 
 * @return el tamaño de la cadena, si es & se retorna un 0 ya que es la cadena
 *         vacía
 */
int String::Length() const {
  if (symbols_ != "&") {
    return symbols_.size();
  } else {
    return 0;
  }
}

/**
 * Se invierte la cadena usando el método std::reverse() de algorithm
 * 
 * @return un objeto de la clase String que se trata de la cadena invertida
 */
String String::Reverse() {
  String reverse_string;
  reverse_string.symbols_ = symbols_;
  std::reverse(reverse_string.symbols_.begin(), reverse_string.symbols_.end());
  reverse_string.alphabet_symbols_ = alphabet_symbols_;
  return reverse_string;
}

/**
 * Se crea un lenguaje con los prefijos incluyendo la cadena vacía (obviamente)
 * Estos se van añadiendo uno a uno añadiendo cada vez un símbolo más
 * 
 * @return un lenguaje implementado con la clase Lenguage que contiene todas las
 *         cadenas que sean prefijo
 */
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

/**
 * Se utiliza el mismo concepto que para el método Prefixes(), sin embargo aquí
 * hacemos uso del método Reverse() para obtener los sufijos
 * 
 * @return Un lenguaje con todos los sufijos de la cadena 
 */
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

/**
 * Sobrecarga del operador < por si es necesario comparar la longitud de dos
 * cadenas
 * 
 * @param string: la cadena con la que se quiere comparar
 * @return un valor booleano dependiente de si la primera cadena es mas corta
 *         o más larga que la otra
 */
bool String::operator<(const String& string) const {
  return (Length() < string.Length() ? true : false); 
}

bool String::Exists(const char symbol) const {
  for (const auto& current_symbol : symbols_) {
    if (current_symbol == symbol) {
      return true;
    }
  }
  return false;
}

String String::Replace(const char symbol, const char symbol_to_replace) const {
  std::string new_symbols{symbols_};
  for (int i{0}; i < symbols_.length(); ++i) {
    if (symbols_[i] == symbol_to_replace) {
      new_symbols[i] = symbol;
    }
  }
  String new_string{new_symbols};
  return new_string;
}

/**
 * Se imprime la cadena mostrando cada símbolo por la salida en el orden 
 * correspondiente
 * 
 * @param output: por donde saldrá dicha información
 * @param string: la cadena a enviar por la salida
 * @return el output con la cadena ya recorrida
 */
std::ostream& operator<<(std::ostream& output, const String& string) {
  for (const auto& symbol : string.symbols_) {
    output << symbol;
  }
  return output;
}