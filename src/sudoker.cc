/*
Copyright (c) 2014, Viktor Gal
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
#include <time.h>

#include "SudokuProblem.h"
#include "BacktrackSolver.h"

int main (int argc, char** argv)
{
	if (argc != 3) {
		std::cerr << "Invalid number of arguments" << std::endl
		<< "Please use the following command:" << std::endl
		<< "\t./sudoku <problem file> <solution file>" << std::endl;

		return EXIT_FAILURE;
	}
	const std::string out_fname = argv[2];

	SudokuSolver* solver = NULL;
	try {
		std::shared_ptr<SudokuProblem> p = SudokuProblem::read_csv(argv[1]);

		clock_t start = clock();
		solver = new BacktrackSolver();

		std::cout << solver->is_solved(p) << std::endl;

		if (!solver->solve(p)) {
			// couldn't solve the problem
			std::cerr << "could not solve the problem!" << std::endl;
		} else {
			std::cout << solver->is_solved(p) << std::endl;
			std::cout << "Sudoku is solved in " << (double)(clock() - start)/CLOCKS_PER_SEC
			<< " seconds, saving solution to '" + out_fname
			<< "'" << std::endl;
			// save the solved problem
			p->save_csv(out_fname);
		}

		delete solver;
	} catch (SudokuException& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
