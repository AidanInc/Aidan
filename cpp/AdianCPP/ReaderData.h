#pragma once


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vector2 {
public:
	float x, y;

	Vector2(float X, float Y);
};

class Vector3 {
public:
	float x, y, z;

	Vector3(float X, float Y, float Z);
};

class SubMeshData {
public:
	vector<int>* tris;
	string materialName;

	SubMeshData();
};

class MeshData {
public:
	string name;
	vector<Vector3*> verts;
	vector<Vector2*> uuverts;
	vector<Vector2*> uuverts2;
	vector<SubMeshData*> submeshes;

	MeshData();
};

class ColorData {
public:
	double r;
	double g;
	double b;
	double a;

	ColorData();
};

class LightData {
public:
	double x;
	double y;
	double z;
	double intensity;
	ColorData* colorData;

	LightData();
};

class MapData {
public:
	double xTiling;
	double yTiling;
	double rotation;
	vector<char>* data;
	string extension;

	MapData();
};

class MaterialData {
public:
	string name;
	bool isTransparent;
	double reflectivity;
	ColorData* mainColor;
	MapData* textureMap;
	MapData* bumpMap;
	MapData* normalMap;

	MaterialData();
};

class CameraData {
public:
	string name;
	double xLocation, yLocation, zLocation;
	double xRotation, yRotation, zRotation;

	CameraData();
};