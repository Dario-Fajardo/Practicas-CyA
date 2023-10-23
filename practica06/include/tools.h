/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
 * @brief Este archivo contiene varias funciones que podrían ser utiles para
 *        varios programas
 */
#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include "state.h"

typedef std::vector<std::set<State>> DfaStatesVector;

void Usage(int argc, char *argv[]);
bool Contains(std::string string, char character);

#endif