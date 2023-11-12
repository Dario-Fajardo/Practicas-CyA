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
  tape_alphabet_ = {};
  input_alphabet_ = {};
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
  output << "Número de estados: " << machine.states_number_ << std::endl;
  output << "Estado inicial: " << machine.initial_state_ << std::endl;
  output << "Final states: { ";
  for (const auto& state_id : machine.final_states_) { // Imprmir estados
    output << state_id << " ";
  }
  output << "}" << std::endl;
  output << "Estados de la máquina: { ";
  for (const State& current_state : machine.machine_states_) {
    std::cout << current_state.GetId() << " ";
  }
  std::cout << "}" << std::endl;
  output << "Número de tuplas de la máquina: " << machine.transition_table_.size();
  output << std::endl; 
  for (const Transition& transition : machine.transition_table_) {
    output << "(" << transition.first.first << ", " << transition.first.second;
    output << ") ---> (" << std::get<0>(transition.second) << ", ";
    output << char(std::get<1>(transition.second)) << ", ";
    output << std::get<2>(transition.second) << ")" << std::endl;
  }
  return output;
}