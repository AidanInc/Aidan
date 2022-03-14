#pragma once
#include "Reader.h"
#include <fstream>
#include <iostream>
#include <string>

namespace Aidan {
	unsigned char peekByte(std::ifstream& fs);
	int readInt(std::ifstream& fs);
	double readDouble(std::ifstream& fs);
	unsigned char readByte(std::ifstream& fs);
	std::string readString(std::ifstream& fs);
	Color readColor(std::ifstream& fs);
	Color readColorLight(std::ifstream& fs);
	Vector2 readVector2(std::ifstream& fs);
	Vector3 readVector3(std::ifstream& fs);
	Triangle readTriangle(std::ifstream& fs);
	MapData readMapData(std::ifstream& fs);
};