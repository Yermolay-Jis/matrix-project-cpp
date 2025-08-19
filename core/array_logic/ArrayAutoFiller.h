#pragma once
#include "array_logic/ArrayModel.h"
#include <random>

class ArrayAutoFiller
{
public:
    ArrayAutoFiller(int min, int max);
    void autoFill(std::shared_ptr<ArrayModel> array_model);

private:
    int min_;
    int max_;
    std::mt19937 random_engine;
};