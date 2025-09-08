#include "matrix_logic/MatrixAutoFiller.h"

MatrixAutoFiller::MatrixAutoFiller(int max, int min) : max_(max), min_(min)
{
    std::random_device rd;
    random_engine_.seed(rd());
};

void MatrixAutoFiller::AutoFill(std::shared_ptr<MatrixModel> matrix_model)
{
    std::uniform_int_distribution<int> distribution(min_, max_);
    size_t rowMatrix = matrix_model->GetRows();
    size_t colMatrix = matrix_model->GetCols();

    auto data = matrix_model->GetMatrix();
    if (!(data == nullptr || rowMatrix == 0 || colMatrix == 0))
    {
        for (size_t i = 0; i < rowMatrix; i++)
        {
            for (size_t j = 0; j < colMatrix; j++)
            {
                int number = distribution(random_engine_);
                matrix_model->SetForIndex(number, i, j);
            }
        }
    }
};