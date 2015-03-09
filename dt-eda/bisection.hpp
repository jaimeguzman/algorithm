/**
   \file bisection.hpp
   \brief Header file for bisection.cpp.
*/

#include "eda.hpp"

void bisection(Parameters *params, AveragePopulationStatistics *avg_stats);
int do_runs(Parameters *params, AveragePopulationStatistics *avg_stats, int quiet=1);
void print_bisection_summary(FILE *f, AveragePopulationStatistics *stats);
