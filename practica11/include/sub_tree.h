/**
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* 2º Curso en Grado en Ingeniería Informática
* Computabilidad y Algoritmia
* Práctica 11: Algoritmos Voraces. Euclidean Minimum Spanning Tree
*
* @author Dario Fajardo alu0101564630@ull.edu.es
* @date 2 Dic 2023
* @brief En este archivo encontramos la declaración de la clase SubTree
*/
#include "basic_types.h"

namespace emst {
  class SubTree {
   public:
    // Constructores
    SubTree(void);
    // Getters
    emst::tree GetArchs(void) const { return archs_; }
    emst::point_collection GetPoints(void) const { return points_; }
    double GetCost(void) const { return total_cost_; }
    // Otros métodos
    void AddPoint(const emst::point& new_point);
    void AddArch(const emst::arch& new_arch);
    bool Contains(const emst::point& point) const;
    void Merge(const SubTree& sub_tree, const emst::weighted_arch& arch);
   private:
    emst::tree archs_;
    emst::point_collection points_;
    double total_cost_;
  };

  typedef std::vector<SubTree> forest;
}