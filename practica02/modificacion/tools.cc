/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
 * @brief Este programa es capaz de recibir por parámetros en nombre de un
 *        archivo y de el obtener una serie de cadenas de las cuales se podrá
 *        obtener información como su alfabeto, longitud, etc.
 */
#include "tools.h"

/**
 * Función que explica el funcionamiento del programa al usiario, además,
 * implementa el uso de --help como parámetro al ejecutar la aplicación para
 * obtener ayuda
 * 
 * @param argc: contador de parámetros de entrada al programa
 * @param argv: vector donde se encuentran los parámetros del programa
 */
void Usage(int argc, char* argv[]) {
  if (argc < 4 || argc > 5) {
    if (argc == 2) {
      std::string parameter{argv[1]};
      if (parameter == "--help" || parameter == "-h") {
        std::cout << "\nEste programa recibe por parámetro un archivo de entrada y\n";
        std::cout << "uno de salida, en el primero debe de haber una serie de\n";
        std::cout << "cadenas separadas por un retorno de carro, en el de salida se\n";
        std::cout << "guardará cierta información sobre estas cadenas, para ello\n";
        std::cout << "el programa ha de ejecutarse con un tercer parámetro que\n";
        std::cout << "será el opcode:\n1) Alfabeto\n2) Longitud\n3) Inversas\n4) ";
        std::cout << "prefijos\n5) Sufijos\n\nEste opcode le dirá al programa que";
        std::cout << " información guardar en el archivo de salida.\n\nFormato del";
        std::cout << " archivo de entrada:\n\nabbab\n6793836\nhola\n\n";
        exit(EXIT_SUCCESS);
      }
    }
    if (argc != 5 && atoi(argv[3]) == 6) {
      std::cout << "Para este opcode necesita introducir un segundo archivo de entrada";
      std::cout << "\ncuyas cadenas serán concatenadas con el primer archivo\n";
      std::cout << "Pruebe: ./p02_cadenas entrada.txt salida.txt opcode entrada2.txt";
    }
    std::cout << "Modo de empleo: ./p02_cadenas entrada.txt salida.txt opcode\n";
    std::cout << "Pruebe: ./p02_cadenas --help para más información\n";
    exit(EXIT_FAILURE);
  } 
}