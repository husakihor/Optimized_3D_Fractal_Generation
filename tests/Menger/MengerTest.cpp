#include "Menger/Menger.hpp"

#include <gtest/gtest.h>
#include <string>

namespace isim
{
TEST(menger, constructor)
{
	const int sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;

	Menger menger(sideLength, point, nbIteration);
	const int expectedNumberOfCubes = 20;
	ASSERT_EQ(expectedNumberOfCubes, menger.m_cubes.size());

	const double expectedLengthCube = 1;

	for (const std::unique_ptr<Cube>& cube : menger.m_cubes)
	{
		ASSERT_EQ(expectedLengthCube, cube->getSideLength());
	}

	ASSERT_EQ(menger.getSideLength(), sideLength);
	ASSERT_EQ(menger.getBottomLeft(), point);
}

TEST(menger, transform)
{
	const int sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;
	Menger menger(sideLength, point, nbIteration);

	const double expectedLengthCube = 1.0 / 3;
	const int expectedNumberOfCubes = 20;
	const double expectedLength = 1;

	Vector newPoint(0, 0, 0);
	menger.transform(newPoint);
	ASSERT_EQ(expectedLength, menger.getSideLength());
	ASSERT_EQ(expectedNumberOfCubes, menger.m_cubes.size());

	for (const std::unique_ptr<Cube>& cube : menger.m_cubes)
	{
		ASSERT_EQ(expectedLengthCube, cube->getSideLength());
	}
}

TEST(menger, reset)
{
	const double sideLength = 3;
	const Vector point = Vector(0, 1, 2);
	const int nbIteration = 0;
	Menger menger(sideLength, point, nbIteration);

	Vector newPoint(0, 0, 0);
	menger.transform(newPoint);
	menger.reset();

	ASSERT_EQ(sideLength, menger.getSideLength());
	ASSERT_EQ(point, menger.m_center);

	Menger mengerOrigin(sideLength, point, nbIteration);

	ASSERT_EQ(menger.m_cubes.size(), mengerOrigin.m_cubes.size());
	const double expectedCubeLength = sideLength / 9;
	for (const auto& m_cube : menger.m_cubes)
	{
		ASSERT_EQ(m_cube->getSideLength(), expectedCubeLength);
	}
}

TEST(menger, intersect)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 0;
	Menger menger(sideLength, center, nbIteration);

	Ray ray;
	ray.startpos = Vector(-5, -1, -1);
	ray.dir = Vector(1, 0, 0);

	ASSERT_TRUE(menger.intersect(ray));
	Vector expected(-1.5, -1, -1);

	ASSERT_EQ(ray.endpos, expected);
}

TEST(menger, getCenter)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 0;
	Menger menger(sideLength, center, nbIteration);

	Ray ray;
	ray.startpos = Vector(-5, -1, -1);
	ray.dir = Vector(1, 0, 0);

	menger.intersect(ray);

	Vector obtainedCenter = isim::Menger::getCenterFromIntersection(ray);
	Vector expectedCenter(-1, -1, -1);
	ASSERT_EQ(obtainedCenter, expectedCenter);
}

TEST(menger, intersect2Generation)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 2;
	Menger menger(sideLength, center, nbIteration);

	Ray ray;
	ray.startpos = Vector(-5, -1, -1);
	ray.dir = Vector(1, 0, 0);

	menger.intersect(ray);
	const Cube* cube = static_cast<const Cube*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / 9);
}

TEST(menger, intersect3Generation)
{
	const double sideLength = 3;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 3;
	Menger menger(sideLength, center, nbIteration);

	Ray ray;
	ray.startpos = Vector(-5, -1, -1);
	ray.dir = Vector(1, 0, 0);

	menger.intersect(ray);
	const Cube* cube = static_cast<const Cube*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / (std::pow(3, nbIteration)));
}


TEST(menger, intersect4Generation)
{
	const double sideLength = 4;
	const Vector center = Vector(0, 0, 0);
	const int nbIteration = 3;
	Menger menger(sideLength, center, nbIteration);

	Ray ray;
	ray.startpos = Vector(-5, -1, -1);
	ray.dir = Vector(1, 0, 0);

	menger.intersect(ray);
	const Cube* cube = static_cast<const Cube*>(ray.obj);
	ASSERT_EQ(cube->getSideLength(), sideLength / (std::pow(3, nbIteration)));
}
};