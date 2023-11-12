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

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <set>
#include <vector>
#include <algorithm>
#include "string.h"

class Language {
 public:
  // Constructores
  Language();
  Language(const std::set<std::string>& language_strings);
  // Getters
  std::set<std::string> GetLanguageStrings() const { return language_strings_; }
  // Otros métodos
  void Insert(const std::string& new_string);
  friend std::ostream& operator<<(std::ostream& output, const Language& string);
 private:
  std::set<std::string> language_strings_;
}; 

#endif