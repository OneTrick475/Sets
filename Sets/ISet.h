#pragma once

class ISet {
public:
	virtual ISet* clone() const = 0;

	virtual bool contains(int element) const = 0;

	virtual ~ISet() = default;
};