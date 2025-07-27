#pragma once
#include "Header.h"

class ArrayModel
{
private:
    std::vector<double> array_;

public:
    ArrayModel();
    size_t getSizeArray() const;
    void setSizeArray(size_t newSizeArray);
    const std::vector<double> &getArray() const;
    void setItem(size_t index, double value);
};