#pragma once
#include "Vector.hpp"
#include "IPredicate.h"

class NotDivisibleByAll : public IPredicate{
private:
	Vector<int> nums;
public:
	NotDivisibleByAll() = default;
	NotDivisibleByAll(const Vector<int>& nums);

	IPredicate* clone() const override;

	bool operator()(int x) const override;

	~NotDivisibleByAll() override = default;
};

class DivisibleByOne : public IPredicate {
private:
	Vector<int> nums;
public:
	DivisibleByOne() = default;
	DivisibleByOne(const Vector<int>& nums);

	IPredicate* clone() const override;

	bool operator()(int x) const override;

	~DivisibleByOne() override = default;
};