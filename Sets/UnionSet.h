#pragma once
#include "ISet.h"
#include "Vector.hpp"
#include "PolymorphicPtr.hpp"

class UnionSet : public ISet{
	Vector<PolymorphicPtr<ISet>> sets;
public:
	UnionSet(const Vector<PolymorphicPtr<ISet>>& sets);

	ISet* clone() const override;
	bool contains(int element) const override;

	~UnionSet() override = default;
};