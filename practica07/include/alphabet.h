/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 22 Sept 2023
 * @brief Este programa es capaz de recibir por parámetros en nombre de un
 *        archivo y de el obtener una serie de cadenas de las cuales se podrá
 *        obtener información como su alfabeto, longitud, etc.
 */
#pragma once

#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>
#include <set>
#include <iostream>

class Alphabet {
 public:
  // Constructores
  Alphabet();
  Alphabet(const std::string& string_symbols);
  // Otros métodos
  void Include(char symbol);
  std::set<char> GetAlphabetSymbols() const { return alphabet_symbols_; }
  friend std::ostream& operator<<(std::ostream& output, const Alphabet& alphabet);
 private:
  std::set<char> alphabet_symbols_;
};

#endif