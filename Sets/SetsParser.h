#pragma once
#include "ISet.h"
#include "MyString.h"
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

class SetsParser {
	PolymorphicPtr<ISet> set;

	Vector<int> getNums(std::istream& file) const;
	PolymorphicPtr<ISet> readSet(const MyString& fileName = "sets.dat") const;

public:
	void run();
};
