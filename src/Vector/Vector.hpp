#pragma once

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

namespace isim
{
struct Vector
{
public:
	explicit Vector(const nlohmann::json& json);
	Vector(double x, double y, double z);

	bool operator==(const Vector& B) const;

	Vector operator*(const float& s) const;

	void operator*=(const float& s);

	Vector operator+(const Vector& v) const;

	void operator+=(const Vector& v);

	Vector operator-(const Vector& v) const;

	void operator-=(const Vector& v);

	float GetLength() const;

	float DotProduct(const Vector& v) const;

	float Normalize();

	Vector Cross(const Vector& v) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector& dt);

	double x, y, z;
};
};
