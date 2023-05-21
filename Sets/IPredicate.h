#pragma once

class IPredicate {
public:
	virtual bool operator()(int x) const = 0;
	virtual IPredicate* clone() const = 0;
	virtual ~IPredicate() = default;
};