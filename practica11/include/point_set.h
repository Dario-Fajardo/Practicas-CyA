/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos la declaración de la clase PointSet
*/
#include "sub_tree.h"
#include <algorithm>
#include <cmath>

#ifndef POINT_SET_H
#define POINT_SET_H

namespace emst {
  class PointSet : public emst::point_vector {
   public:
    // Constructores
    PointSet(const emst::point_vector& points, const double& minimum_distance);
    // Getters
    inline const emst::tree& GetTree(void) const { return emst_; }
    inline const emst::point_vector& GetPoints(void) const { return *this; }
    inline const double GetCost(void) const { return cost_; }
    // Otros métodos
    void EMST(void);
   private:
    emst::tree emst_;
    double cost_;
    double minimum_distance_;
    void ComputeArchVector_(emst::arch_vector& archs) const;
    void FindIncidentSubTrees_(const emst::forest& sub_tree, const emst::arch &arch, int& i, int& j) const;
    void MergeSubTrees_(emst::forest& sub_tree, const emst::arch& arch, int i, int j) const;
    double EuclideanDistance_(const emst::arch& arch) const;
  };
}

#endif