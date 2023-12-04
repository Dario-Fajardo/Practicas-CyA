/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos la definición de la clase SubTree
*/

#include "../include/sub_tree.h"

namespace emst {
  SubTree::SubTree(void) {
    archs_ = {};
    points_ = {};
    total_cost_ = 0;
  }

  void SubTree::AddArch(const emst::arch& arch) {
    archs_.push_back(arch);
    AddPoint(arch.first);
    AddPoint(arch.second);
  }

  void SubTree::AddPoint(const emst::point& point) {
    points_.insert(point);
  }

  bool SubTree::Contains(const emst::point& point) const {
    return (points_.find(point) != points_.end());
  }

  void SubTree::Merge(const SubTree &sub_tree, const emst::weighted_arch& arch) {
    archs_.insert(archs_.end(), sub_tree.archs_.begin(), sub_tree.archs_.end());
    archs_.emplace_back(arch.second);
    points_.insert(sub_tree.points_.begin(), sub_tree.points_.end());
    total_cost_ += arch.first + sub_tree.GetCost();
  }
}