#pragma once

#include "Vector/Vector.hpp"

#include <limits>

namespace isim
{
class Transform;
struct Ray
{
	Ray() : distance(std::numeric_limits<double>::infinity()),
			obj(nullptr),
			startpos(0, 0, 0),
			dir(0, 0, 0),
			endpos(0, 0, 0)
	{
	};
	Vector startpos;
	Vector dir;

	Vector endpos;
	double distance;

	const Transform* obj;

	bool didHit()
	{
		return this->distance != std::numeric_limits<double>::infinity();
	}
};
};