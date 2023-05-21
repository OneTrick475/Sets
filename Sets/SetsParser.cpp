#include "SetsParser.h"
#include <fstream>
#include <iostream>
#include "Set.h"
#include "IPredicate.h"
#include "CriteriaSet.h"
#include "Predicates.h"
#include "Vector.hpp"

PolymorphicPtr<ISet> SetsParser::readSet(const MyString& fileName) const{
    std::ifstream file(fileName.c_str(), std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("couldnt open file");

    short workMode;
    short numberOfElements;

    file.read((char*)&numberOfElements, sizeof(short));
    file.read((char*)&workMode, sizeof(short));

    if (workMode < 0 || workMode > 4)
        throw std::invalid_argument("T should be a number between 0 and 4");
    if (numberOfElements < 0 || numberOfElements > 32)
        throw std::invalid_argument("N should be a number between 0 and 32");

    if(workMode == 0) {
        Vector<int> nums = getNums(file);
        return PolymorphicPtr<ISet>(new Set(nums));
    }
    if(workMode == 1) {
        Vector<int> nums = getNums(file);
        return PolymorphicPtr<ISet>(new CriteriaSet(PolymorphicPtr<IPredicate>(new NotDivisibleByAll(nums))));
    }
    if(workMode == 2) {
        Vector<int> nums = getNums(file);
        return PolymorphicPtr<ISet>(new CriteriaSet(PolymorphicPtr<IPredicate>(new DivisibleByOne(nums))));
    }

}
