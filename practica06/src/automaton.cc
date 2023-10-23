/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Oct 2023
 * @brief En este archivo se define la clase Automata, usada para simular
 *        el comportamiento de estos en el programa principal.
 */

#include "../include/automaton.h"

 /**
  * Constructor por defecto de la clase autómata, asigna valores vacíos por
  * si se llama al constructor sin parámetros 
  */
Automaton::Automaton() {
  automaton_alphabet_ = {};
  automaton_states_ = {};
  initial_state_ = {};
  final_states_ = {}; 
}

/**
 * Se utiliza este constructor por si se intenta instaciar un autómata usando un
 * archivo de texto (cosa que se hace en este programa)
 * 
 * @param file_name: un std::string con el nombre del archivo del que se leerá
 *                   toda la información del autómata
 */
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
  automaton_alphabet_.Include('&'); // Para evitar errores al comprobar los símbolos
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
      if (GetAlphabet().GetAlphabetSymbols().count(transition.first) == 0) {
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
  bool correct_transitions = true;
  std::set<int> states_ids;
  for (const State& current_state : automaton_states_) {
    states_ids.insert(current_state.GetId());
  }
  for (const State& current_state : automaton_states_) {
    for (std::pair<char, int> transition : current_state.GetTransitions()) {
      if (states_ids.count(transition.second) == 0) {
        std::cout << "Error: Todas las transiciones han de ser con estados que ";
        std::cout << "pertenezcan al autómata\n";
        exit(EXIT_FAILURE);
      }
    }
  }
  for (const State& current_state : automaton_states_) {
    for (const std::pair<char, int> transtion : current_state.GetTransitions()) {
      std::pair<int, char> transition_args {current_state.GetId(), transtion.first};
      TransitionPair automaton_transition{transition_args, transtion.second};
      transition_table_.insert(automaton_transition); 
    }   
  }
}

/**
 * Constructor de la clase autómata para el método que SubsetConstruction(), se
 * utiliza para crear un DFA usando la información obtenida en la función antes
 * nombrada, solo sirve para construir DFA.
 * 
 * @param transition: una tabla de transiciones
 * @param states: map que contiene la equivalencia entre un conjunto de estados
 *                del nfa usado en SubsetConstruction() y una id que será la del
 *                estado que defina dicho conjunto
 * @param initial_state: id del estado inicial
 * @param final_states: id's de los estados finales del autómata
 */
Automaton::Automaton(DfaTable transitions, DfaState states, int initial_state, 
std::set<int> final_states, Alphabet dfa_alphabet) {
  automaton_alphabet_ = dfa_alphabet;
  states_number_ = states.size();
  for (DfaStatePair state_info : states) {
    State new_state;
    new_state.SetId(state_info.second);
    if (new_state.GetId() == initial_state) {
      initial_state_ = new_state;
    }
    if (final_states.count(new_state.GetId()) != 0) {
      new_state.SetIsFinal(true);
      final_states_.insert(new_state);
    }
    std::multimap<char, int> new_state_transitions;
    for (const TransitionPair& transition : transitions) {
      if (new_state.GetId() == transition.first.first) {
        std::pair<char, int> new_state_transition{transition.first.second, 
        transition.second};
        new_state_transitions.insert(new_state_transition);
      }
    }
    new_state.SetTransitions(new_state_transitions);
    automaton_states_.insert(new_state);
  }
}


/**
 * Método que nos permite evaluar una cadena usando el autómata para ver si 
 * pertenece al lenguaje que este reconoce. Utiliza varios conjuntos de estados 
 * y la funcion Transition() para iterar sobre ellos y acabar consiguiendo los 
 * estados finales que se alcancan mediante dicha cadena
 * 
 * @param user_string: la cadena del alfabeto del autómata que ha introducido
 *                     el usuario mediante un archivo de texto
 * 
 * @return los estados en los que termina el autómata tras itroducir la cadena
 *         este conjunto nos servirá para verificar posteriormente si alguno
 *         de ellos es un estado de aceptación usando la función Accept()
 */
