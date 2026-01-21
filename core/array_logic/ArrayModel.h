#pragma once
#include <vector>

class ArrayModel
{
private:
    std::vector<int> array_;
    size_t capacity_;
    size_t size_;

public:
    explicit ArrayModel(int capacity = 0);
    size_t getCapacity() const;
    size_t getSize() const;
    void setCapacity(size_t newCapacity);
    void setSize(size_t newSize);
    const std::vector<int> &getArray() const;
    void setItemForIndex(size_t index, int value);
    void pushItem(int &value);
};