#include "Cube.hpp"
#include "Material/UniformMaterial.hpp"
#include "Vector/Vector.hpp"

#include <iostream>

namespace isim
{
static ObjectFactory<Cube> factory("cube");

Cube::Cube(const nlohmann::json& json) : MeshObject(json),
		m_sideLength(json["length"]),
		m_mat(new UniformMaterial(Color(255, 0, 0), 1.0))
{
}

Cube::Cube(const Vector& position, double length) : MeshObject(position),
		m_sideLength(length),
		m_mat(new UniformMaterial(Color(255, 0, 0), 1.0))
{
	m_isEmpty = false;
}

double Cube::getSideLength() const
{
	return m_sideLength;
}

void Cube::setSideLength(double length)
{
	m_sideLength = length;
}

const std::unique_ptr<Material>& Cube::getMaterial(const Ray& ray) const
{
	return m_mat;
}

void Cube::RayIntersectsTriangle(const Plane& T, Ray& ray) const
{
	std::pair<Vector, Vector> edges(T.B - T.A, T.C - T.A);
	Vector h = ray.dir.Cross(edges.second);
	double determinant = edges.first.DotProduct(h);
	const double epsilon = 0.0000001;
	if (abs(determinant) < epsilon)
	{
		return;
	}
	double inverseDeterminant = 1.0 / determinant;
	Vector distStartA = ray.startpos - T.A;
	double u = inverseDeterminant * distStartA.DotProduct(h);
	if (u < 0.0 || u > 1.0)
	{
		return;
	}
	Vector q = distStartA.Cross(edges.first);
	double v = inverseDeterminant * ray.dir.DotProduct(q);
	if (v < 0.0 || u + v > 1.0)
	{
		return;
	}
	double t = inverseDeterminant * edges.second.DotProduct(q);
	Vector endpos = ray.startpos + ray.dir * t;
	double distance = (endpos - ray.startpos).GetLength();
	if (distance < ray.distance)
	{
		ray.distance = distance;
		ray.endpos = endpos;
		ray.obj = this;
	}
}

std::string toBinary(int n)
{
	std::string r;
	while (n != 0)
	{
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	while (r.size() != 3)
	{
		r = "0" + r;
	}
	return r;
}

std::vector<Vector> Cube::getPoints() const
{
	auto points = std::vector<Vector>();
	for (int i = 0; i < 8; i++)
	{
		std::string binary = toBinary(i);
		int signX = binary[0] == '0' ? -1 : 1;
		int signY = binary[1] == '0' ? -1 : 1;
		int signZ = binary[2] == '0' ? -1 : 1;
		double newX = m_position.x + (m_sideLength / 2) * signX;
		double newY = m_position.y + (m_sideLength / 2) * signY;
		double newZ = m_position.z + (m_sideLength / 2) * signZ;
		const Vector& newPoint = Vector(newX, newY, newZ);
		points.emplace_back(newPoint);

	}
	return points;
}

std::vector<Plane> getTriangles(std::vector<Vector> points)
{
	auto triangles = std::vector<Plane>();
	triangles.emplace_back(Plane(points[0], points[4], points[5]));
	triangles.emplace_back(Plane(points[0], points[4], points[1]));
	triangles.emplace_back(Plane(points[1], points[3], points[5]));
	triangles.emplace_back(Plane(points[1], points[3], points[7]));
	triangles.emplace_back(Plane(points[3], points[2], points[6]));
	triangles.emplace_back(Plane(points[3], points[2], points[7]));
	triangles.emplace_back(Plane(points[0], points[2], points[6]));
	triangles.emplace_back(Plane(points[0], points[2], points[4]));
	triangles.emplace_back(Plane(points[0], points[1], points[3]));
	triangles.emplace_back(Plane(points[0], points[1], points[2]));
	triangles.emplace_back(Plane(points[4], points[6], points[7]));
	triangles.emplace_back(Plane(points[4], points[6], points[5]));
	return triangles;
}

bool Cube::isIntersected(Ray& ray) const
{
	auto points = getPoints();
	auto planes = getTriangles(points);
	for (auto& plane : planes)
	{
		RayIntersectsTriangle(plane, ray);
	}
	return ray.didHit();
}

bool Cube::operator==(const Cube& B) const
{
	return m_sideLength == B.m_sideLength && m_position == B.m_position;
}

bool Cube::isEmpty() const
{
	return m_isEmpty;
}

void Cube::setIsEmpty(bool isEmpty)
{
	m_isEmpty = isEmpty;
}

std::ostream& operator<<(std::ostream& os, const Cube& c)
{
	return std::cout << c.getPosition();
}
};
