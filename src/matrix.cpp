#include "../include/matrix.h"
#include "../include/menuLab_3.h"

Matrix::Matrix()
{
    matrix = new double *[rows]();
    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = new double[cols]();
    }
}
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
{
    matrix = new double *[rows]();
    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = new double[cols]();
    }
}
void Matrix::changeSize(size_t newRows, size_t newCols)
{
    try
    {
        if (newRows == 0 || newCols == 0)
        {
            throw std::bad_alloc();
        }
        for (size_t i = 0; i < rows; i++)
        {
            delete matrix[i];
        }
        delete[] matrix;
        double **newMatrix = new double *[newRows]();
        for (size_t i = 0; i < newRows; i++)
        {
            newMatrix[i] = new double[newCols]();
        }
        matrix = newMatrix;
        rows = newRows;
        cols = newCols;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "������: ������� �������� �� ������ 1!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void Matrix::printMatrix() const
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << "   " << matrix[i][j];
        }
        std::cout << "\n\n";
    }
}
Matrix::~Matrix()
{
    for (size_t i = 0; i < rows; i++)
    {
        delete matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}
