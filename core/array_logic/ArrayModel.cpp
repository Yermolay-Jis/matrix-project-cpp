#include "ArrayModel.h"

ArrayModel::ArrayModel(int capacity) : capacity_(capacity) {};

size_t ArrayModel::getCapacity() const
{
    return capacity_;
};

size_t ArrayModel::getSize() const
{
    return size_;
}

void ArrayModel::setCapacity(size_t newCapacity)
{
    array_.reserve(newCapacity);
    capacity_ = newCapacity;
};

void ArrayModel::setSize(size_t newSize)
{
    array_.resize(newSize);
    capacity_ = newSize;
    size_ = newSize;
    for (size_t i = 0; i < newSize; i++)
        array_[i] = 0;
}

const std::vector<int> &ArrayModel::getArray() const
{
    return array_;
};

void ArrayModel::setItemForIndex(size_t index, int value)
{
    if (index < array_.size())
    {
        array_[index] = value;
    };
};

void ArrayModel::pushItem(int &value)
{
    array_.push_back(value);
};