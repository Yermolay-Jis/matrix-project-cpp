#pragma once
#include "matrix_logic/matrix.h"
#include <random>
#include <memory>

class MatrixAutoFiller
{
public:
    MatrixAutoFiller(int max, int min);
    void AutoFill(std::shared_ptr<MatrixModel> matrix_model);

private:
    int max_, min_;
    std::mt19937 random_engine_;
};