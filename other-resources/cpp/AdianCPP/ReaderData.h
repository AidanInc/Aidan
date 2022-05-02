#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Triangle {
	int a, b, c;
	Triangle();
	Triangle(int A, int B, int C);
};

struct Vector2 {
	float x, y;
	Vector2();
	Vector2(float X, float Y);
};

struct Vector3 {
	float x, y, z;
	Vector3();
	Vector3(float X, float Y, float Z);
};

struct SubMesh {	
	std::vector<int> tris;
	std::string materialName;
};

struct Mesh {
	std::string name;
	std::vector<Vector3> verts;
	std::vector<Vector2> uverts;
	std::vector<SubMesh> submeshes;
};


/**
 * @TODO unsure about this as it talks about Transform and don't understand this part
 */
struct MeshInst {
	std::string name;
	//Transform transform;
};

struct Color {
	double r;
	double g;
	double b;
	double a;
	Color();
};

struct Light {
	Vector3 pos;
	float intensity;
	Color color;
	Light();
};

struct MapData {
	double xTiling;
	double yTiling;
	std::string extension;
	std::vector<char> data;
	MapData();
};

struct Material {
	std::string name;
	bool transparency;
	double reflectivity;
	Color color;
	MapData textureMap;
	MapData bumpMap;
	MapData normalMap;
	Material();
};

struct Camera {
	std::string name;
	Vector3 pos;
	Vector3 rotation;
};