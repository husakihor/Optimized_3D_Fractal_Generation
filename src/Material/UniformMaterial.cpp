#include "UniformMaterial.hpp"

namespace isim
{
UniformMaterial::UniformMaterial(const Color& c, float kd) : m_color(c),
		m_kd(kd)
{
}

MaterialInfo UniformMaterial::getInfo(const Ray& ray)
{
	return MaterialInfo{m_color, m_kd};
}
};