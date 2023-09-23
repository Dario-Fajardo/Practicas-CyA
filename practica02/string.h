/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
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
  // Otros métodos
  int Length() const;
  String Reverse();
  bool operator<(const String& string) const;
  Language Prefixes();
  Language Sufixes();
  friend std::ostream& operator<<(std::ostream& output, const String& string);

 private:
  std::string symbols_;
  Alphabet alphabet_symbols_;
};

#endif