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

#ifndef __SUDOKUSOLVER_H__
#define __SUDOKUSOLVER_H__

#include "SudokuProblem.h"
/**
 * Abstract class to solve a Sudoku problem
 *
 */
class SudokuSolver {

	public:
		SudokuSolver();

		virtual ~SudokuSolver();

		/**
		 * Solve Sudoku problem
		 *
		 * @param p the problem itself
		 * @return True if successfully solved the problem, False otherwise
		 */
		virtual bool solve(std::shared_ptr<SudokuProblem> p) = 0;

		/**
		 * Checks whether the supplied solution is solved
		 *
		 * @param p the problem itself
		 * @return True if the Sudoku problem is solved, False otherwise
		 */
		static bool is_solved(std::shared_ptr<SudokuProblem> p);

	protected:
		/**
		 * Checks whether the supplied row or column elements are unique
		 *
		 * @param it ConstRowXpr or ConstColXpr pointer
		 * @param val if set then checks whether adding the given value would
		 * change uniqueness
		 * @return True if all elements unique, False otherwise
		 */
		template<typename Iterator>
		static bool is_unique(Iterator& it, int val = SudokuProblem::UNASSIGNED);

		/**
		 * Checks whether the supplied block elements are unique
		 *
		 * @parma b block of the sudoku grid
		 * @param val if set then checks whether adding the given value would
		 * change uniqueness
		 * @return True if all elements are unique, False otherwise
		 */
		static bool is_unique(SudokuProblem::ConstBlock& b, int val = SudokuProblem::UNASSIGNED);

	protected:
		/** pointer to the given problem itself */
		std::shared_ptr<SudokuProblem> _p;
};

#endif /* __SUDOKUSOLVER_H__ */
