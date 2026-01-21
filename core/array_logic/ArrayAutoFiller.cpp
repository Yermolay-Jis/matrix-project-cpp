#include "ArrayAutoFiller.h"
#include "ArrayModel.h"

ArrayAutoFiller::ArrayAutoFiller(const int min, const int max) : min_(min), max_(max)
{
    std::random_device rd;
    random_engine.seed(rd());
};

void ArrayAutoFiller::autoFill(ArrayModel &array_model)
{

    std::uniform_int_distribution<int> distribuition(min_, max_);
    size_t capacityArray = array_model.getCapacity();

    if (array_model.getArray().size() < 1)
    {
        for (size_t i = 0; i < capacityArray; ++i)
        {
            int number = distribuition(random_engine);
            array_model.setItemForIndex(i, number);
        };
    }
    else
    {
        for (size_t i = 0; i < capacityArray; ++i)
        {
            int number = distribuition(random_engine);
            array_model.setItemForIndex(i, number);
        };
    }
};