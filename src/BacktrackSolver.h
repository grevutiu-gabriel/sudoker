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

#ifndef __BACKTRACKSOLVER_H__
#define __BACKTRACKSOLVER_H__

#include "SudokuSolver.h"

/**
 * A simple backtrack sudoku solver using recursion.
 * It finds the first viable solution, but not all of it.
 */
class BacktrackSolver : public SudokuSolver {

	public:
		BacktrackSolver();

		virtual ~BacktrackSolver();

		/**
		 * Solve Sudoku problem.
		 *
		 * @param p the problem itself
		 * @return True if successfully solved the problem, False otherwise
		 */
		virtual bool solve(std::shared_ptr<SudokuProblem> p);

	private:
		/**
		 * Checks whether an assignment of a given element would satisfy
		 * the rules of Sudoku:
		 *    * the elements of the row are unique
		 *    * the elements of the column are unique
		 *    * the elements of the block are unique
		 *
		 * @param row the row of the element
		 * @param col the column of the element
		 * @param val the value of the element
		 * @return True if the the setting does not break the rules, False otherwise
		 */
		bool try_assign(unsigned int row, unsigned int col, int val) const;
};

#endif /* __BACKTRACKSOLVER_H__ */
