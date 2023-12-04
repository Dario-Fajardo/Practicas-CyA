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
  PointSet::PointSet(const emst::point_vector& points) {
    for (const point& current_point : points) {
      (*this).emplace_back(current_point);
    }
  }

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
    for (const emst::weighted_arch& arch : archs) { // Recorremos el vector con los arcos y fusionamos los que se puedan conectar
      int i{0}, j{0};
      FindIncidentSubTrees_(forest, arch.second, i, j);
      if (i != j) {
        MergeSubTrees_(forest, arch.second, i, j);
      }
    }
    emst_ = forest[0].GetArchs(); // El árbol mínimo será el que este en forest
  }

  void PointSet::ComputeArchVector_(emst::arch_vector& archs) const {
    archs.clear();
    const int point_set_size = size(); // Tamaño del PointSet
    for (int i{0}; i < point_set_size - 1; ++i) { // Recorremos el PointSet
      const emst::point &point_i{(*this)[i]}; // Punto i
      for (int j{i + 1}; j < point_set_size; ++j) { // Comprobamos todos los puntos con los que se pueda unir i
        const emst::point& point_j{(*this)[j]}; // Punto j
        const double dist = EuclideanDistance_(std::make_pair(point_i, point_j)); // Calculamos distancia
        archs.emplace_back(std::make_pair(dist, std::make_pair(point_i, point_j))); // Hacemos el arco entre ambos puntos
      }
    }
    std::sort(archs.begin(), archs.end()); // Ordenamos el vector de arcos
  }

  double PointSet::EuclideanDistance_(const emst::arch& arch) const {
    double x_component{arch.first.first - arch.second.first}; // Distancia entre las componentes x de los puntos del arco
    double y_component{arch.first.second - arch.second.second}; // Distancia entre las componentes y de los puntos del arco
    double distance;
    distance = pow(x_component, 2) + pow(y_component, 2); 
    distance = sqrt(distance); // Cálculo de la distancia de los puntos
    return distance;
  }

  void PointSet::FindIncidentSubTrees_(const emst::forest& sub_tree, const emst::arch &arch, int& i, int& j) const {
    for (int k{0}; k < sub_tree.size(); ++k) { // Recorremos los sub-árboles del bosque
      if (sub_tree[k].Contains(arch.first)) { // Si el k-ésimo árbol contiene el arco, i es igual a k
        i = k;
      }
      if (sub_tree[k].Contains(arch.second)) { // Si el k-ésimo árbol contiene el arco, j es igual a k
        j = k;
      }
    }
  }

  void PointSet::MergeSubTrees_(emst::forest& sub_tree, const emst::arch& arch, int i, int j) const {
    sub_tree[i].Merge(sub_tree[j], std::make_pair(EuclideanDistance_(arch), arch)); // Unimos ambos arboles mediante el arco arch
    sub_tree.erase(sub_tree.begin() + j);
  }
}