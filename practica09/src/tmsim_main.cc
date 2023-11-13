#include <iostream>
#include "../include/turing_machine.h"

int main() {
  TuringMachine machine{"ejemplo_error.tm"};
  std::cout << machine; 
  std::ifstream tape_file{"input.tape", std::ios_base::in};
  std::string tape_string;
  getline(tape_file, tape_string);
  if (machine.Compute(tape_string)) {
    std::cout << "ACEPTADA" << std::endl;
  } else {
    std::cout << "RECHAZADA" << std::endl;
  }
  return 0;
}