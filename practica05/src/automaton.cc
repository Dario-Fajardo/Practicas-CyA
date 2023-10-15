/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 5: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 13 Oct 2023
 * @brief En este archivo se define la clase Automata, usada para simular
 *        el comportamiento de estos en el programa principal.
 */

#include "../include/automaton.h"

Automaton::Automaton() {
  automaton_alphabet_ = {};
  automaton_states_ = {};
  initial_state_ = {};
  final_states_ = {}; 
}

Automaton::Automaton(const std::string& file_name) {
  std::ifstream file{file_name, std::ios_base::in};
  std::string line{};
  getline(file, line);
  for (const auto& actual_character : line) {
    if (actual_character != ' ') {
      if (actual_character == '&') {
        std::cout << "Error: El caracter & no puede ser utilizado ya que en este ";
        std::cout << "programa es utilizado para representar la cadena vacía.\n";
        exit(EXIT_FAILURE);
      }
      automaton_alphabet_.Include(actual_character);
    }
  }
  getline(file, line);
  states_number_ = stoi(line);
  int initial_id;
  if (states_number_ >= 1) {
    getline(file, line);
    if ((Contains(line, ' ')) && line.length() > 2) {
      std::cout << "Error: Solo puede existir un único estado inicial\n";
      exit(EXIT_FAILURE);
    }
    initial_id = stoi(line);
  }
  int line_counter{0};
  while(getline(file, line)) {
    State new_state{line};
    automaton_states_.insert(new_state);
    if (new_state.GetId() == initial_id) {
      initial_state_ = new_state;
    }
    if (new_state.GetIsFinal()) {
      final_states_.insert(new_state);
    }
    for (std::pair<char, int> transition : new_state.GetTransitions()) {
      if (automaton_alphabet_.GetAlphabetSymbols().find(transition.first) == 
      automaton_alphabet_.GetAlphabetSymbols().end()) {
        std::cout << "Error: Los símbolos de las transiciones han de ";
        std::cout << "pertenecer al alfabeto sobre el que se forma el lenguaje ";
        std::cout << "que reconoce el autómata\n";
        exit(EXIT_FAILURE);
      }
    }
    ++line_counter;
  }
  if (line_counter < 0 || line_counter > states_number_) {
    std::cout << "Error: El número de líneas que definen estados en el archivo de ";
    std::cout << "entrada ha de ser igual al número de estados que tiene el ";
    std::cout << "autómata\n";
    exit(EXIT_FAILURE);
  }
  bool correct_transitions = false;
  for (const State& current_state : automaton_states_) {
    for (std::pair<char, int> transition : current_state.GetTransitions()) {
      if (current_state.GetId() == transition.second) {
        correct_transitions = true;
      }
    }
    if (correct_transitions == false) {
      std::cout << "Error: Todas las transiciones han de ser con estados que ";
      std::cout << "pertenezcan al autómata\n";
      exit(EXIT_FAILURE);
    } 
  }
}
std::set<State> Automaton::Evaluate(const String& user_string) {
  std::set<State> iteration_states{initial_state_};
  for (const auto& current_symbol : user_string.GetSymbols()) {
    std::set<State> auxiliar_state_saving_set;
    for (const State& current_iteration_state : iteration_states) {
      auxiliar_state_saving_set = StateSetUnion(auxiliar_state_saving_set, 
                                  Transition(current_symbol, current_iteration_state));
    }
    iteration_states = auxiliar_state_saving_set;
  }
  return iteration_states;
}

std::set<State> Automaton::Transition(const char& symbol, const State& current) {
  std::set<State> next_states;
  for (const std::pair<char, int> transition : current.GetTransitions()) {
    if (transition.first == symbol) {
      for (const State& next_state : automaton_states_) {
        if (next_state.GetId() == transition.second) {
          next_states.insert(next_state);
        }
      }
    }
  }
  return next_states;
}

bool Automaton::Accept(const std::set<State>& evaluation_states) {
  for (const State& current_state : evaluation_states) {
    if (final_states_.find(current_state) != final_states_.end()) {
      return true;
    }
  }
  return false;
}