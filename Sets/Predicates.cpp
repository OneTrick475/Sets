#include "Predicates.h"

NotDivisibleByAll::NotDivisibleByAll(const Vector<int>& nums) : nums(nums) {}

bool NotDivisibleByAll::operator()(int x) const {
    for(size_t i = 0; i < nums.len(); i++) {
		if (x % nums[i] == 0)
			return false;
    }
	return true;
}

IPredicate* NotDivisibleByAll::clone() const {
	return new NotDivisibleByAll(*this);
}


DivisibleByOne::DivisibleByOne(const Vector<int>& nums) : nums(nums) {}

bool DivisibleByOne::operator()(int x) const {
	bool divisible = false;
	for (size_t i = 0; i < nums.len(); i++) {
		if (x % nums[i] == 0 && divisible)
			return false;
		if (x % nums[i] == 0)
			divisible = true;
	}
	return divisible;
}

IPredicate* DivisibleByOne::clone() const {
	return new DivisibleByOne(*this);
}

