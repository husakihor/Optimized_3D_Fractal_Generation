#pragma once

#include "Material.hpp"

namespace isim
{
class UniformMaterial : public Material
{
public:
	UniformMaterial(const Color& c, float kd);
	virtual MaterialInfo getInfo(const Ray& ray) override;
private:
	Color m_color;
	float m_kd;
};
};