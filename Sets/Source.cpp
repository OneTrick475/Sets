#include <iostream>
#include "CriteriaSet.h"
#include "IntersectionSet.h"
#include "PolymorphicPtr.hpp"
#include "ISet.h"
#include "Set.h"
#include "UnionSet.h"
#include "Predicates.h"

int main() {
	Vector<int> vector;
	vector.pushBack(2);
	vector.pushBack(3);

	CriteriaSet s1(PolymorphicPtr<IPredicate>(new NotDivisibleByAll(vector)));

	for (int i = 0; i <= 100; i++) {
		if (s1.contains(i))
			std::cout << i << ' ';
	}
}
