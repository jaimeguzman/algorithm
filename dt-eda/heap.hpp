/**
   \file heap.hpp
   \brief Header file for heap.cpp.
*/

#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#define HEAP_MINUS_INFINITY -1

int max_heapify(double *x, int i, int n, int *index, int *rev_index);
int build_max_heap(int *a, int *b, double *x, int n, int *index, int *rev_index);
int float_up_max_heap(double *x, int i, int n, int *index, int *rev_index);
int increase_key_max_heap(double *x, int i, double val, int n, int *index, int *rev_index);
int pop_max_heap(double *x, int &n, int *index, int *rev_index);
void print_max_heap(double *x, int n, int *index, int *rev_index);
int check_max_heap(double *x, int n, int *index, int *rev_index);

#endif
