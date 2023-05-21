#include "IntersectionSet.h"

IntersectionSet::IntersectionSet(const Vector<PolymorphicPtr<ISet>>& sets) : sets(sets) {}

ISet* IntersectionSet::clone() const {
	return new IntersectionSet(*this);
}

bool IntersectionSet::contains(int element) const {
	for (size_t i = 0; i < sets.len(); i++) {
		if (!sets[i]->contains(element))
			return false;
	}
	return true;
}

