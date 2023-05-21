#include "CriteriaSet.h"

CriteriaSet::CriteriaSet(const PolymorphicPtr<IPredicate>& pred) : pred(pred) {}

bool CriteriaSet::contains(int element) const {
	return (*pred)(element);
}

ISet* CriteriaSet::clone() const {
	return new CriteriaSet(*this);
}

