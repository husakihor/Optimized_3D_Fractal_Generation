#pragma once

#include "Image/Color.hpp"
#include "Scene/Ray.hpp"

namespace isim
{
struct MaterialInfo
{
	Color color;
	float kd;
};

class Material
{
public:
	virtual ~Material() = default;
	virtual MaterialInfo getInfo(const Ray& ray) = 0;
};
};