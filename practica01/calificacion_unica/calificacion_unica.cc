/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 1: Contenedores Asociativos
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 16 Sept 2023
 * @brief Este programa lee un fichero con diversas notas para varios alumnos y
 *        muestra la más alta para cada uno, además, en ejecución, permite hacer
 *        cambios en estas notas.
 */
#include "calificacion_unica.h"
#include <iostream>
#include <fstream>

/**
 * Lee las calificaciones del archivo y las organiza en un map que retorna
 * 
 * @param nombre_archivo: el nombre del dicho archivo
 * @return un mapa con pares de alumno y nota más alta
 */
std::map<std::string, double> LeerCalificaciones(const std::string& nombre_archivo) {
  const char kEspacio{' '};
  std::ifstream fichero{nombre_archivo, std::ios_base::in};
  std::map<std::string, double> calificaciones;
  std::string linea;
  while(getline(fichero, linea)) { // Recorremos el archivo línea por línea
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
    double nota_real{stod(nota_alumno)};
    if (nota_real > calificaciones[id_alumno]) { // Si es la mayor, la incluimos
      calificaciones[id_alumno] = nota_real;
    }
  }
  return calificaciones; // Retornamos la lista con los alumnos y su mayor nota
}

/**
 * Una función que imprime maps
 * 
 * @param lista: el mapa a imprimir
 */
void ImprimirCalificaciones(const std::map<std::string, double>& lista) {
  for (const auto& pair : lista) { // Recorremos par por par el map
    std::cout << pair.first << " " << pair.second << std::endl;
  }
}

/**
 * Función que nos permite editar las notas de un alumno o añadir nuevos 
 * 
 * @param lista: la lista de alumnos
 */
void InsertarCalificacion(std::map<std::string, double>& lista) {
    std::string alumno;
    std::cout << "Introduzca el ID del alumno al que quiere modificar la nota\n";
    std::cin >> alumno;
  double nota;
  do {
    std::cout << "\nAhora indique la nota numérica: ";
    std::cin >> nota;
  } while (nota < 0.0 || nota > 10.0);
    lista[alumno] = nota;
}

/**
 * Función utilizada para imprimir el modo de uso del programa y para añadir una
 * opción de pedir información mediante "--help"
 * 
 * @param argc: contador de parametros pasados al programa
 * @param argv: vector con todos los parametros en forma de string
 */
void Usage(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Modo de empleo: ./calificacion_unica archivo.txt\n";
    std::cout << "Pruebe: ./calificacion_unica --help para más información\n";
    exit(EXIT_SUCCESS);
  } 
  
  std::string parameter{argv[1]};
  if (parameter == "--help" || parameter == "-h") {
    std::cout << "Este programa permite visualizar una lista de alumnos y\n";
    std::cout << "notas mostrando siempre la mayor nota de cada alumno,\n";
    std::cout << "además, podrá editarlas y añadir nuevos alumnos.\n\nEste ";
    std::cout << "programa requiere que se le pase como parámetro el nombre\n";
    std::cout << "de un archivo de texto con líneas compuestas por el ID de\n";
    std::cout << "un alumno separado por un espacio de su nota en este\n";
    std::cout << "formato:\n\n";
    std::cout << "alu0101564630 9.5\nalu0101234359 7.75\nalu0101010101 8.25\n";
    exit(EXIT_SUCCESS);
  }
}

/**
 * Función que implementa el menú del programa
 * 
 * @param lista: lista de alumnos con la que se va a trabajar
 */
void Menu(std::map<std::string, double>& lista){
  int opcion;
  system("clear");
  ImprimirCalificaciones(lista);
  std::cout << "\n[0] Salir del programa\n";
  std::cout << "[1] Editar Calificaciones\n";
  std::cout << "Elija una opción: \n";
  std::cin >> opcion;
  if (opcion == 0) {
    system("clear");
    exit(EXIT_SUCCESS);
  } else if (opcion == 1) {
    InsertarCalificacion(lista);
  } else {
    std::cout << "\nError: Esa opción no existe\n";
    std::cout << "Saliendo del programa...\n";
    exit(EXIT_FAILURE);
  }
}