std::set<State> Automaton::Evaluate(const String& user_string) {
  std::set<State> iteration_states{initial_state_};
  for (const auto& current_symbol : user_string.GetSymbols()) {
    std::set<State> auxiliar_set;
    std::set<State> clausure;
    for (const State& current_iteration_state : iteration_states) {
      auxiliar_set = StateSetUnion(auxiliar_set, 
                                  Transition(current_symbol, 
                                  current_iteration_state));
      for (const State& auxiliar_state_set : auxiliar_set) {
        clausure = EClausure(auxiliar_state_set);
        for (const State& clausure_state : clausure) {
          auxiliar_set.insert(clausure_state);
        }
      }
    }
    iteration_states = auxiliar_set;
  }
  return iteration_states;
}

/**
 * Método clave para el funcionamiento de Evaluate, ya que permite saber a que
 * estados se transiciona con cierto símbolo.
 * 
 * @param symbol: símbolo con el que se realizará la transición al siguiente
 *                conjunto de estados
 * @param current: estado en el que nos encontramos y el cual tiene la 
 *                 información necesaria para completar la transición
 * 
 * @return un conjunto de estados al que se llega tras la transición
 */
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

std::set<State> Automaton::Transition(const char& symbol, const std::set<State>& current) {
  std::set<State> next_states;
  for (const State& current_state : current) {
    for (const std::pair<char, int> transition : current_state.GetTransitions()) {
      if (transition.first == symbol) {
        for (const State& next_state : automaton_states_) {
          if (next_state.GetId() == transition.second) {
            next_states.insert(next_state);
          }
        }
      }
    }
  }
  return next_states;
}

/**
 * Recorre todas las trancisiones del estado current y devuelve todas aquellas
 * a las que se puede llegar consumiendo 0 símbolos, es decir, él mismo y todas
 * las posibles conexiones de épsilon transiciones
 * 
 * @param current: este estado se obtiene desde la fución evaluate
 * 
 * @return el conjunto de estados al que se puede llegar, utilizado en la
 *         función evaluate para NFA's
 */
std::set<State> Automaton::EClausure(const State& current) {
  std::set<State> e_clausure;
  e_clausure.insert(current);
  for (const std::pair<char, int>& transition : current.GetTransitions()) {
    if (transition.first == '&') {
      for (const State& transition_state : automaton_states_) {
        if (transition_state.GetId() == transition.second) {
          e_clausure = StateSetUnion(e_clausure, EClausure(transition_state));
        }
      }
    }
  }
  return e_clausure;
}

std::set<State> Automaton::EClausure(const std::set<State>& state_set) {
  std::set<State> final_e_clausure;
  for (const State& current_state : state_set) {
    std::set<State> current_e_clausure{EClausure(current_state)};
    for (const State& e_clausure_state : current_e_clausure) {
      final_e_clausure.insert(e_clausure_state);
    }
  }
  return final_e_clausure;
}

/**
 * Sencillo método que simplemente verifica que un conjunto de estados contiene
 * al menos uno de aceptación, necesario para completar el proceso de aceptación
 * de una cadena. Se recorren ambos conjuntos en busca de la existencia de alguno
 * en el conjunto de estados finales
 * 
 * @param evaluation_states: estados finales devueltos por la función Evaluate()
 * 
 * @return true si la cadena es aceptada, false si no
 */
bool Automaton::Accept(const std::set<State>& evaluation_states) {
  for (const State& current_state : evaluation_states) {
    if (final_states_.find(current_state) != final_states_.end()) {
      return true;
    }
  }
  return false;
}

