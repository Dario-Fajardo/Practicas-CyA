/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 5: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 13 Oct 2023
 * @brief En este archivo se declara la clase Automata, usada para simular
 *        el comportamiento de estos en el programa principal.
 */
#pragma once

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "alphabet.h"
#include "state.h"
#include "string.h"
#include "tools.h"
#include <fstream>
#include <vector>

typedef std::multimap<std::pair<int, char>, int> NfaTable;
typedef std::map<std::pair<int, char>, int> DfaTable;
typedef std::pair<std::pair<int, char>, int> TransitionPair;
typedef std::map<std::set<State>, int> DfaState;
typedef std::pair<std::set<State>, int> DfaStatePair;

class Automaton {
 public:
  // Constructores
  Automaton();
  Automaton(const std::string& file_name);
  Automaton(DfaTable transitions, DfaState states, int initial_state, 
  std::set<int> final_states, Alphabet alphabet);
  // Getters
  Alphabet GetAlphabet() { return automaton_alphabet_; }
  int GetNumberOfStates() { return states_number_; }
  std::set<State> GetStates() { return automaton_states_; }
  State GetInitial() { return initial_state_; }
  std::set<State> GetFinal() { return final_states_; }
  // Otros métodos
  std::set<State> Evaluate(const String& user_string);
  std::set<State> Transition(const char& symbol, const State& current);
  std::set<State> Transition(const char& symbol, const std::set<State>& current);
  std::set<State> EClausure(const State& current);
  std::set<State> EClausure(const std::set<State>& state_set);
  bool Accept(const std::set<State>& evaluation_states);
  Automaton SubsetConstruction();
  void PrintInFile(std::ofstream& output_file);
 private:
  Alphabet automaton_alphabet_;
  int states_number_;
  std::set<State> automaton_states_;
  State initial_state_;
  std::set<State> final_states_;
  NfaTable transition_table_;
};

inline void printstateset(const std::set<State>& set) {
  std::cout << "{";
  for (const State& a : set) {
    std::cout << a.GetId() << " ";
  }
  std::cout << "}\n";
}

#endif