#pragma once

#include <stdint.h>
#include <box2d/b2_types.h>

class Bitmask
{
public:
	Bitmask();

	void SetMask(Bitmask& other);
	uint64_t GetMask() const;
	uint16 GetMask16() const;

	bool GetBit(int pos) const;
	void SetBit(int pos, bool on);

	void SetBit(int pos);
	void ClearBit(int pos);

	void Clear();

private:
	uint64_t bits;
};
