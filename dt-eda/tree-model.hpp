/**
   \file tree-model.hpp
   \brief Header file for tree-model.cpp.
*/

#ifndef _TREE_MODEL_HPP_
#define _TREE_MODEL_HPP_

#include <stdio.h>

//! Class for storing, creating, and sampling the tree models.

class TreeModel {

 public:

  //! Constructor (assumes binary representation).
  TreeModel(int n);

  //! Another constructor (assumes arbitrary finite alphabets).
  TreeModel(int n, int *num_vals);

  //! Destructor.
  ~TreeModel();

  //! Learn the structure of the model.
  void learnStructure(int **x, int N, int loud=1);

  //! Learn the probabilities for a given structure.
  void learnProbabilities(int **x, int N, int loud=1);

  //! Sample the tree model to generate new candidate solutions.
  void sampleModel(int **x, int N);

  //! Print the model into a stream.
  void printModel(FILE *f);

 private:

  //! Number of variables (string positions).
  int n;

  //! Number of values for all string positions.
  int *num_vals;

  //! Compute mutual information of two positions, given a data set.
  inline double mutualInformation(int i, int j, int **x, int N);

  //! Compute ancestral ordering of the computed tree graph.
  void ancestralOrderingRec(int &i);

  //! Generates a marginal probability of a single character.
  int generate_marginal(int n, double *p);

  //! Generates a conditional probability of a single character.
  int generate_conditional(int n, int m, double *p, int pred);

  //! Storage for the learned model.
  int root;
  int *pred;
  int **succ;
  int *num_succ;
  int *anc_order;
  double **prob;
  int *num_prob;
  
  //! Local structures for temporary computing the mutual info. 
  int *mi_num;
  double *mi_p;
  double *mi_pi;
  double *mi_pj;
  int max_num_vals;
};

#endif
