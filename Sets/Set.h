#pragma once
#include "ISet.h"
#include "Vector.hpp"

class Set : public ISet {
	Vector<int> nums;
public:
	Set(const Vector<int>& nums);

	ISet* clone() const override;
	bool contains(int element) const override;
};
