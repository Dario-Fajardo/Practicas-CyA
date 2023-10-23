/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 5: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 13 Oct 2023
 * @brief En este archivo se declara la clase Estado, usada para componer la
 *        clase automata del archivo automaton.h
*/

#pragma once

#ifndef STATE_H
#define STATE_H

#include <set>
#include <map>
#include <string>

class State {
 public:
  // Constructores
  State();
  State(const std::string& text_line);
  // Getters
  int GetTransitionNumber() const { return transition_number_; }
  void SetTransitionNumber(int transition_number) { transition_number_ = transition_number; }
  std::multimap<char, int> GetTransitions() const { return transitions_; }
  void SetTransitions(std::multimap<char, int> transitions) { transitions_ = transitions; }
  bool GetIsFinal() const { return is_final_; }
  void SetIsFinal(bool is_final) { is_final_ = is_final; }
  int GetId() const { return id_; }
  void SetId(int id) { id_ = id; };
  // Otros métodos
  bool operator<(const State& state) const;
  bool operator==(const State& state) const;
 private:
  int transition_number_;
  std::multimap<char, int> transitions_;
  bool is_final_;
  int id_;
};

std::set<State> StateSetUnion(std::set<State> first_set, 
std::set<State> second_set);

#endif