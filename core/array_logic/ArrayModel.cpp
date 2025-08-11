#include "ArrayModel.h"

ArrayModel::ArrayModel() {};

size_t ArrayModel::getSizeArray() const
{
    return this->array_.size();
};

void ArrayModel::setSizeArray(size_t newSizeArray)
{
    this->array_.resize(newSizeArray);
};

const std::vector<int> &ArrayModel::getArray() const
{
    return this->array_;
};

void ArrayModel::setItemForIndex(size_t index, int value)
{
    if (index < this->array_.size())
    {
        this->array_[index] = value;
    };
};

void ArrayModel::setItem(int &value)
{
    this->array_.push_back(value);
};