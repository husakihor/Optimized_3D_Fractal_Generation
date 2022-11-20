#include "Vector.hpp"

namespace isim
{
Vector::Vector(const nlohmann::json& j)
{
	x = j["x"];
	y = j["y"];
	z = j["z"];
}

Vector::Vector(double x, double y, double z) : x(x),
		y(y),
		z(z)
{
}

bool Vector::operator==(const Vector& B) const
{
	return this->x == B.x && this->y == B.y && this->z == B.z;
}

Vector Vector::operator*(const float& s) const
{
	return Vector{this->x * s, this->y * s, this->z * s};
}

void Vector::operator*=(const float& s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

Vector Vector::operator+(const Vector& v) const
{
	return Vector{x + v.x, y + v.y, z + v.z};
}

void Vector::operator+=(const Vector& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

Vector Vector::operator-(const Vector& v) const
{
	return Vector{this->x - v.x, this->y - v.y, this->z - v.z};
}

void Vector::operator-=(const Vector& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

float Vector::GetLength() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector::DotProduct(const Vector& v) const
{
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}

float Vector::Normalize()
{
	float length = this->GetLength();
	this->x /= length;
	this->y /= length;
	this->z /= length;
	return length;
}

Vector Vector::Cross(const Vector& v) const
{
	return Vector{this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x};
}

std::ostream& operator<<(std::ostream& os, const Vector& dt)
{
	os << '(' << dt.x << ',' << dt.y << ',' << dt.z << ')';
	return os;
}
};