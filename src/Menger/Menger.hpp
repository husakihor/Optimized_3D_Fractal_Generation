#pragma once

#include "Object/Cube/Cube.hpp"

#include <vector>

namespace isim
{
class Menger
{
public:
	void transform(const Vector& point);
	void reset();
	const Vector& getBottomLeft() const;
	void print();
private:

	FRIEND_TEST(menger, constructor);
	FRIEND_TEST(menger, transform);
	FRIEND_TEST(menger, generateFirstIteration);
	FRIEND_TEST(menger, generateSecondIteration);
	FRIEND_TEST(menger, genereteZeroIteration);
	FRIEND_TEST(menger, print);
	FRIEND_TEST(menger, generateThirdIteration);
	FRIEND_TEST(menger, save);
	FRIEND_TEST(menger, initMenger);
	FRIEND_TEST(menger, reset);
	FRIEND_TEST(menger, getCenter);
	FRIEND_TEST(menger, intersect);
	FRIEND_TEST(menger, intersect2Generation);
	FRIEND_TEST(menger, intersect3Generation);
	FRIEND_TEST(menger, intersect4Generation);

	Menger(double sideLength, const Vector& center, int nbIterations);
	void initMenger();

protected:

	Vector m_originCenter;
	double m_originLength;
	Vector m_center;
	int m_nbIterations;
	double m_length;
	std::set<std::unique_ptr<Cube>> m_cubes;

	static void
	transformCube(double newCubeLength, const std::unique_ptr<Cube>& cube, const std::unique_ptr<Cube>& originCube,
				  int x, int y, int z);
	double getSideLength() const;
	bool intersect(Ray& ray);
	static const Vector& getCenterFromIntersection(const Ray& ray);
};
};
