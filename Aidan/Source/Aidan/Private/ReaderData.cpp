#include "ReaderData.h"

/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 */
Triangle::Triangle() {
	a = 0;
	b = 0;
	c = 0;
}


/**
 * @brief Construct a new Triangle:: Triangle object
 * 
 * @param A - int value of point 1
 * @param B - int value of point 2
 * @param C - int value of point 3
 */
Triangle::Triangle(int A, int B, int C) {
	a = A;
	b = B;
	c = C;
}

/**
 * @brief Construct a new Vector 2:: Vector 2 object
 * 
 */
Vector2::Vector2() {
	x = 0;
	y = 0;
}

/**
 * @brief Construct a new Vector 2:: Vector 2 object
 * 
 * @param X - x position
 * @param Y  - y position
 */
Vector2::Vector2(float X, float Y) {
	x = X;
	y = Y;
}

/**
 * @brief Construct a new Vector 3:: Vector 3 object
 * 
 */
Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

/**
 * @brief Construct a new Vector 3:: Vector 3 object
 * 
 * @param X - x position
 * @param Y - y position
 * @param Z - z position
 */
Vector3::Vector3(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

/**
 * @brief Construct a new Color:: Color object
 * 
 */
Color::Color() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}


/**
 * @brief Construct a new Light:: Light object
 * 
 */
Light::Light() {
	intensity = 0;
}


/**
 * @brief Construct a new Material:: Material object
 * 
 */
Material::Material() {
	transparency = false;
	reflectivity = 0;
}


/**
 * @brief Construct a new Map Data:: Map Data object
 * 
 */
MapData::MapData() {
	xTiling = 0;
	yTiling = 0;
}