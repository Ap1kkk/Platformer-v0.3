#include "Bitmask.h"

Bitmask::Bitmask() : bits(0)
{
}

void Bitmask::SetMask(Bitmask& other)
{
	bits = other.GetMask();
}

uint64_t Bitmask::GetMask() const
{
	return bits;
}

bool Bitmask::GetBit(int pos) const
{
	return (bits & (static_cast<unsigned long long>(1) << pos)) != 0;
}

void Bitmask::SetBit(int pos, bool on)
{
	if (on)
	{
		SetBit(pos);
	}
	else
	{
		ClearBit(pos);
	}
}

void Bitmask::SetBit(int pos)
{
	bits = bits | static_cast<unsigned long long>(1) << pos;
}

void Bitmask::ClearBit(int pos)
{
	bits = bits & ~(static_cast<unsigned long long>(1) << pos);
}

void Bitmask::Clear()
{
	bits = 0;
}
