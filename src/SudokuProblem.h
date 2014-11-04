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

#ifndef __SUDOKUPROBLEM_H__
#define __SUDOKUPROBLEM_H__

#include <memory>
#include <string>
#include <exception>

#include <Eigen/Eigen>

using namespace Eigen;

/**
 * SudokuException class that is used
 *
 */
class SudokuException : public std::exception {
	private:
		std::string caused;

	public:
		SudokuException(const std::string& r);
		virtual ~SudokuException() throw ();
		virtual const char* what() const throw();
};

/**
 * Class that represents the sudoku problem itself
 *
 */
class SudokuProblem {
	public:
		/** the value of an unassigned/unknown element */
		const static int UNASSIGNED = 0;

		/** size of the Sudoku problem */
		const static int GRID_SIZE = 9;

		/** number of rows of a block */
		const static int BLOCK_ROWS = 3;

		/** number of columns of a block */
		const static int BLOCK_COLS = 3;

		/** Type of the SudokuGrid which holds the problem itself */
		typedef Matrix<int, GRID_SIZE, GRID_SIZE> SudokuGrid;

		/** Type definition for the row pointer */
		typedef SudokuGrid::ConstRowXpr ConstRowPtr;

		/** Type definition for the column pointer*/
		typedef SudokuGrid::ConstColXpr ConstColPtr;

		/** Type definition for the block pointer */
		typedef const Block<const SudokuGrid> ConstBlock;
	private:
		SudokuProblem(SudokuProblem& orig);
		SudokuProblem& operator=(const SudokuProblem&);

	public:
		SudokuProblem();

		~SudokuProblem();

		/**
		 * Sets the given element with the supplied value
		 * appart from element setting it does some extra constraint checking
		 *
		 * @param row the row of the element
		 * @param col the column of the element
		 * @param val the value of the element
		 */
		void set(const unsigned int row, const unsigned int col, int val) throw(SudokuException);

		/**
		 * Get the element value at the given location (row, col)
		 *
		 * @param row reference to the row
		 * @param col reference to the column
		 * @return element value
		 */
		int get(const unsigned int row, const unsigned int col) const throw(SudokuException);

		/**
		 * Get row of the grid
		 *
		 * @param row the requested row
		 * @return const pointer to the row
		 */
		ConstRowPtr get_row(const unsigned int row) const;

		/**
		 * Get column of the grid
		 *
		 * @param col the requested column
		 * @return const pointer to the column
		 */
		ConstColPtr get_col(const unsigned int col) const;

		/**
		 * Get column of the grid
		 *
		 * @param col the requested column
		 * @return const pointer to the column
		 */
		ConstBlock get_block(const unsigned startRow, const unsigned startCol) const;

		/**
		 * Get the first element that is unassigned, i.e. unknown
		 *
		 * @param row reference to the row
		 * @param col reference to the column
		 * @return True if an unassigned element was found, False otherwise
		 */
		bool get_unassigned(unsigned int& row, unsigned int& col) const;

		/**
		 * Read a csv file that contains the sudoku problem.
		 * As specified it reads an 9x9 csv, where the unknown elements are
		 * represented by 0.
		 *
		 * @param fname file name of the problem file in csv format, where unknown value is 0
		 * @return
		 */
		static std::shared_ptr<SudokuProblem> read_csv(const std::string& fname) throw (SudokuException);

		/**
		 * Save the solved Sudoku problem into a given file in CSV format.
		 * The format of the file is same as the one described above for load.
		 *
		 * @param fname the file name where to save the solved sudoku in csv
		 */
		void save_csv(const std::string& fname) throw (SudokuException);

	private:
		/** formating constant for Eigen when writing to io */
		static const IOFormat _CSVFormat;

		/** the memory that represents the problem itself */
		SudokuGrid _m;
};

#endif /* __SUDOKUPROBLEM_H__ */
