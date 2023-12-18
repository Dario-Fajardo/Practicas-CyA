/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos la definición de la clase PointSet y la
*        lógica del algoritmo que calculará el EMST
*/
#include "../include/point_set.h"

namespace emst {
  /**
   * Constructor de la clase PointSet a partir de un vector con todos los puntos de un conjunto
   * de puntos
   * 
   * @param points: vector con los puntos 
   */
  PointSet::PointSet(const emst::point_vector& points, const double& minimum_distance) {
    for (const point& current_point : points) {
      (*this).emplace_back(current_point);
    }
    minimum_distance_ = minimum_distance;
  }

  /**
   * Método que calcula el árbol generador mínimo euclidiano de un conjunto de puntos en un espacio
   * bidimensional, para ello, utiliza un algoritmo greedy similar al de Kruskal, se genera un sub árbol
   * por cada punto y se van uniendo estos teniendo siempre encuenta de no crear aristas entre puntos de 
   * un mismo árbol (evitando así los ciclos), al terminar, en el atributo emst_ de la clase PointSet
   * tendremos un árbol mínimo generador
   */
  void PointSet::EMST(void) {
    emst::arch_vector archs;
    ComputeArchVector_(archs); // Vector con todos los arcos 
    forest forest; 
    for (const emst::point& point : *this) { // Creamos un sub-árbol por cada punto
      SubTree sub_tree;
      sub_tree.AddPoint(point);
      forest.emplace_back(sub_tree);
    }
    int i{0};
    double cost{0};
    for (const emst::weighted_arch& arch : archs) { // Recorremos el vector con los arcos y fusionamos los que se puedan conectar
      int i{0}, j{0};
      FindIncidentSubTrees_(forest, arch.second, i, j);
      if (i != j) {
        MergeSubTrees_(forest, arch.second, i, j);
        cost += arch.first;
      }
    }
    emst_ = forest[0].GetArchs(); // El árbol mínimo será el que este en forest
    cost_ = cost;
  }

  /**
   * Método privado de la clase arch vector que crea un vector con todas las posibles aristas entre los
   * puntos del espacio bidimensional para ir comprobando si nos sirven o no
   * 
   * @param archs: vector el cual se va a modificar para incluir las aristas
   */
  void PointSet::ComputeArchVector_(emst::arch_vector& archs) const {
    archs.clear();
    const int point_set_size = size(); // Tamaño del PointSet
    for (int i{0}; i < point_set_size - 1; ++i) { // Recorremos el PointSet
      const emst::point &point_i{(*this)[i]}; // Punto i
      for (int j{i + 1}; j < point_set_size; ++j) { // Comprobamos todos los puntos con los que se pueda unir i
        const emst::point& point_j{(*this)[j]}; // Punto j
        const double dist = EuclideanDistance_(std::make_pair(point_i, point_j)); // Calculamos distancia
        if (dist >= minimum_distance_) {
          archs.emplace_back(std::make_pair(dist, std::make_pair(point_i, point_j))); // Hacemos el arco entre ambos puntos
        }
      }
    }
    std::sort(archs.begin(), archs.end()); // Ordenamos el vector de arcos
  }

  /**
   * Método privado de la clase PointSet que nos permite calcular la distancia euclidea entre dos puntos unidos en un arco
   * con este método podemos determinar los costes de las aristas sobre las que aplicaremos un algoritmo similar al de kruskal
   * 
   * @param arch: arco que une ambos puntos
   * 
   * @return el valor de la distancia entre ambos puntos tomando sus componentes
   */
  double PointSet::EuclideanDistance_(const emst::arch& arch) const {
    double x_component{arch.first.first - arch.second.first}; // Distancia entre las componentes x de los puntos del arco
    double y_component{arch.first.second - arch.second.second}; // Distancia entre las componentes y de los puntos del arco
    double distance;
    distance = pow(x_component, 2) + pow(y_component, 2); 
    distance = sqrt(distance); // Cálculo de la distancia de los puntos
    return distance;
  }

