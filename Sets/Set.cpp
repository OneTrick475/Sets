#include "Set.h"

Set::Set(const Vector<int>& nums) : nums(nums) {}

ISet* Set::clone() const {
	return new Set(*this);
}

bool Set::contains(int element) const {
	for(size_t i = 0; i < nums.len(); i++) {
		if (nums[i] == element)
			return true;
	}
	return false;
}

