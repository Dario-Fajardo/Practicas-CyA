#include <iostream>
#include "../include/turing_machine.h"

int main() {
  TuringMachine machine{"ejemplo.tm"};
  std::cout << machine; 
  std::ifstream tape_file{"input.tape", std::ios_base::in};
  std::string tape_string;
  getline(tape_file, tape_string);
  machine.Compute(tape_string);
  return 0;
}