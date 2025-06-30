#pragma once
#include "Header.h"


struct Matrix {
	size_t rows = 0, cols = 0;
	double** matrix;

	Matrix();
	Matrix(size_t rows, size_t cols);
	void fillMatrix(size_t rows, size_t cols, size_t x, size_t y);
	void changeSize(size_t rows, size_t cols);
	void changeEl(Matrix&matrix , size_t rows, size_t cols);
	void printMatrix() const;
	~Matrix();
};


