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

#include "SudokuProblem.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

SudokuException::SudokuException(const std::string& r)
 : caused(r) {
}

SudokuException::~SudokuException() throw () {
}

const char* SudokuException::what() const throw() {
	return caused.c_str();
}


SudokuProblem::SudokuProblem() {

}

SudokuProblem::~SudokuProblem() {
}

std::shared_ptr<SudokuProblem> SudokuProblem::read_csv(const std::string& fname) throw (SudokuException) {
	// open file
	std::ifstream sudoku_file(fname.c_str());

	// check if managed to open
	if (!sudoku_file.is_open()) {
		throw SudokuException("could not open file " + fname);
	}

	// parse the input file
	std::string line;
	//std::vector<std::vector<int> > grid;
	int curr_row = 0;
	SudokuGrid m;
	while (getline(sudoku_file, line)) {

		// make sure that the number of rows are not more than it is expected
		if (curr_row >= GRID_SIZE) {
			sudoku_file.close();
			throw SudokuException("Invalid sudoku problem: invalid number of rows");
		}

		// tokenize a line, i.e. a row
		std::string element;
		std::istringstream ss(line);
		std::vector<int> row;
		while (getline(ss, element, ',')) {
			if (!isdigit(element.c_str()[0])) {
				sudoku_file.close();
				throw SudokuException("Invalid sudoku problem: contains non-digit element");
			}
			row.push_back(atoi(element.c_str()));
		}

		// assure that the row is GRID_SIZE wide
		if (row.size() != GRID_SIZE) {
			sudoku_file.close();
			throw SudokuException("Invalid sudoku problem: row width is not "
			                      + std::to_string(GRID_SIZE) +
			                      " at row " + std::to_string(curr_row+1));
		}
		m.row(curr_row) = Eigen::VectorXi::Map(&row[0], row.size());

		//grid.push_back(row);
		curr_row++;
	}
	sudoku_file.close();

	// validate the number of rows, i.e. if it's GRID_SIZE
	if (!curr_row || (curr_row != GRID_SIZE)) {
		std::cout << curr_row << std::endl;
		throw SudokuException("Invalid sudoku problem: invalid number of rows");
	}

	std::shared_ptr<SudokuProblem> p(new SudokuProblem);
	p->_m = m;
	return p;
}

void SudokuProblem::save_csv(const std::string& fname) throw (SudokuException) {
	std::ofstream sudoku_file(fname.c_str());

	// check if managed to open
	if (!sudoku_file.is_open()) {
		throw SudokuException("could not open file " + fname);
	}

	// write the matrix into the file in CSVFormat
	sudoku_file << _m.format(_CSVFormat);

	sudoku_file.close();
}

bool SudokuProblem::get_unassigned(unsigned int& row, unsigned int& col) const {
	for (row = 0; row < _m.rows(); row++)
		for (col = 0; col < _m.cols(); col++)
			if (_m(row, col) == UNASSIGNED)
				return true;
	return false;
}

void SudokuProblem::set(const unsigned int row, const unsigned int col, int val) throw(SudokuException) {
	if (row >= GRID_SIZE) throw SudokuException("out-of-bound row index");
	if (col >= GRID_SIZE) throw SudokuException("out-of-bound column index");
	if ((val < 0) || (val > 9)) throw SudokuException("trying to set non-digit value");

	_m(row, col) = val;
}

int SudokuProblem::get(const unsigned int row, const unsigned int col) const throw(SudokuException) {
	if (row >= GRID_SIZE) throw SudokuException("out-of-bound row index");
	if (col >= GRID_SIZE) throw SudokuException("out-of-bound column index");

	return _m(row, col);
}

SudokuProblem::ConstRowPtr SudokuProblem::get_row(const unsigned int row) const {
	if (row >= GRID_SIZE) throw SudokuException("out-of-bound row index");
	return _m.row(row);
}

SudokuProblem::ConstColPtr SudokuProblem::get_col(const unsigned int col) const {
	if (col >= GRID_SIZE) throw SudokuException("out-of-bound column index");
	return _m.col(col);
}

SudokuProblem::ConstBlock SudokuProblem::get_block(const unsigned startRow, const unsigned startCol) const {
	if (startRow >= GRID_SIZE) throw SudokuException("out-of-bound row index");
	if (startCol >= GRID_SIZE) throw SudokuException("out-of-bound column index");

	return _m.block(startRow, startCol, BLOCK_ROWS, BLOCK_COLS);;
}

const IOFormat SudokuProblem::_CSVFormat = IOFormat(StreamPrecision, DontAlignCols, ",", "\n");
