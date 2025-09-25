#include "MergeSort.h"

std::vector<int> mergeSort(const std::vector<int> &arr)
{
    size_t size = arr.size();
    if (size <= 1)
        return arr;

    std::vector<int> left_branch;
    std::vector<int> right_branch;
    size_t div_size = size / 2;

    for (size_t i = 0; i < div_size; ++i)
    {
        left_branch.push_back(arr[i]);
    };
    for (size_t i = div_size; i < size; ++i)
    {
        right_branch.push_back(arr[i]);
    };

    left_branch = mergeSort(left_branch);
    right_branch = mergeSort(right_branch);

    std::vector<int> mergeArr;
    size_t left_idx = 0;
    size_t right_idx = 0;
    while (left_idx < left_branch.size() && right_idx < right_branch.size())
    {
        if (left_branch[left_idx] <= right_branch[right_idx])
        {
            mergeArr.push_back(left_branch[left_idx]);
            left_idx++;
        }
        else
        {
            mergeArr.push_back(right_branch[right_idx]);
            right_idx++;
        };
    };

    while (left_idx < left_branch.size())
    {
        mergeArr.push_back(left_branch[left_idx]);
        left_idx++;
    };

    while (right_idx < right_branch.size())
    {
        mergeArr.push_back(right_branch[right_idx]);
        right_idx++;
    };
    return mergeArr;
};