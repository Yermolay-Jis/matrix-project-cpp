#include "../include/ArrayModel.h"

ArrayModel::ArrayModel() {};

size_t ArrayModel::getSizeArray() const
{
    return array_.size();
};

void ArrayModel::setSizeArray(size_t newSizeArray)
{
    array_.resize(newSizeArray);
};

const std::vector<double> &ArrayModel::getArray() const
{
    return array_;
};

void ArrayModel::setItem(size_t index, double value)
{
    if (index < array_.size())
    {
        array_[index] = value;
    };
};