/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 7: Gramáticas en Forma Normal de Chomsky
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 29 Oct 2023
 * @brief Este archivo declara la clase Grammar utilizada para simular el
 *        funcionamiento de una gramática independiente del contexto.
 */

#include <set>
#include <map>
#include <vector>
#include <fstream>
#include "string.h"

typedef std::multimap<char, String> ProductionSet;
typedef std::pair<char, String> Production;

class Grammar {
 public:
  // Constructores
  Grammar();
  Grammar(const std::string& file_name);
  Grammar(const Grammar& original_grammar);
  // Getters
  Alphabet GetAlphabet() const { return grammar_alphabet_; }
  std::set<char> GetNonTerminals() const  { return non_terminal_symbols_; }
  char GetStart() const { return starting_symbol_; }
  ProductionSet GetProductions() const { return productions_; }
  // Operadores
  friend std::ofstream& operator<<(std::ofstream& output, const Grammar& grammar);
  friend std::ostream& operator<<(std::ostream& output, const Grammar& grammar);
  // Otros métodos
  Grammar ChomskyNormalForm() const;
  char BiggestNonTerminal() const;
  bool NormalizedProductionExists(const Production& production) const;
 private:
  Alphabet grammar_alphabet_;
  std::set<char> non_terminal_symbols_;
  char starting_symbol_;
  ProductionSet productions_;
};

bool IsTerminal(const char symbol);