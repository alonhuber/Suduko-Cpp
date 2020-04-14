#pragma once
#include "Solver.h"
#ifdef SOLVER_EXPORTS
#define SOLVER_EXPORTS __declspec(dllexport)
#else
#define SOLVER_EXPORTS __declspec(dllimport)
#endif

void SOLVER_EXPORTS solveSuduko(std::string path, std::string outputPath);

