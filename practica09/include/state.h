/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 10 Nov 2023
 * @brief Este archivo declara la clase State para implementar un simulador
 * de máquinas de Turing
 */

class State {
 public:
  // Constructores
  State();
  State(int id);
  // Getters
  int GetId() const { return id_; }
  // Operadores
  bool operator<(const State& state) const;
 private:
  int id_;
};