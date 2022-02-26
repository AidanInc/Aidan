#pragma once
#include "Reader.h"
#include <fstream>
#include <iostream>
#include <string>

namespace Aidan {
	unsigned char peekByte(std::ifstream& fs);
	int readInt(std::ifstream& fs);
	float readFloat(std::ifstream& fs);
	unsigned char readByte(std::ifstream& fs);
	std::string readString(std::ifstream& fs);
	Color readColor(std::ifstream& fs);
	Vector2 readVector2(std::ifstream& fs);
	Vector3 readVector3(std::ifstream& fs);
	SubMesh readSubMesh(std::ifstream& fs);
	Triangle readTriangle(std::ifstream& fs);

};