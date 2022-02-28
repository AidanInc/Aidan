#include "ReaderData.h"

Triangle::Triangle() {
	a = 0;
	b = 0;
	c = 0;
}

Triangle::Triangle(int A, int B, int C) {
	a = A;
	b = B;
	c = C;
}

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float X, float Y) {
	x = X;
	y = Y;
}

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Light::Light() {
	intensity = 0;
}

Material::Material() {
	transparency = false;
	reflectivity = 0;
}

MapData::MapData() {
	xTiling = 0;
	yTiling = 0;
}