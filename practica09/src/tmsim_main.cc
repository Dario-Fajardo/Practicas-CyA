#include <iostream>
#include "../include/turing_machine.h"

int main() {
  TuringMachine machine{"ejemplo.tm"};
  std::cout << machine;
  return 0;
}