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

#include "SudokuSolver.h"


SudokuSolver::SudokuSolver() {

}

SudokuSolver::~SudokuSolver() {

}

#include <iostream>

bool SudokuSolver::is_solved(std::shared_ptr<SudokuProblem> p) {
	if (p.get() == NULL)
		return false;

	for (int i = 0; i < SudokuProblem::GRID_SIZE; i++) {
		if (!is_unique(p->get_row(i)))
		    return false;
		if (!is_unique(p->get_col(i)))
			return false;

		unsigned int blockRowStart = i - i % SudokuProblem::BLOCK_ROWS;
		unsigned int blockColStart = i % SudokuProblem::BLOCK_COLS * SudokuProblem::BLOCK_COLS;

		if (!is_unique(p->get_block(blockRowStart, blockColStart)))
		    return false;
	}
	return true;
}

inline bool check_uniqueness(int cur_val, bool (&seen)[10], int val) {
	// val is given we just want to check if that's equals cur_val
	if (val != SudokuProblem::UNASSIGNED) {
		if (cur_val == val)
			return false;
	} else {
		// if val not set we are actually validating the solution
		// if any value in the problem is 0, i.e. unassigned it's not solved
		if (cur_val == SudokuProblem::UNASSIGNED) {
			return false;
		}
		// if haven't seen the value, mark it seen
		if (!seen[cur_val]) {
			seen[cur_val] = true;
		} else {
			// we've seen this element before... i.e. non unique digit
			return false;
		}
	}
	return true;
}

template<typename Iterator>
bool SudokuSolver::is_unique(Iterator& it, int val) {
	bool seen[] = {false, false, false, false, false,
				false, false, false, false, false};
	for (int i = 0; i < it.size(); i++) {
		if (!check_uniqueness(it[i], seen, val))
			return false;
	}
	return true;
}

bool SudokuSolver::is_unique(SudokuProblem::ConstBlock& b, int val) {
	bool seen[] = {false, false, false, false, false,
				false, false, false, false, false};
	for (unsigned int i = 0; i < b.cols(); i++) {
		for (unsigned int j = 0; j < b.rows(); j++) {
			if (!check_uniqueness(b(i, j), seen, val))
				return false;
		}
	}
	return true;
}

