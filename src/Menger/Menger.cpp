#include "Menger.hpp"

namespace isim
{
Menger::Menger(double sideLength, const Vector& center, int nbIterations) : m_length(sideLength),
		m_center(center),
		m_nbIterations(nbIterations),
		m_originCenter(center),
		m_originLength(sideLength)
{
	initMenger();
}

double Menger::getSideLength() const
{
	return m_length;
}

const Vector& Menger::getBottomLeft() const
{
	return m_center;
}

void Menger::print()
{
	std::cout << m_cubes.size() << std::endl;
	for (const std::unique_ptr<Cube>& cube : m_cubes)
	{
		std::cout << cube << std::endl;
	}
}

void Menger::transform(const Vector& point)
{
	m_center = point;
	m_length /= 3;
	const double newCubeLength = m_length / 3;
	std::unique_ptr<Cube> originCube(new Cube(point, m_length));
	for (const std::unique_ptr<Cube>& cube : m_cubes)
	{
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 and y == 0)
				{
					continue;
				}
				for (int z = -1; z < 2; z++)
				{
					if ((x == 0 and y == 0) or (x == 0 or y == 0) and z == 0)
					{
						continue;
					}
					transformCube(newCubeLength, cube, originCube, x, y, z);
				}
			}
		}
	}
}

void Menger::transformCube(const double newCubeLength, const std::unique_ptr<Cube>& cube,
						   const std::unique_ptr<Cube>& originCube, int x, int y, int z)
{
	auto pos = originCube->getPosition();
	double xPos = pos.x + x * newCubeLength;
	double yPos = pos.y + y * newCubeLength;
	double zPos = pos.z + z * newCubeLength;
	cube->setPosition(Vector{xPos, yPos, zPos});
	cube->setSideLength(newCubeLength);
}

void Menger::initMenger()
{
	double newRay = m_length / 3;
	Cube originCube(m_center, m_length);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 and y == 0)
			{
				continue;
			}
			for (int z = -1; z < 2; z++)
			{
				if ((x == 0 and y == 0) or (x == 0 or y == 0) and z == 0)
				{
					continue;
				}
				auto pos = originCube.getPosition();
				double xPos = pos.x + x * newRay;
				double yPos = pos.y + y * newRay;
				double zPos = pos.z + z * newRay;
				m_cubes.emplace(new Cube(Vector{xPos, yPos, zPos}, newRay));
			}
		}
	}
}

void Menger::reset()
{
	m_length = m_originLength;
	m_center = m_originCenter;
	transform(m_center);
	m_length *= 3;
}

bool Menger::intersect(Ray& ray)
{
	for (const auto& cube : m_cubes)
	{
		cube->isIntersected(ray);
	}
	for (; ray.didHit() && m_nbIterations - 1 > 0; m_nbIterations--)
	{
		transform(getCenterFromIntersection(ray));
		for (const auto& cube : m_cubes)
		{
			cube->isIntersected(ray);
		}
	}
	return ray.didHit();
}

const Vector& Menger::getCenterFromIntersection(const Ray& ray)
{
	auto intersectedCube = static_cast<const Cube*>(ray.obj);
	return intersectedCube->getPosition();
}
};