#pragma once
#include "array_logic/ArrayModel.h"
#include <random>

class ArrayAutoFiller
{
public:
    ArrayAutoFiller(const int min, const int max);
    void autoFill(ArrayModel &array_model);

private:
    int min_;
    int max_;
    std::mt19937 random_engine;
};