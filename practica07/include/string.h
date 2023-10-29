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

#ifndef STRING_H
#define STRING_H

#include <string>
#include <iostream>
#include <algorithm>
#include "language.h"
#include "alphabet.h"

class Language;

class String {
 public:
  // Constructores
  String();
  String(const std::string& symbols);
  // Getters
  Alphabet GetAlphabet() const { return alphabet_symbols_; }
  std::string GetSymbols() const { return symbols_; }
  // Otros métodos
  int Length() const;
  String Reverse();
  bool operator<(const String& string) const;
  bool Exists(const char symbol) const;
  String Replace(const char symbol, const char symbol_to_replace) const;
  Language Prefixes();
  Language Sufixes();
  friend std::ostream& operator<<(std::ostream& output, const String& string);

 private:
  std::string symbols_;
  Alphabet alphabet_symbols_;
};

#endif