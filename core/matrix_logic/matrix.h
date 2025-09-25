#pragma once
#include <cstddef>

struct MatrixModel
{
public:
	MatrixModel();
	MatrixModel(size_t rows, size_t cols);
	double GetValueForIndex(size_t i, size_t j) const;
	void SetForIndex(double value, size_t row, size_t col);
	size_t GetRows() const;
	size_t GetCols() const;
	std::shared_ptr<std::vector<std::vector<double>>> GetMatrix() const;
	void CreateMatrix(size_t rows, size_t cols);
	~MatrixModel() = default;

private:
	size_t rows_ = 0, cols_ = 0;
	std::shared_ptr<std::vector<std::vector<double>>> data_;
};
