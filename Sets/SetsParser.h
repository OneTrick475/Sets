#pragma once
#include "ISet.h"
#include "MyString.h"
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

class SetsParser {
	PolymorphicPtr<ISet> set;

	MyString readFileName(std::ifstream& file) const;
	Vector<int> readNums(std::istream& file, size_t numberOfElements) const;
	PolymorphicPtr<ISet> readSet(const MyString& fileName = "sets.dat") const;

public:
	void getInRange(int low, int high);
	void run();
};
