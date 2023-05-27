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

//when trying to generate the next number, the program seems to stop, this is not the case. There is an iterator trying to find the first number(starting
//at the min value for int which causes it to be very slow) however since there is no way to know where we should start beforehand and storing the numbers
//for a criteria set would also be a major problem. I could not find a solution to this problem

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
    file.close();
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
            std::cout << i << " ";
	}
    std::cout << '\n';
}

SetsParser::SetsParser() {
    set = readSet();
}

void SetsParser::run() {
    Iterator it = end();

    while(true) {
        std::cout << "chose an option\n1. Nums in range [a, b]\n2. Next num\n3. Exit\n";
        int option;
        std::cin >> option;
        while (std::cin.fail() || option < 1 || option > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printf("Invalid. Enter a number between %d and %d\n", 1, 3);
            std::cin >> option;
        }
        if(option == 1) {
            std::cout << "Enter 2 numbers: ";
            int a;
            int b;
            std::cin >> a;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "invalid. enter a number\n";
                std::cin >> a;
            }
            std::cin >> b;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "invalid. enter a number\n";
                std::cin >> b;
            }
            getInRange(a, b);
        }
        if(option == 2) {
	        if(it == end()) {
                it = begin();
	        }
            std::cout << *it;
            ++it;
        }
        if(option == 3) 
            return;
    }
}

SetsParser::Iterator::Iterator(int num, bool isOver, const SetsParser* set) : num(num), isOver(isOver), set(set) {}

int SetsParser::Iterator::operator*() const {
    return num;
}

SetsParser::Iterator& SetsParser::Iterator::operator++() {
    if (num == std::numeric_limits<int>::max()) {
            isOver = true;
            return *this;
        }
    if (isOver)
        throw std::logic_error("there arent any other elements");

    while (true) {
        num++;
        if (set->set->contains(num))
            return *this;
        if (num == std::numeric_limits<int>::max()) {
            isOver = true;
            return *this;
        }
    }
}

SetsParser::Iterator SetsParser::begin() const {
    int i = std::numeric_limits<int>::min();
    while(true) {
    	if(set->contains(i)) 
            return Iterator(i, false, this);
        if (i == std::numeric_limits<int>::max())
            return Iterator(i, true, this);
        i++;
    }
}

SetsParser::Iterator SetsParser::end() const {
    return Iterator(std::numeric_limits<int>::max(), true, this);
}

bool SetsParser::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

bool SetsParser::Iterator::operator==(const Iterator& other) const {
    return (set == other.set) && (isOver == other.isOver) && (num == other.num);
}


