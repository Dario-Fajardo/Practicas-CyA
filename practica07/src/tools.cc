/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 6: Algoritmo de construcción de subconjuntos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 23 Sept 2023
 * @brief Este archivo contiene varias funciones que podrían ser útiles para
 *        varios programas
 */

#include "../include/tools.h"

/**
 * Función que comprueba los parámetros de entrada del main para saber si se
 * han introducido correctamente, además permite incluir una función --help
 * que le dará al usuario información detallada del uso de la aplicación al 
 * usuario
 * 
 * @param argc: número de parámetros pasados al programa
 * @param argv: todos los valores introducidos por línea de comandos
 */
void Usage(int argc, char *argv[]) {
  if (argc != 3) {
    if (argc == 2) {
      std::string parameter{argv[1]};
      if (parameter == "--help" || parameter == "-h") {
        std::cout << "\nEste programa recibe por consola el nombre de dos\n";
        std::cout << "archivos, el primero contiene la información de una\n";
        std::cout << "gramática independiente del contexto, esta gramática\n";
        std::cout << "será leída e interpretada y el programa la pasará a\n";
        std::cout << "forma normal de Chomsky, está nueva gramática\n";
        std::cout << "equivalente se escribirá en el fichero de salida\n";
        std::cout << "proporcionado por el usuario\n\n";
        std::cout << "El formato del archivo de entrada ha de ser el siguiente:\n\n";
        std::cout << "Una primera línea con el número de símbolos terminales\n";
        std::cout << "seguida de una línea para cada uno de ellos\n";
        std::cout << "Después la misma ejecución con cada uno de los símbolos\n";
        std::cout << "no terminales. Por último habra que incluir una línea\n";
        std::cout << "con el número de producciones de la gramática y por\n";
        std::cout << "supuesto, una línea para cada una de estas producciones\n";
        std::cout << "teniedo el símbolo no terminal de origen, un espacio\n";
        std::cout << "y la forma sentencial que se produce.\n\n";
        std::cout << "Teniendo todo esto en cuenta el archivo de entrada\n";
        std::cout << "deberia tener un formato similar al siguiente:\n\n";
        std::cout << "3\na\nb\nc\n3\nS\nX\nY\n13\nS aXbX\nS abX\nS aXb\nS ab\n";
        std::cout << "X aY\nX bY\nX a\nX b\nY aY\nY bY\na\nb\nc\n\n";
        std::cout << "IMPORTANTE: Este archivo de entrada no puede tener\n";
        std::cout << "producciones vacías tales como X & (salvo en el\n";
        std::cout << "símbolo inicial para indicar que se acepta la cadena\n";
        std::cout << "vacía) ni producciones unitarias tales como A B\n\n";
        exit(EXIT_SUCCESS);
      }
    }
    std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n";
    std::cout << "Pruebe: ./Grammar2CNF --help para más información\n";
    exit(EXIT_FAILURE);
  } 
}

/**
  * Permite buscar un caracter dentro de un std::string
  * 
  * @param string: la cadena en la que se va a buscar
  * @param character: el caracter a encontrar
  * 
  * @return true si se encuentra, false si no
  */
bool Contains(std::string string, char character) {
  for (const auto& actual_character : string) {
    if (actual_character == character) {
      return true;
    }
  }
  return false;
}