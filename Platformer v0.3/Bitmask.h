#pragma once

#include <stdint.h>

class Bitmask
{
public:
	Bitmask();

	void SetMask(Bitmask& other);
	uint64_t GetMask() const;

	bool GetBit(int pos) const;
	void SetBit(int pos, bool on);

	void SetBit(int pos);
	void ClearBit(int pos);

	void Clear();

private:
	uint64_t bits;
};
