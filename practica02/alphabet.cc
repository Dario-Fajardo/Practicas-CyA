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

#include "alphabet.h"
#include <string>

/**
 * Constructor por defecto por si se crea un objeto sin indicar ningún valor
 */
Alphabet::Alphabet() {
  alphabet_symbols_ = {};
}

/**
 * Constructor parametrizado, usado posteriormente para obtener el conjunto de
 * símbolos de una cadena
 * 
 * @param string_symbols: un std::string obtenido de un objeto String para poder
 *                        construir su alfabeto
 */
Alphabet::Alphabet(const std::string& string_symbols) {
  if (string_symbols != "&") {
    for (const auto& symbol : string_symbols) {
        alphabet_symbols_.insert(symbol);
    }
  } else {
    alphabet_symbols_ = {};
  }
}

/**
 * Usada para editar los alfabetos sin tener acceso a sus atributos
 * 
 * @param symbol: el símbolo que se va a incluir en este alfabeto
 */
void Alphabet::Include(char symbol) {
  alphabet_symbols_.insert(symbol);
}

/**
 * Se imprime el alfabeto como un conjunto cualquiera, entre {} y con sus
 * elementos separados por coma y espacio
 * 
 * @param output: la salida por la que se imprimirá
 * @param alphabet: el alfabeto a imprimir
 */
std::ostream& operator<<(std::ostream& output, const Alphabet& alphabet) {
  int iterator{1};
  output << "{";
  for (const auto& actual_symbol : alphabet.alphabet_symbols_) {
    output << actual_symbol;
    if (iterator != alphabet.alphabet_symbols_.size()) {
      output << ", ";
    }
    iterator++;
  }
  output << "}";
  return output;
}