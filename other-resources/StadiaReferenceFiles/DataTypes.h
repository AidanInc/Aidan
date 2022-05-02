#pragma once
// source shared between AliReview and Renderer - patch changes
#include <vector>
#include <string>

// data structures
// 2 dimensional vector
struct Vector2 {
    float u, v;
    Vector2();
};

// point or vector (depending on context)
// can represent simple direction if normalized
// 3x1 row-major vector
struct Vector3 {
    float x, y, z;
    Vector3();
    explicit Vector3(float X, float y, float z);
    float    operator[](int index) const;
    float&    operator[](int index);
    Vector3  operator-() const;                  // unary negation
    Vector3& operator+=(const Vector3&);         // assignment addition
    Vector3& operator-=(const Vector3&);         // assignment subtraction
    Vector3& operator*=(const float);            // assignment scalar multiplication
    Vector3  cross(const Vector3&) const;        // cross product
    float    length() const;
    float    lengthSquared() const;
    Vector3& normalize();
};
typedef Vector3 Point; // conceptually distinct, but same implementation
// non-member operators
Vector3 operator+(Vector3, const Vector3&);        // addition
Vector3 operator-(Vector3, const Vector3&);        // subtraction
float   operator*(const Vector3&, const Vector3&); // dot product
Vector3 operator*(float, Vector3);                 // scalar multiplication

struct Vector4 {
    float x, y, z, w;
    Vector4();
    explicit Vector4(float x, float y, float z, float w);
    float    operator[](int index) const;
    float&   operator[](int index);
    Vector4  operator-() const;                     // unary negation
    Vector4& operator+=(const Vector4&);            // assignment addition
    Vector4& operator-=(const Vector4&);            // assignment subtraction
    Vector4& operator*=(float);                     // assignment scalar multiplication
    float    length() const;
    float    lengthSquared() const;
    void     normalize();
};
// non-member operators
Vector4 operator+(Vector4, const Vector4&);         // addition
Vector4 operator-(Vector4, const Vector4&);         // subtraction
float   operator*(const Vector4&, const Vector4&);  // dot product
Vector4 operator*(float, Vector4);                  // scalar multiplication

struct Triangle {
    int a, b, c; // clockwise winding order
    Triangle();
	Triangle(int a, int b, int c);
};

struct Color {
    unsigned char r, g, b; // 0-255
    Color();
};

// 4x4 matrix
struct Matrix44 {
public:
    Matrix44();
    explicit Matrix44(const Vector4&, const Vector4&, const Vector4&, const Vector4&);
    explicit Matrix44(float m00, float m01, float m02, float m03,
                      float m10, float m11, float m12, float m13,
                      float m20, float m21, float m22, float m23,
                      float m30, float m31, float m32, float m33 );
    Vector4   operator[](int index) const;
    Vector4&  operator[](int index);
    Matrix44& operator+=(const Matrix44&);
    Matrix44& operator-=(const Matrix44&);
    Matrix44& operator*=(const Matrix44&);
    Matrix44  operator*(const Matrix44&) const;
    // convention is pre-multiplication: point = point * transform
    friend Vector3 operator*(const Vector3&, const Matrix44&);
    void      transpose();
    void      zero();
    void      identity();
private:
    // row-major
    Vector4 matrix[4];
};
typedef Matrix44 Transform; // synonymous

Matrix44 translate(Matrix44 t, float x, float y, float z);
Matrix44 rotateX(float radians);
Matrix44 rotateY(float radians);
Matrix44 rotateZ(float radians);
Matrix44 rotateAboutAxis(Vector3 axis, float radians);
Matrix44 scale(float x, float y, float z);

struct Submesh {
    std::string           material;
    std::vector<Vector3>  vertices;
    std::vector<Vector2>  uvs;
    std::vector<Triangle> tris;
};