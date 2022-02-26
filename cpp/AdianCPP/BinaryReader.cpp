#include "BinaryReader.h"
#include <assert.h>
#include <memory>

unsigned char Aidan::peekByte(std::ifstream& fs)
{
	unsigned char c = 0;
	int nextInt = fs.peek();
	c = static_cast<unsigned char>(nextInt);
	return c;
}

int Aidan::readInt(std::ifstream& fs)
{
	int x = 0;
	assert(sizeof(x) == 4); // abort if size of int isn't 4 bytes
	fs.read(reinterpret_cast<char*>(&x), 4);
	return x;
}

float Aidan::readFloat(std::ifstream& fs)
{
	float x = 0.0f;
	assert(sizeof(x) == 4);
	fs.read(reinterpret_cast<char*>(&x), 4);
	return x;
}

unsigned char Aidan::readByte(std::ifstream& fs)
{
	unsigned char x = 0;
	assert(sizeof(x) == 1);
	fs.read(reinterpret_cast<char*>(&x), 1);
	return x;
}

std::string Aidan::readString(std::ifstream& fs) {
	int len = readInt(fs);
	std::unique_ptr<char[]> buffer{ new char[len] }; //create a char[] that will be the buffer of what we read
	fs.read(buffer.get(), len);
	std::string x(buffer.get(), len);
	return x;
}

Color Aidan::readColor(std::ifstream& fs) {
	Color c;
	c.r = readByte(fs);
	c.g = readByte(fs);
	c.b = readByte(fs);
	return c;
}

Vector2 Aidan::readVector2(std::ifstream& fs) {
	Vector2 v;
	v.x = readFloat(fs);
	v.y = readFloat(fs);
	return v;
}

Vector3 Aidan::readVector3(std::ifstream& fs) {
	Vector3 v;
	v.x = readFloat(fs);
	v.y = readFloat(fs);
	v.z = readFloat(fs);
	return v;
}

Triangle Aidan::readTriangle(std::ifstream& fs) {
	Triangle t;
	t.a = readInt(fs);
	t.b = readInt(fs);
	t.c = readInt(fs);
	return t;
}

SubMesh Aidan::readSubMesh(std::ifstream& fs) {
	SubMesh sm;
	sm.materialName = readString(fs);

	int vertCount = readInt(fs);
	for (int i = 0; i < vertCount; i++) {
		sm.verts.push_back(readVector3(fs));
	}

	//uverts will be the same number as verts
	for (int i = 0; i < vertCount; i++) {
		sm.uverts.push_back(readVector2(fs));
	}

	int triCount = readInt(fs);
	for (int i = 0; i < triCount; i++) {
		sm.tris.push_back(readTriangle(fs));
	}
	return sm;
}

