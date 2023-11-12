/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 10 Nov 2023
 * @brief Este archivo define la clase State para implementar un simulador
 * de máquinas de Turing
 */
#include "../include/state.h"

/**
 * Constructor por defecto de la clase State, por si acaso se intenta instanciar
 * sin pasar ningún parámetro
 */
State::State() {
  id_ = 0;
}

/**
 * Constructor parametrizado de la clase State, usado para crear estados de una 
 * máquina de  Turing a partir de un id dado
 * 
 * @param id: el identificador del estado
 */
State::State(int id) {
  id_ = id;
}

/**
 * Sobrecarga del operador < para la clase State, usado para ordenar los objetos
 * State en un set
 * 
 * @param state: estado con el que se va a comparar el id
 * 
 * @return true si el id es mayor, false si es menor
 */
bool State::operator<(const State& state) const {
  return this->id_ < state.id_;
}