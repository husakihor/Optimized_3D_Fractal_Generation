#pragma once

#include <cstdint>
#include <ostream>

namespace isim
{
struct Color
{
	Color() : r(0),
			g(0),
			b(0),
			a(255)
	{
	}

	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r(r),
			g(g),
			b(b),
			a(255)
	{
	}

	Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) : r(r),
			g(g),
			b(b),
			a(a)
	{
	}

	std::uint8_t r;
	std::uint8_t g;
	std::uint8_t b;
	std::uint8_t a;

	friend inline std::ostream& operator<<(std::ostream& os, const Color& dt)
	{
		os << "(R:" << std::to_string(dt.r) << ", G:" << std::to_string(dt.g) << ", B:" << std::to_string(dt.b)
		   << ", A:" << std::to_string(dt.a) << ")";
		return os;
	}
};
};
