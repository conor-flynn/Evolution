#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

class Vector2 {
private:
	float x, y;
public:

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2 &vector);

	float getX() const;
	float getY() const;
	void setX(float x);
	void addX(float x);
	void setY(float y);
	void addY(float y);

	Vector2 operator-(const Vector2& other);
	Vector2 operator+(const Vector2& other);


	static float distance(const Vector2 &a, const Vector2 &b);
	static Vector2 subtract(const Vector2 &b, const Vector2 &a);
	static Vector2 add(const Vector2 &a, const Vector2 &b);
	static float dot(const Vector2 &a, const Vector2 &b);
	static float angle(const Vector2 &a, const Vector2 &b);

	Vector2 scale(float value) const;
	Vector2 rotate(float value) const;
	Vector2 add(const Vector2 &a) const;
	float length() const;

	void scale(float value);
};

#endif