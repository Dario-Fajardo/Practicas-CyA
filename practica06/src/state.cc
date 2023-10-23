/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 5: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 13 Oct 2023
 * @brief En este archivo se define la clase Estado, usada para componer la
 *        clase automata del archivo automaton.h
*/

#include "../include/state.h"

/**
 * Constructor por defecto de la clase State por si se intenta instanciar sin 
 * pasar parámetros
 */
State::State() {
  transition_number_ = 0;
  transitions_ = {};
  is_final_ = false;
  id_ = 0;
}

/**
 * Constructor de la clase State a partir de una línea de texto, cada línea del
 * archivo que el usuario pasa al programa representa un estado, simplemente
 * se utiliza esta para construirlo
 * 
 * @param text_line: línea de texto que contiene toda la información para crear
 *                   un estado de un autómata
 */
State::State(const std::string& text_line) {
  id_ = int(text_line[0]) - 48;
  is_final_ = text_line[2] == '1' ? true : false;
  transition_number_ = text_line[4];
  if (transition_number_ > 0) {
    for (int i = 6; i < text_line.length(); i += 4) {
      int transition_state_id{int(text_line[i + 2]) - 48};
        std::pair<char, int> transition{text_line[i], transition_state_id};
        transitions_.insert(transition);
    }
  }
}

/**
 * Operador utilizado para que al crear conjuntos se puedan ordenar de menor a 
 * mayor según el número identificador
 * 
 * @param state: el estado con el que se va a comparar
 */
bool State::operator<(const State& state) const {
  return id_ < state.id_;
}

bool State::operator==(const State& state) const {
  return id_ == state.id_;
}


/**
 * Función no perteneciente a la clase utilizada en el método Evaluate de la 
 * clase Automaton, esta permite unir dos estados en uno solo (tal y como hace
 * la unión matemática de conjuntos) ya que se necesita en la función que
 * define un autómata
 * 
 * @param first_set, second_set: ambos conjuntos serán iterados y se insertarán
 *                               sus elementos en otro
 * 
 * @return un conjunto de estado resultado de la unión de los otros dos
 */
std::set<State> StateSetUnion(std::set<State> first_set, 
std::set<State> second_set) {
  std::set<State> final_set;
  for (const State& actual_state : first_set) {
    final_set.insert(actual_state);
  }
  for (const State& actual_state : second_set) {
    final_set.insert(actual_state);
  }
  return final_set;
}