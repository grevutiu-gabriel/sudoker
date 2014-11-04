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

#include "BacktrackSolver.h"

BacktrackSolver::BacktrackSolver() {

}

BacktrackSolver::~BacktrackSolver() {

}

bool BacktrackSolver::solve(std::shared_ptr<SudokuProblem> p)
{
	unsigned int row, col;
	this->_p = p;

	if (!_p->get_unassigned(row, col))
		return true;

	for (int digit = 1; digit < 10; digit++) {
		if (try_assign(row, col, digit)) {
			_p->set(row, col, digit);

			if (this->solve(p))
				return true;

			// couldn't find a good solution, reseting
			_p->set(row, col, SudokuProblem::UNASSIGNED);
		}
	}

	return false;
}

bool BacktrackSolver::try_assign(unsigned int row, unsigned int col, int val) const {
	unsigned int blockRowStart = (row - row % SudokuProblem::BLOCK_ROWS);
	unsigned int blockColStart = (col - col % SudokuProblem::BLOCK_COLS);

	return (is_unique(_p->get_row(row), val)
			&& is_unique(_p->get_col(col), val)
			&& is_unique(_p->get_block(blockRowStart, blockColStart), val));
}

