#include "ArrayModel.h"

ArrayModel::ArrayModel(int capacity) : capacity_(std::move(capacity)) {};

size_t ArrayModel::getCapacity() const
{
    return this->capacity_;
};

void ArrayModel::setCapacity(size_t newSizeArray)
{
    this->array_.reserve(newSizeArray);
    capacity_ = newSizeArray;
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

void ArrayModel::pushItem(int &value)
{
    this->array_.push_back(value);
};