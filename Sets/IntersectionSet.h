#pragma once
#include "Iset.h"
#include "Vector.hpp"
#include "PolymorphicPtr.hpp"

class IntersectionSet : public ISet {
	Vector<PolymorphicPtr<ISet>> sets;
public:
	IntersectionSet(const Vector<PolymorphicPtr<ISet>>& sets);

	ISet* clone() const override;
	bool contains(int element) const override;
	~IntersectionSet() override = default;
};
