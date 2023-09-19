/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 17 Sept 2023
 * @brief Este programa lee un fichero con diversas notas para varios alumnos y
 *        muestra todas ellas para cada uno, además, en ejecución, permite hacer
 *        cambios en estas notas.
 */

#include "calificaciones_multiples.h"
#include <fstream>
#include <iostream>

/**
 * Constructor por defecto de la clase Lista
 */
Lista::Lista() {
  alumnos_ = {};
}

/**
 * Constructor de la clase Lista que utiliza un archivo para obtener datos
 * 
 * @param nombre_archivo: una string con el nombre del archivo desde el cual se
 *                        leerán los datos
 */
Lista::Lista(std::string nombre_archivo) {
  const char kEspacio{' '};
  std::ifstream fichero{nombre_archivo, std::ios_base::in};
  std::string linea;
  while(getline(fichero, linea)) {
    std::string id_alumno;
    std::string nota_alumno;
    int contador{0};
    for (const auto& caracter_actual : linea) { // Separamos y guardamos cada dato
      if (contador >= 13 && caracter_actual != kEspacio) {
        nota_alumno += caracter_actual;
      } else if (caracter_actual != kEspacio) {
        id_alumno += caracter_actual;
      }
      contador++;
    }
    identificadores_.insert(id_alumno);
    alumnos_.insert(std::pair<std::string, double>{id_alumno, stod(nota_alumno)});
  }
}

/**
 * Método de la clase Lista que permite imprimirla por pantalla
 */
void Lista::ImprimirLista() {
  for (const auto& id_actual : identificadores_) {
    std::cout << id_actual << " : ";
    for (const std::pair<std::string, double>& alumno_actual : alumnos_) {
        if (alumno_actual.first == id_actual) {
          std::cout << alumno_actual.second << " ";
        }
    }
    std::cout << std::endl;
  }
}

/**
 * Método de la clase lista que permite modificar una instancia de esta
 * añadiendo una calificación y/o alumnos nuevos a ella
 */
void Lista::InsertarCalificacion() {
  std::cout << "Indique el alumno al que le va a dar una nota: ";
  std::string alumno;
  std::cin >> alumno;
  double nota;
  do {
    std::cout << "\nAhora indique la nota numerica: ";
    std::cin >> nota;
  } while (nota < 0.0 || nota > 10.0);
  std::cout << std::endl;
  alumnos_.insert(std::pair<std::string, double>{alumno, nota});
  if (identificadores_.find(alumno) == identificadores_.end()) {
    identificadores_.insert(alumno);
  }
}

/**
 * Función que implementa el menú de la aplicación para facilitar su uso
 * 
 * @param lista_de_alumnos: un objeto Lista sobre el que el programa trabajará
 */
void Menu(Lista& lista_de_alumnos){
  int opcion;
  system("clear");
  lista_de_alumnos.ImprimirLista();
  std::cout << "\n[0] Salir del programa\n";
  std::cout << "[1] Editar Calificaciones\n";
  std::cout << "Elija una opción: \n";
  std::cin >> opcion;
  if (opcion == 0) {
    system("clear");
    exit(EXIT_SUCCESS);
  } else if (opcion == 1) {
    lista_de_alumnos.InsertarCalificacion();
  } else {
    std::cout << "\nError: Esa opción no existe\n";
    std::cout << "Saliendo del programa...\n";
    exit(EXIT_FAILURE);
  }
}

/**
 * Función que explica el funcionamiento del programa al usiario, además,
 * implementa el uso de --help como parámetro al ejecutar la aplicación para
 * obtener ayuda
 * 
 * @param argc: contador de parámetros de entrada al programa
 * @param argv: vector donde se encuentran los parámetros del programa
 */
void Usage(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Modo de empleo: ./calificaciones_multiples archivo.txt\n";
    std::cout << "Pruebe: ./calificaciones_multiples --help para más información\n";
    exit(EXIT_SUCCESS);
  } 
  
  std::string parameter{argv[1]};
  if (parameter == "--help" || parameter == "-h") {
    std::cout << "Este programa permite visualizar una lista de alumnos y\n";
    std::cout << "notas mostrando todas las notas de cada alumno,\n";
    std::cout << "además, podrá añadir notas y estudiantes\n\nEste ";
    std::cout << "programa requiere que se le pase como parámetro el nombre\n";
    std::cout << "de un archivo de texto con líneas compuestas por el ID de\n";
    std::cout << "un alumno separado por un espacio de su nota en este\n";
    std::cout << "formato:\n\n";
    std::cout << "alu0101564630 9.5\nalu0101234359 7.75\nalu0101010101 8.25\n";
    exit(EXIT_SUCCESS);
  }
}
