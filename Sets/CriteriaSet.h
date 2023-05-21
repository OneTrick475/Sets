#pragma once
#include "IPredicate.h"
#include "ISet.h"
#include "PolymorphicPtr.hpp"

class CriteriaSet : public ISet {
	PolymorphicPtr<IPredicate> pred;
public:
	ISet* clone() const override;

	CriteriaSet(const PolymorphicPtr<IPredicate>& pred);

	bool contains(int element) const override;

	~CriteriaSet() override = default;
};