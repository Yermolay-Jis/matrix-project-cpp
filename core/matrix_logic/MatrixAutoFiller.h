#pragma once
#include "matrix_logic/matrix.h"
#include <random>
#include <memory>

class MatrixAutoFiller
{
public:
    MatrixAutoFiller(int min, int max);
    void AutoFill(std::shared_ptr<MatrixModel> matrix_model);

private:
    int min_, max_;
    std::mt19937 random_engine_;
};