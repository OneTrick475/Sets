#include "SetsParser.h"
#include <fstream>
#include <iostream>
#include "Set.h"
#include "IPredicate.h"
#include "CriteriaSet.h"
#include "IntersectionSet.h"
#include "Predicates.h"
#include "UnionSet.h"
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
        Vector<int> nums = readNums(file, numberOfElements);
        return PolymorphicPtr<ISet>(new Set(nums));
    }
    if(workMode == 1) {
        Vector<int> nums = readNums(file, numberOfElements);
        return PolymorphicPtr<ISet>(new CriteriaSet(PolymorphicPtr<IPredicate>(new NotDivisibleByAll(nums))));
    }
    if(workMode == 2) {
        Vector<int> nums = readNums(file, numberOfElements);
        return PolymorphicPtr<ISet>(new CriteriaSet(PolymorphicPtr<IPredicate>(new DivisibleByOne(nums))));
    }
    if(workMode == 3) {
        Vector<PolymorphicPtr<ISet>> sets;
	    for(size_t i = 0; i < numberOfElements; i++) {
            sets.pushBack(readSet(readFileName(file)));
	    }
        return PolymorphicPtr<ISet>(new UnionSet(sets));
    }
    if (workMode == 4) {
        Vector<PolymorphicPtr<ISet>> sets;
        for (size_t i = 0; i < numberOfElements; i++) {
            sets.pushBack(readSet(readFileName(file)));
        }
        return PolymorphicPtr<ISet>(new IntersectionSet(sets));
    }
}

MyString SetsParser::readFileName(std::ifstream& file) const {
    MyString fileName;
    char ch[2]{ '\0' };
    while(true) {
        file.read((char*)&ch, sizeof(char));
        fileName += ch;
        if (strcmp(ch, "\0") == 0)
            return fileName;
    }
}

Vector<int> SetsParser::readNums(std::istream& file, size_t numberOfElements) const {
    Vector<int> nums;
    for(size_t i = 0; i < numberOfElements; i++) {
        int x;
        file.read((char*)&x, sizeof(int));
        nums.pushBack(x);
    }
    return nums;
}

void SetsParser::getInRange(int low, int high) {
	for(int i = low; i <= high; i++) {
        if (set->contains(i))
            std::cout << i;
	}
}


void SetsParser::run() {
    set = readSet();
}

