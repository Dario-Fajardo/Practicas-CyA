/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 9: Implementación de un simulador de máquinas de Turing
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 8 Nov 2023
 * @brief En este archivo se define la clase TuringMachine que usaremos para
 *        simular el funcionamiento de una máquina de turing en este programa
 */
#include "../include/turing_machine.h"

/**
 * Constructor por defecto de la clase TuringMachine por si se instancia sin dar
 * ningún valor
 */
TuringMachine::TuringMachine() {
  machine_states_ = {};
  // tape_alphabet_ = {};
  // input_alphabet_ = {};
  initial_state_ = 0;
  states_number_ = 0;
  final_states_ = {};
  transition_table_ = {};
}

/**
 * Constructor de la clase TuringMachine que construye dicho objeto a partir de
 * la entrada de un archivo .tm
 * 
 * @param file_name: un std::string con el nombre del fichero .tm
 */
TuringMachine::TuringMachine(const std::string& file_name) {
  std::string line;
  // Obtenemos el archivo
  std::ifstream file{file_name, std::ios_base::in};
  // Primera línea que contiene el número de estados
  getline(file, line);
  states_number_ = stoi(line);
  // Segunda línea que indica el estado de arranque
  getline(file, line);
  initial_state_ = stoi(line);
  // Tercera línea que indica los id's de los estados de aceptación
  getline(file, line);
  std::string current_number{""};
  // Recorremos toda la línea para obtener los estados de aceptación
  for (int i{0}; i < line.length(); i = i + 2) {
    final_states_.insert(static_cast<int>(line[i]) - 48);
  }
  // Línea 4 obtenemos el número de tuplas que componen la máquina
  getline(file, line);
  int transitions{stoi(line)};
  // En el resto de líneas obtenemos las tuplas de las transiciones
  int line_counter{0};
  std::set<int> existing_states; // Estados que ya han sido creados
  while(getline(file, line)) {
    // Se lee la transición y la incluimos en las transiciones de la máquina
    TransitionFirst first{std::make_pair(int(line[0]) - 48, line[2])}; 
    TransitionSecond second{std::make_tuple(line[4], Movement (line[6]), int(line[8]) - 48)};
    transition_table_.insert(std::make_pair(first, second));
    // Creamos estados y los incluímos en la máquina
    if (!existing_states.count(first.first)) {
      State new_state{first.first};
      existing_states.insert(first.first);
      machine_states_.insert(new_state);
    }
  }
  for (const auto& final_state_id : final_states_) {
    State final_state{final_state_id};
    machine_states_.insert(final_state);
  }
}

/**
 * Método usado para imprimir la información de una máquina de Turing por
 * consola
 * 
 * @param output: salida para el operador <<
 * @param machine: máquina de la cual iremos obteniendo información para
 *                 imprimirla
 * 
 * @return la salida modificada con la información
 */
std::ostream& operator<<(std::ostream& output, const TuringMachine& machine) {
  output << machine.states_number_ << std::endl;
  output << machine.initial_state_ << std::endl;
  for (const auto& state_id : machine.final_states_) { // Imprmir estados
    output << state_id << " ";
  }
  output << std::endl << machine.transition_table_.size() << std::endl;
  for (const Transition& transition : machine.transition_table_) {
    output << transition.first.first << transition.first.second;
    output << std::get<0>(transition.second) << char(std::get<1>(transition.second));
    output << std::get<2>(transition.second) << std::endl;
  }
  return output;
}

TransitionSecond TuringMachine::ComputationStep(const TransitionFirst& 
state_and_symbol) const {
  TransitionSecond tuple;
  for (const Transition& transition_pair : transition_table_) {
    if (state_and_symbol == transition_pair.first) {
      tuple = transition_pair.second;
    }
  }
  return tuple;
}

String TuringMachine::CreateTape(const String& tape_string) const {
  String tape{"$"};
  for (const auto& current_symbol : tape_string.GetSymbols()) {
    tape.InsertSymbol(current_symbol);
  }
  tape.InsertSymbol('$');
  return tape;
}

bool TuringMachine::Compute(const String& tape_string) const {
  bool stopped{false}; // Booleano que comprueba que la máquina no ha parado
  String tape = CreateTape(tape_string); // Cinta de la máquina
  char current_char{tape.GetSymbols()[1]}; // Carácter actual
  int current_state{initial_state_};
  int position{1}; // Posición inicial de la cabeza de lectura/escritura
  while (!stopped) {
    if (transition_table_.count(std::make_pair(current_state, current_char))) {
      TransitionSecond next_tuple{ComputationStep(std::make_pair(current_state, 
      current_char))};
      tape[position] = std::get<0>(next_tuple); // Símbolo a escribir
      if (std::get<1>(next_tuple) == Movement::L) {
        --position;
      } else if (std::get<1>(next_tuple) == Movement::R) {
        ++position;
      }
      current_state = std::get<2>(next_tuple);
      current_char = tape[position];
    } else {
      stopped = true;
    }
  }
  std::cout << tape << std::endl;
  if (final_states_.count(current_state)) {
    return true;
  }
  return false; 
}