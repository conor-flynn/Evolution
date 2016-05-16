#include "Vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2 & vector) {
	this->x = vector.getX();
	this->y = vector.getY();
}

float Vector2::getX() const { return this->x; }
float Vector2::getY() const { return this->y; }
void Vector2::setX(float x) {
	this->x = x;
}
void Vector2::addX(float x) {
	this->x += x;
}
void Vector2::setY(float y) {
	this->y = y;
}
void Vector2::addY(float y) {
	this->y += y;
}

Vector2 Vector2::operator-(const Vector2 & other) {
	Vector2 res = Vector2();

	res.setX(this->getX() - other.getX());
	res.setY(this->getY() - other.getY());

	return res;
}

Vector2 Vector2::operator+(const Vector2 & other) {
	Vector2 res = Vector2();

	res.setX(this->getX() + other.getX());
	res.setY(this->getY() + other.getY());

	return res;
}







float Vector2::distance(const Vector2 & a, const Vector2 & b) {
	return pow(pow(a.getX() - b.getX(),2) + pow(a.getY() - b.getY(),2),0.5f);
}

Vector2 Vector2::subtract(const Vector2 &b, const Vector2 &a) {
	return Vector2(b.getX() - a.getX(), b.getY() - a.getY());
}
Vector2 Vector2::add(const Vector2 &a, const Vector2 &b) {
	return Vector2(a.getX() + b.getX(), a.getY() + b.getY());
}
float Vector2::dot(const Vector2 &a, const Vector2 &b) {
	return (a.getX() * b.getX()) + (a.getY() * b.getY());
}

float Vector2::angle(const Vector2 & a, const Vector2 & b) {
	return acos( Vector2::dot(a,b) / (a.length() * b.length())) * (180.0f / 3.1415f);
}

Vector2 Vector2::scale(float value) const {
	return Vector2(this->getX() * value, this->getY() * value);
}

Vector2 Vector2::rotate(float value) const {
	float rad = (value / 180.0f) * 3.1415f;;
	float newx = (getX() * cos(rad)) - (getY() * sin(rad));
	float newy = (getX() * sin(rad)) + (getY() * cos(rad));
	return Vector2(newx, newy);
}

Vector2 Vector2::add(const Vector2 & a) const {
	return add(*this, a);
}

float Vector2::length() const {
	return pow( pow(x,2.0f) + pow(y,2.0f) , 0.5f);
}

void Vector2::scale(float value) {
	this->x *= value;
	this->y *= value;
}
