#pragma once
#include <vector>

class ArrayModel
{
private:
    std::vector<int> array_;
    int capacity_;

public:
    ArrayModel();
    size_t getSizeArray() const;
    void setSizeArray(size_t newSizeArray);
    const std::vector<int> &getArray() const;
    void setItemForIndex(size_t index, int value);
    void setItem(int &value);
};