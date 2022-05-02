// source shared between AliReview and Renderer - patch changes
#include "DataTypes.h"
#include <math.h>

// Vector2 definitions
Vector2::Vector2() : u(0), v(0) {}

// Vector3 definitions
Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::operator[](int index) const {
    return (&x)[index];
}

float& Vector3::operator[](int index) {
    return (&x)[index];
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& a) {
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

Vector3& Vector3::operator*=(const float a) {
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

Vector3 Vector3::cross(const Vector3& a) const {
    return Vector3(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x);
}

float Vector3::length() const {
    return sqrt( lengthSquared() );
}

float Vector3::lengthSquared() const {
    return x*x + y*y + z*z;
}

// fast Newton-Raphson iteration with a clever first approximation
// popularized by john carmack in quake engines
float invSqrt(float x) {
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}

Vector3& Vector3::normalize() {
    float invLength;
    invLength = invSqrt( lengthSquared() );
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

Vector3 operator+(Vector3 a, const Vector3& b) {
    a += b;
    return a;
}

Vector3 operator-(Vector3 a, const Vector3& b) {
    a -= b;
    return a;
}

float operator*(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 operator*(float a, Vector3 b) {
    b.x *= a;
    b.y *= a;
    b.z *= a;
    return b;
}

// Vector4 definitions

Vector4::Vector4() : x(0), y(0), z(0), w(0) {}

Vector4::Vector4(float X, float Y, float Z, float W) {
    x = X;
    y = Y;
    z = Z;
    w = W;
}

float Vector4::operator[](int index) const {
    return (&x)[index];
}

float& Vector4::operator[](int index) {
    return (&x)[index];
}

Vector4 Vector4::operator-() const {
    return Vector4(-x, -y, -z, -w);
}

Vector4& Vector4::operator+=(const Vector4& a) {
    x += a.x;
    y += a.y;
    z += a.z; 
    w += a.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& a) {
    x -= a.x;
    y -= a.y;
    z -= a.z;
    w -= a.w;
    return *this;
}

Vector4& Vector4::operator*=(float a) {
    x *= a;
    y *= a;
    z *= a;
    w *= a;
    return *this;
}

float Vector4::length() const {
    return sqrt(lengthSquared());
}

float Vector4::lengthSquared() const {
    return x*x + y*y + z*z + w*w;
}

void Vector4::normalize() {
    float invLength;
    invLength = invSqrt( lengthSquared() );
    x *= invLength;
    y *= invLength;
    z *= invLength;
    w *= invLength;
}

Vector4 operator+(Vector4 a, const Vector4& b) {
    a += b;
    return a;
}

Vector4 operator-(Vector4 a, const Vector4& b) {
    a -= b;
    return a;
}

float operator*(const Vector4& a, const Vector4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 operator*(float a, Vector4 b) {
    b.x *= a;
    b.y *= a;
    b.z *= a;
    b.w *= a;
    return b;
}

// triangle definitions
Triangle::Triangle() : a(0), b(0), c(0) {}

Triangle::Triangle(int A, int B, int C) : a(A), b(B), c(C) {}

Color::Color() : r(0), g(0), b(0) {}

// Vector44 definitions
Matrix44::Matrix44() {
    identity();
}

Matrix44::Matrix44(const Vector4& row0,
                   const Vector4& row1,
                   const Vector4& row2,
                   const Vector4& row3) {
    matrix[0] = row0;
    matrix[1] = row1;
    matrix[2] = row2;
    matrix[3] = row3;
}

Matrix44::Matrix44(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) {
    matrix[0][0] = m00; matrix[0][1] = m01; matrix[0][2] = m02; matrix[0][3] = m03;
    matrix[1][0] = m10; matrix[1][1] = m11; matrix[1][2] = m12; matrix[1][3] = m13;
    matrix[2][0] = m20; matrix[2][1] = m21; matrix[2][2] = m22; matrix[2][3] = m23;
    matrix[3][0] = m30; matrix[3][1] = m31; matrix[3][2] = m32; matrix[3][3] = m33;
}

Vector4 Matrix44::operator[](int index) const {
    return matrix[index];
}

Vector4& Matrix44::operator[](int index) {
    return matrix[index];
}

Matrix44& Matrix44::operator+=(const Matrix44& a) {
    matrix[0].x += a[0].x; matrix[0].y += a[0].y; matrix[0].z += a[0].z; matrix[0].w += a[0].w;
    matrix[1].x += a[1].x; matrix[1].y += a[1].y; matrix[1].z += a[1].z; matrix[1].w += a[1].w;
    matrix[2].x += a[2].x; matrix[2].y += a[2].y; matrix[2].z += a[2].z; matrix[2].w += a[2].w;
    matrix[3].x += a[3].x; matrix[3].y += a[3].y; matrix[3].z += a[3].z; matrix[3].w += a[3].w;
    return *this;
}

Matrix44& Matrix44::operator-=(const Matrix44& a) {
    matrix[0].x -= a[0].x; matrix[0].y -= a[0].y; matrix[0].z -= a[0].z; matrix[0].w -= a[0].w;
    matrix[1].x -= a[1].x; matrix[1].y -= a[1].y; matrix[1].z -= a[1].z; matrix[1].w -= a[1].w;
    matrix[2].x -= a[2].x; matrix[2].y -= a[2].y; matrix[2].z -= a[2].z; matrix[2].w -= a[2].w;
    matrix[3].x -= a[3].x; matrix[3].y -= a[3].y; matrix[3].z -= a[3].z; matrix[3].w -= a[3].w;
    return *this;
}

Matrix44& Matrix44::operator*=(const Matrix44& a) {
    *this = (*this) * a;
    return *this;
}

Matrix44 Matrix44::operator*(const Matrix44& a) const {
    Transform r;
    r.matrix[0][0] = matrix[0][0] * a.matrix[0][0] + matrix[0][1] * a.matrix[1][0] + matrix[0][2] * a.matrix[2][0] + matrix[0][3] * a.matrix[3][0];
    r.matrix[0][1] = matrix[0][0] * a.matrix[0][1] + matrix[0][1] * a.matrix[1][1] + matrix[0][2] * a.matrix[2][1] + matrix[0][3] * a.matrix[3][1];
    r.matrix[0][2] = matrix[0][0] * a.matrix[0][2] + matrix[0][1] * a.matrix[1][2] + matrix[0][2] * a.matrix[2][2] + matrix[0][3] * a.matrix[3][2];
    r.matrix[0][3] = matrix[0][0] * a.matrix[0][3] + matrix[0][1] * a.matrix[1][3] + matrix[0][2] * a.matrix[2][3] + matrix[0][3] * a.matrix[3][3];
 
    r.matrix[1][0] = matrix[1][0] * a.matrix[0][0] + matrix[1][1] * a.matrix[1][0] + matrix[1][2] * a.matrix[2][0] + matrix[1][3] * a.matrix[3][0];
    r.matrix[1][1] = matrix[1][0] * a.matrix[0][1] + matrix[1][1] * a.matrix[1][1] + matrix[1][2] * a.matrix[2][1] + matrix[1][3] * a.matrix[3][1];
    r.matrix[1][2] = matrix[1][0] * a.matrix[0][2] + matrix[1][1] * a.matrix[1][2] + matrix[1][2] * a.matrix[2][2] + matrix[1][3] * a.matrix[3][2];
    r.matrix[1][3] = matrix[1][0] * a.matrix[0][3] + matrix[1][1] * a.matrix[1][3] + matrix[1][2] * a.matrix[2][3] + matrix[1][3] * a.matrix[3][3];
 
    r.matrix[2][0] = matrix[2][0] * a.matrix[0][0] + matrix[2][1] * a.matrix[1][0] + matrix[2][2] * a.matrix[2][0] + matrix[2][3] * a.matrix[3][0];
    r.matrix[2][1] = matrix[2][0] * a.matrix[0][1] + matrix[2][1] * a.matrix[1][1] + matrix[2][2] * a.matrix[2][1] + matrix[2][3] * a.matrix[3][1];
    r.matrix[2][2] = matrix[2][0] * a.matrix[0][2] + matrix[2][1] * a.matrix[1][2] + matrix[2][2] * a.matrix[2][2] + matrix[2][3] * a.matrix[3][2];
    r.matrix[2][3] = matrix[2][0] * a.matrix[0][3] + matrix[2][1] * a.matrix[1][3] + matrix[2][2] * a.matrix[2][3] + matrix[2][3] * a.matrix[3][3];
 
    r.matrix[3][0] = matrix[3][0] * a.matrix[0][0] + matrix[3][1] * a.matrix[1][0] + matrix[3][2] * a.matrix[2][0] + matrix[3][3] * a.matrix[3][0];
    r.matrix[3][1] = matrix[3][0] * a.matrix[0][1] + matrix[3][1] * a.matrix[1][1] + matrix[3][2] * a.matrix[2][1] + matrix[3][3] * a.matrix[3][1];
    r.matrix[3][2] = matrix[3][0] * a.matrix[0][2] + matrix[3][1] * a.matrix[1][2] + matrix[3][2] * a.matrix[2][2] + matrix[3][3] * a.matrix[3][2];
    r.matrix[3][3] = matrix[3][0] * a.matrix[0][3] + matrix[3][1] * a.matrix[1][3] + matrix[3][2] * a.matrix[2][3] + matrix[3][3] * a.matrix[3][3];
    return r;
}

void Matrix44::transpose() {
    Matrix44 transpose;
    int		i, j;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            transpose[i][j] = matrix[j][i];
        }
    }
    *this = transpose;
}

void Matrix44::zero() {
    *this = Matrix44( Vector4(0, 0, 0, 0),
                      Vector4(0, 0, 0, 0),
                      Vector4(0, 0, 0, 0),
                      Vector4(0, 0, 0, 0) );
}

void Matrix44::identity() {
    *this = Matrix44 ( Vector4(1, 0, 0, 0),
                       Vector4(0, 1, 0, 0),
                       Vector4(0, 0, 1, 0),
                       Vector4(0, 0, 0, 1) );
}

Vector3 operator*(const Vector3& a, const Matrix44& b) {
    float s = b.matrix[3].x * a.x + b.matrix[3].y * a.y + b.matrix[3].z * a.z + b.matrix[3].w;
    if(s == 0.0f) {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
    if(s == 1.0f) {
        return Vector3(
            b.matrix[0].x * a.x + b.matrix[0].y * a.y + b.matrix[0].z * a.z + b.matrix[0].w,
            b.matrix[1].x * a.x + b.matrix[1].y * a.y + b.matrix[1].z * a.z + b.matrix[1].w,
            b.matrix[2].x * a.x + b.matrix[2].y * a.y + b.matrix[2].z * a.z + b.matrix[2].w);
    } else {
        float invS = 1.0f / s;
        return Vector3(
            (b.matrix[0].x * a.x + b.matrix[0].y * a.y + b.matrix[0].z * a.z + b.matrix[0].w) * invS,
            (b.matrix[1].x * a.x + b.matrix[1].y * a.y + b.matrix[1].z * a.z + b.matrix[1].w) * invS,
            (b.matrix[2].x * a.x + b.matrix[2].y * a.y + b.matrix[2].z * a.z + b.matrix[2].w) * invS);
    }
}

Matrix44 translate(Matrix44 t, float x, float y, float z) {
	Matrix44 translation { 1, 0, 0, 0,
				           0, 1, 0, 0,
				           0, 0, 1, 0,
				           x, y, z, 1 };
	return translation;
}

Matrix44 rotateX(float x) {
	// rotate about object origin (not world space origin)
	
	Matrix44 rotation{ 1, 0,       0,        0,
					   0, cos(-x), -sin(-x), 0,
					   0, sin(-x), cos(-x),  0,
					   0, 0,       0,        1 };
	return rotation;
}

Matrix44 rotateY(float y) {
	Matrix44 rotation{ cos(-y),  0, sin(-y), 0,
					   0,        1, 0,       0,
					   -sin(-y), 0, cos(-y), 0,
					   0,        0, 0,       1 };
	return rotation;
}

Matrix44 rotateZ(float z) {
	Matrix44 rotation{ cos(-z), -sin(-z), 0, 0,
					   sin(-z), cos(-z),  0, 0,
					   0,       0,        1, 0,
					   0,       0,        0, 1 };
	return rotation;
}

Matrix44 rotateAboutAxis(Vector3 u, float r) {
    u.normalize();
    Matrix44 rotation{ cos(r)+u.x*u.x*(1.0f - cos(r)),    u.x*u.y*(1.0f-cos(r))-u.z*sin(r),  u.x*u.z*(1.0f-cos(r))+u.y*sin(r),  0.0f,
                        u.y*u.x*(1.0f-cos(r))+u.z*sin(r), cos(r) + u.y*u.y*(1.0f - cos(r)),  u.y*u.z*(1.0f-cos(r))-u.x*sin(r),  0.0f,
                        u.z*u.x*(1-cos(r))-u.y*sin(r),    u.z*u.y*(1-cos(r)) + u.x*sin(r),   cos(r) + u.z*u.z*(1-cos(r)),       0.0f,
                        0.0f,                             0.0f,                              0.0f,                              1.0f };
    return rotation;
}

Matrix44 scale(float x, float y, float z) {
	Matrix44 scale{ x, 0, 0, 0,
		            0, y, 0, 0,
		            0, 0, z, 0,
		            0, 0, 0, 1 };
	return scale;
}