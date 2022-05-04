#include "BinaryReader.h"
#include <assert.h>
#include <memory>

/** 
 * @param fs - File Stream 
 * @return unsigned char - returns the next byte of the file specified 
 */
unsigned char Aidan::peekByte(std::ifstream& fs)
{
	unsigned char c = 0;
	int nextInt = fs.peek();
	c = static_cast<unsigned char>(nextInt);
	return c;
}

/** 
 * @param fs - File Stream 
 * @return unsigned int - returns the next int (4 bytes) of the file specified 
 */
int Aidan::readInt(std::ifstream& fs)
{
	int x = 0;
	assert(sizeof(x) == 4); // abort if size of int isn't 4 bytes
	fs.read(reinterpret_cast<char*>(&x), 4);
	return x;
}

/** 
 * @param fs - File Stream 
 * @return unsigned double - returns the next double value (8 bytes) of the file specified 
 */
double Aidan::readDouble(std::ifstream& fs)
{
	double x = 0.0f;
	assert(sizeof(x) == 8);
	fs.read(reinterpret_cast<char*>(&x), 8);
	return x;
}

/** 
 * @param fs - File Stream 
 * @return unsigned char - returns the next byte (1 byte) of the file specified 
 */
unsigned char Aidan::readByte(std::ifstream& fs)
{
	unsigned char x = 0;
	assert(sizeof(x) == 1);
	fs.read(reinterpret_cast<char*>(&x), 1);
	return x;
}
/** 
 * @param fs - File Stream 
 * @return unsigned std::string - returns the next string set of the file specified 
 */
std::string Aidan::readString(std::ifstream& fs) {
	int len = readInt(fs);
	std::unique_ptr<char[]> buffer{ new char[len] }; //create a char[] that will be the buffer of what we read
	fs.read(buffer.get(), len);
	std::string x(buffer.get(), len);
	return x;
}

/**
 * @param fs - File Stream
 * @return Color - Makes a new Color Struct with the values read from the file specified
 */
Color Aidan::readColor(std::ifstream& fs) {
	Color c;
	c.r = readDouble(fs);
	c.g = readDouble(fs);
	c.b = readDouble(fs);
	c.a = readDouble(fs);
	return c;
}

/**
 * @param fs - File Stream
 * @return Color - Makes a new Color Struct without Alpha with the values read from the file specified
 */
Color Aidan::readColorLight(std::ifstream& fs) {
	Color c;
	c.r = readDouble(fs);
	c.g = readDouble(fs);
	c.b = readDouble(fs);
	return c;
}

/**
 * @param fs - File Stream
 * @return Vector2 - Makes a new Vector2 Struct with the values read from the file specified
 */
Vector2 Aidan::readVector2(std::ifstream& fs) {
	Vector2 v;
	v.x = readDouble(fs);
	v.y = readDouble(fs);
	return v;
}

/**
 * @param fs - File Stream
 * @return Vector3 - Makes a new Vector3 Struct with the values read from the file specified
 */
Vector3 Aidan::readVector3(std::ifstream& fs) {
	Vector3 v;
	v.x = readDouble(fs);
	v.y = readDouble(fs);
	v.z = readDouble(fs);
	return v;
}

/**
 * @param fs - File Stream
 * @return Triangle - Makes a new Triangle Struct with the values read from the file specified
 */
Triangle Aidan::readTriangle(std::ifstream& fs) {
	Triangle t;
	t.a = readInt(fs);
	t.b = readInt(fs);
	t.c = readInt(fs);
	return t;
}

/**
 * @param fs - File Stream
 * @return MapData - Makes a new MapData Struct with the values read from the file specified
 */
MapData Aidan::readMapData(std::ifstream& fs) {
	MapData md;
	md.xTiling = readDouble(fs);
	md.yTiling = readDouble(fs);
	md.extension = readString(fs);

	int mainTextureDataSize = readInt(fs);
	for (int i = 0; i < mainTextureDataSize; i++) {
		md.data.push_back(readByte(fs));
	}
	return md;
}

