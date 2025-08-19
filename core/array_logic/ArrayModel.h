#pragma once
#include <vector>

class ArrayModel
{
private:
    std::vector<int> array_;
    int capacity_;

public:
    explicit ArrayModel(int capacity = 0);
    size_t getCapacity() const;
    void setCapacity(size_t newSizeArray);
    const std::vector<int> &getArray() const;
    void setItemForIndex(size_t index, int value);
    void pushItem(int &value);
};