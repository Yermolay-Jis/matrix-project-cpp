#include "matrix.h"
// #include "ui/screens/matrix_operations/menuLab_3.h"
#include <string>
#include <iostream>

MatrixModel::MatrixModel()
{
    data_ = std::make_shared<std::vector<std::vector<double>>>(rows_);
    for (size_t i = 0; i < rows_; i++)
    {
        (*data_)[i] = std::vector<double>(cols_);
    };
}
MatrixModel::MatrixModel(size_t rows, size_t cols) : rows_(rows), cols_(cols)
{
    data_ = std::make_shared<std::vector<std::vector<double>>>(rows_);
    for (size_t i = 0; i < rows_; i++)
    {
        (*data_)[i] = std::vector<double>(cols_);
    };
}

const std::string MatrixModel::MatrixFormat()
{
    std::stringstream ss;
    for (size_t i = 0; i < rows_; i++)
    {
        for (size_t j = 0; j < cols_; j++)
        {
            ss << (*data_)[i][j] << "\t";
        };
        ss << "\n";
    };
    return ss.str();
}

void MatrixModel::SetForIndex(double value, size_t row, size_t col)
{
    if (!(data_ == nullptr || rows_ == 0 || cols_ == 0))
    {
        (*data_)[row][col] = value;
    }
    else
    {
        return;
    }
}

size_t MatrixModel::GetRows() const
{
    return rows_;
}

size_t MatrixModel::GetCols() const
{
    return cols_;
}

const std::shared_ptr<std::vector<std::vector<double>>> MatrixModel::GetMatrix() const
{
    return data_;
}

void MatrixModel::CreateMatrix(size_t rows, size_t cols)
{
    rows_ = rows;
    cols_ = cols;
    data_ = std::make_shared<std::vector<std::vector<double>>>(rows_);
    for (size_t i = 0; i < rows_; i++)
    {
        (*data_)[i] = std::vector<double>(cols_);
    };
}
