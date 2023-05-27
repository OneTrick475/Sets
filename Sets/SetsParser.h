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
	class Iterator {
		const SetsParser* set;
		int num;
		bool isOver;
		Iterator(int num, bool isOver, const SetsParser* set);
	public:
		Iterator& operator++();
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		int operator*() const;
		friend class SetsParser;
	};

	SetsParser();

	Iterator begin() const;
	Iterator end() const;
	void getInRange(int low, int high);
	void run();
	// run function is for starting the cli
	// with getInRange you can manually get numbers in a range
	// example usage of the iterator:
	// SetsParser sets;
	// for(SetsParser::Iterator it = sets.begin(); it != sets.end(); ++it){
	//		std::cout << *it;}  or do smth else with the value
	// however theres a major problem with the iterator -> read in cpp file.
};