  /**
   * Método privado de la clase PointSet que encuentra a que árboles de un bosque pertenecen ambos puntos de una arista,
   * posteriormente en el método EMST, vemos si i y j son iguales o no, para saber si la arista entre ambos puntos
   * es válida para crear el emst
   * 
   * @param sub_trees: bosque donde se encuentran los sub_árboles
   * @param arch: arista que contiene ambos puntos
   * @param i, j: dos enteros que almacenaran el índice del sub árbol en el vector al que pertenecen el primer punto de
   *              la arista y el segundo respectivamente, posteriormente estos valores se comparan ya que si son iguales
   *              significa que la arista uniría puntos de un mismo sub árbol y crearía un ciclo, por lo tanto no nos
   *              sirve
   */
  void PointSet::FindIncidentSubTrees_(const emst::forest& sub_trees, const emst::arch &arch, int& i, int& j) const {
    for (int k{0}; k < sub_trees.size(); ++k) { // Recorremos los sub-árboles del bosque
      if (sub_trees[k].Contains(arch.first)) { // Si el k-ésimo árbol contiene el arco, i es igual a k
        i = k;
      }
      if (sub_trees[k].Contains(arch.second)) { // Si el k-ésimo árbol contiene el arco, j es igual a k
        j = k;
      }
    }
  }

  /**
   * Método privado de la clase Pointset que usa el método SubTree::Merge para unir dos sub árboles de un bosque
   * en uno solo en este mismo bosque, para ello en el método EMST, la llamamos cuando creamos un arco que une dos
   * sub árboles del bosque
   * 
   * @param sub_trees: bosque del cual sacaremos los sub árboles
   * @param arch: arista que une los sub árboles
   * @param i, j: índices de ambos sub árboles en el vector que representa el bosque (sub_trees)
   */
  void PointSet::MergeSubTrees_(emst::forest& sub_trees, const emst::arch& arch, int i, int j) const {
    sub_trees[i].Merge(sub_trees[j], std::make_pair(EuclideanDistance_(arch), arch)); // Unimos ambos arboles mediante el arco arch
    sub_trees.erase(sub_trees.begin() + j);
  }

  void PointSet::QuickHull(void) {
    hull_.clear();
    emst::point min_x_point{0.0, 0.0};
    emst::point max_x_point{100000.0, 100000.0};
    XBounds_(min_x_point, max_x_point);
    QuickHull(emst::line{min_x_point, max_x_point}, side::LEFT);
    QuickHull(emst::line{min_x_point, max_x_point}, side::RIGHT);
    // Borrar duplicados
    std::sort(hull_.begin(), hull_.end());
    hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
  }

  void PointSet::QuickHull(const emst::line& line_a, int side) {
    emst::point farthest;
    if (FarthestPoint_(line_a, side, farthest)) {
      QuickHull(emst::line{line_a.first, farthest}, -FindSide_(emst::line(line_a.first, farthest), line_a.second));
      QuickHull(emst::line{farthest, line_a.second}, -FindSide_(emst::line(farthest, line_a.second), line_a.first));
    } else {
      hull_.emplace_back(line_a.first);
      hull_.emplace_back(line_a.second);
    }
  }

  bool PointSet::FarthestPoint_(const emst::line& line_a, int side, emst::point& farthest) const {
    farthest = emst::point_vector::at(0);
    double max_dist{0};
    bool found{false};
    for (const emst::point& current_point : *this) {
      const double dist{Distance_(line_a, current_point)};
      if (FindSide_(line_a, current_point) == side && dist > max_dist) {
        farthest = current_point;
        max_dist = dist;
        found = true;
      }
    }
    return found;
  }

  double PointSet::PointToLine_(const emst::line& line_a, const emst::point& point_a) const {
    const emst::point& point_b{line_a.first};
    const emst::point& point_c{line_a.second};
    return (point_a.second - point_b.second) * (point_c.first - point_b.first) - (point_c.second - point_b.second) * (point_a.first - point_b.first);
  }

  double PointSet::Distance_(const emst::line& line_a, const emst::point& point_a) const {
    return fabs(PointToLine_(line_a, point_a));
  }

  void PointSet::XBounds_(point& min_x, point& max_x) const {
    for (const emst::point& current_point : *this) {
      if (current_point.first < min_x.first) {
        min_x = current_point;
      } else if (current_point.first > max_x.first) {
        max_x = current_point;
      }
    }
  }
}