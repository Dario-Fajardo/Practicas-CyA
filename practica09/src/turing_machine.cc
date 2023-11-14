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
  if (!file.good()) { // Comprobamos que el archivo se ha leído sin errores
    std::cout << "[ERROR]: no se puede acceder al archivo, compruebe que exista\n";
    exit(EXIT_FAILURE);
  }
  // Primera línea que contiene el número de estados
  getline(file, line);
  if (line.find(' ') != std::string::npos) { // Comprobamos el formato
    std::cout << "[ERROR]: No puede haber más de un número de estados\n";
    exit(EXIT_FAILURE);
  }
  states_number_ = stoi(line);
  // Segunda línea que indica el estado de arranque
  getline(file, line);
  if (line.find(' ') != std::string::npos) { // Comprobamos el formato
    std::cout << "[ERROR]: No puede haber más de un estado de arranque\n";
    exit(EXIT_FAILURE);
  }
  initial_state_ = stoi(line);
  // Tercera línea que indica los id's de los estados de aceptación
  getline(file, line);
  std::string current_number{""};
  // Recorremos toda la línea para obtener los estados de aceptación
  for (int i{0}; i < line.length(); i = i + 2) {
    if (!std::isdigit(line[i])) {
      std::cout << "[ERROR]: los estados solo pueden ser nombrados con números\n";
      exit(EXIT_FAILURE);
    }
    final_states_.insert(static_cast<int>(line[i]) - 48);
  }
  // Línea 4 obtenemos el número de tuplas que componen la máquina
  getline(file, line);
  if (line.find(' ') != std::string::npos) { // Comprobamos el formato
    std::cout << "[ERROR]: No puede haber más de un número de tuplas\n";
    exit(EXIT_FAILURE);
  }
  int transitions{stoi(line)};
  // En el resto de líneas obtenemos las tuplas de las transiciones
  int line_counter{0};
  std::set<int> existing_states; // Estados que ya han sido creados
  while(getline(file, line)) {
    if (line.size() != 9) { // Comprobamos el formato de las tuplas
      std::cout << "[ERROR]: Formato de las tuplas incorrecto\n";
      exit(EXIT_FAILURE);
    }
    // Se lee la transición y la incluimos en las transiciones de la máquina
    TransitionFirst first{std::make_pair(int(line[0]) - 48, line[2])}; 
    TransitionSecond second{std::make_tuple(line[4], Movement (line[6]), 
    int(line[8]) - 48)};
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

/**
 * Este método de la clase TuringMachine se ocupa de realizar los pasos de
 * computo, es decir, al pasarle un símbolo y un estado, devolverá
 * una tripleta con un símbolo para escribir, un movimiento y un estado al que
 * se transicionara
 * 
 * @param state_and_symbol: estado y símbolo que se le pasan al método
 * 
 * @return una tripleta con un símbolo para escribir en la cinta de la máquina,
 *         un movimiento y un estado, estas equivalencias se obtienen del
 *         atributo transition_table_ de la clase TuringMachine
 */
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

/**
 * Esta función coge una cadena de entrada y simula ser la cinta de la máquina
 * de Turing
 * 
 * @param tape_string: cadena de entrada para la cinta
 * 
 * @return una cadena con símbolos blancos que simula ser la cinta
 */
String TuringMachine::CreateTape(const String& tape_string) const {
  String tape{"$"};
  for (const auto& current_symbol : tape_string.GetSymbols()) {
    tape.InsertSymbol(current_symbol);
  }
  tape.InsertSymbol('$');
  return tape;
}

/**
 * Método que computa una cadena con una máquina de Turing de la clase
 * TuringMachine, se itera comprobando las transiciones de la máquina e imprimimos
 * cada paso de cómputo con el método PrintComputationStep()
 * 
 * @param tape_string: la cadena a computar, importante recalcar de que esto
 *                     no se trata de la cinta de la máquina, esta se va a
 *                     insertar dentro de otra cadena que simulará la cinta
 * 
 * @return true si se acepta, false si no
 */
bool TuringMachine::Compute(const String& tape_string) const {
  bool stopped{false}; // Booleano que comprueba que la máquina no ha parado
  String tape = CreateTape(tape_string); // Cinta de la máquina
  char current_char{tape.GetSymbols()[1]}; // Carácter actual
  int current_state{initial_state_};
  int position{1}; // Posición inicial de la cabeza de lectura/escritura
  PrintComputationStep(tape, current_state, position); // Imprimimos situación inicial
  int iteration_counter{0};
  while (!stopped) {
    if (iteration_counter > 100) {
      return false;
    }
    if (transition_table_.count(std::make_pair(current_state, current_char))) {
      // Si la transición existe
      TransitionSecond next_tuple{ComputationStep(std::make_pair(current_state, 
      current_char))};
      tape[position] = std::get<0>(next_tuple); // Símbolo a escribir

      // Comprobamos el movimiento a realizar por la cabeza de lectura/escritura
      if (char(std::get<1>(next_tuple)) == 'L') {
        if (position != 0) { // Simulamos que los símbolos blancos son infinitos
          --position; // Posición a la izquierda
        }
      } else if (char(std::get<1>(next_tuple)) == 'R') {
        if (position != tape.Length()) {
          ++position; // Posición a la derecha
        }
      }

      current_state = std::get<2>(next_tuple); // Siguiente estado
      PrintComputationStep(tape, current_state, position); // Imprimimos el paso
      current_char = tape[position]; // Siguiente símbolo
    } else {
      stopped = true; // Se para la máquina
    }
    ++iteration_counter;
  }
  // Comprobamos si la cadena se rechaza o se acepta y retornamos el valor
  if (final_states_.count(current_state)) {
    return true;
  }
  return false; 
}

/**
 * Usada para imprimir los pasos de cómputo que vaya realizando el método
 * Compute(), el formato de la impresión simula el de la cinta de una máquina de
 * Turing, con símbolos blancos a sus lados, y en la posición de la cabeza de
 * lectura escritura encontramos información sobre el estado actual de la máquina
 * 
 * @param tape: cinta de la máquina
 * @param current_state: estado actual para imprimirlo
 * @param position: información sobre la posición en la que esta la cabeza de 
 *                  lectura/escritura de la máquina
 */
void TuringMachine::PrintComputationStep(String& tape, int current_state, 
int position) const {
  for (int i{0}; i < position ; ++i) { // Imprimos hasta la posicion del estado
    std::cout << tape[i];
  }
  std::cout << " q" << current_state << " "; // Imprimimos el estado
  for (int i{position}; i < tape.Length(); ++i) { // Terminamos de imprimir
    std::cout << tape[i];
  }
  std::cout << std::endl;
}