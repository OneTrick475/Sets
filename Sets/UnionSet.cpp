#include "UnionSet.h"

UnionSet::UnionSet(const Vector<PolymorphicPtr<ISet>>& sets) : sets(sets) {}

ISet* UnionSet::clone() const {
	return new UnionSet(*this);
}

bool UnionSet::contains(int element) const {
	for (size_t i = 0; i < sets.len(); i++) {
		if (sets[i]->contains(element))
			return true;
	}
	return false;
}

