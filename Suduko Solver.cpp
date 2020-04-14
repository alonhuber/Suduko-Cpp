// Suduko Solver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Solver.h"

int main()
{
	std::string path = "../Suduko.csv";
	std::string output = "../Resloved sudoko.csv";
	Solver solver;
	solver.solve(path,output);
    return 0;
}

