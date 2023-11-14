/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 9: Implementación de un simulador de máquinas de Turing
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 8 Nov 2023
 * @brief En este archivo se declara la clase TuringMachine que usaremos para
 *        simular el funcionamiento de una máquina de turing en este programa
 */

#include <set>
#include <map>
#include <tuple>
#include <fstream>
#include "alphabet.h"
#include "state.h"
#include "string.h"

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

enum class Movement {
  L,
  R,
  S
};

typedef std::set<State> StateSet;
typedef std::pair<int, char> TransitionFirst;
typedef std::tuple<char, Movement, int> TransitionSecond;
typedef std::multimap<TransitionFirst, TransitionSecond> Table;
typedef std::pair<TransitionFirst, TransitionSecond> Transition;


class TuringMachine {
 public:
  // Constructores
  TuringMachine();
  TuringMachine(const std::string& file_name);
  // Getters
  StateSet GetMachineStates() { return machine_states_; }
  int GetInitial() { return initial_state_; }
  std::set<int> GetFinalStates() { return final_states_; }
  Table GetTransitions() { return transition_table_; }
  // Otros métodos
  TransitionSecond ComputationStep(const TransitionFirst& state_and_symbol) const;
  bool Compute(const String& tape_string) const;
  void PrintComputationStep(String& tape, int current_state, int position) const;
  friend std::ostream& operator<<(std::ostream& output, const TuringMachine& machine);
  String CreateTape(const String& tape_string) const;
 private:
  StateSet machine_states_;
  int initial_state_;
  int states_number_;
  std::set<int> final_states_;
  Table transition_table_;
};

#endif