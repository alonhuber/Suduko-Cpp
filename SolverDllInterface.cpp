#include "stdafx.h"
#include "Solver.h"
#ifdef SOLVER_EXPORTS
#define SOLVER_EXPORTS __declspec(dllexport)
#else
#define SOLVER_EXPORTS __declspec(dllimport)
#endif

extern "C" {
	__declspec(dllexport) bool solveSuduko(char* path, char* outputPath)
	{
		Solver solver;
		solver.solve(path, outputPath);
	}
}