/**
 * Método que implementa el algoritmo de construcción de subconjuntos, usado
 * para crear un DFA a partir de un NFA
 * 
 * @return un DFA construido a partir de una tabla de transiciones y una tabla
 *         de equivalencias entre cierto conjunto de estados y su id como nuevo
 *         estado
*/
Automaton Automaton::SubsetConstruction() {
  DfaTable tran_dfa;
  DfaStatePair initial_pair{EClausure(initial_state_), 0};
  Alphabet dfa_alphabet;
  DfaState dfa_states{initial_pair};
  int initial_state;
  std::set<int> final_states;
  std::set<int> marked;
  for (const auto& iteration_pair : dfa_states) {
    if (!marked.count(iteration_pair.second)) {
      marked.insert(iteration_pair.second);
      for (const auto& symbol : automaton_alphabet_.GetAlphabetSymbols()) {
        if (symbol != '&') {
          dfa_alphabet.Include(symbol);
          DfaStatePair new_pair;
          new_pair.first = EClausure(Transition(symbol, iteration_pair.first));
          if (dfa_states.find(new_pair.first) == dfa_states.end()) {
            new_pair.second = iteration_pair.second + 1;
            marked.erase(new_pair.second);
            dfa_states.insert(new_pair);
            for (const State& pair_state : new_pair.first) {
              if (pair_state.GetIsFinal()) {
                final_states.insert(new_pair.second);
              }
            }
          } else {
            for (DfaStatePair pair : dfa_states) {
              if (new_pair.first == pair.first) {
                new_pair.second = pair.second;
              }
            }
          }
          std::pair<int, char> transition_first{iteration_pair.second, symbol};
          TransitionPair full_transition{transition_first, new_pair.second};
          tran_dfa.insert(full_transition);
        }
      }
    }
  }
  for (const auto& iteration_pair : dfa_states) {
    if (!marked.count(iteration_pair.second)) {
      marked.insert(iteration_pair.second);
      for (const auto& symbol : automaton_alphabet_.GetAlphabetSymbols()) {
        if (symbol != '&') {
          dfa_alphabet.Include(symbol);
          DfaStatePair new_pair;
          new_pair.first = EClausure(Transition(symbol, iteration_pair.first));
          if (dfa_states.find(new_pair.first) == dfa_states.end()) {
            new_pair.second = iteration_pair.second + 1;
            marked.erase(new_pair.second);
            dfa_states.insert(new_pair);
            for (const State& pair_state : new_pair.first) {
              if (pair_state.GetIsFinal()) {
                final_states.insert(new_pair.second);
              }
            }
          } else {
            for (DfaStatePair pair : dfa_states) {
              if (new_pair.first == pair.first) {
                new_pair.second = pair.second;
              }
            }
          }
          std::pair<int, char> transition_first{iteration_pair.second, symbol};
          TransitionPair full_transition{transition_first, new_pair.second};
          tran_dfa.insert(full_transition);
        }
      }
    }
  }
  Automaton dfa{tran_dfa, dfa_states, initial_state, final_states, dfa_alphabet};
  return dfa;
}

/**
 * Lee los datos de un autómata y los imprime en un archivo
 * 
 * @param output_file: archivo en el que se imprimirá la información del autómata
*/
void Automaton::PrintInFile(std::ofstream& output_file) {
  // Alfabeto
  for (const auto& symbol : automaton_alphabet_.GetAlphabetSymbols()) {
    if (symbol != '&') {
      output_file << symbol << " ";
    }
  }
  output_file << std::endl;
  // Número de estados
  output_file << states_number_ << std::endl;
  // ID del estado de arranque
  output_file << initial_state_.GetId() << std::endl;
  // Transiciones y estados
  for (const State& state : automaton_states_) {
    output_file << state.GetId() << " " << state.GetIsFinal() << " ";
    output_file << state.GetTransitions().size();
    for (const std::pair<char, int>& transition : state.GetTransitions()) {
      output_file << " " << transition.first << " " << transition.second;
    }
    output_file << std::endl;
  }
}