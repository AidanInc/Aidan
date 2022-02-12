#include "BinaryReader.h"

BinaryReader::BinaryReader(string path)
{
	counter = 0;
	fileStream.open(path, ios::binary);
	fileStream.seekg(0);
}

BinaryReader::~BinaryReader() {
	fileStream.close();
}

int BinaryReader::peekNext()
{
	return fileStream.peek();
}

int BinaryReader::readInt()
{
	fileStream.tellg();
	if (!fileStream.eof) {
		int value;
		fileStream.read((char*)value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		return value;
	}
}

double BinaryReader::readDouble()
{
	fileStream.tellg();
	if (!fileStream.eof) {
		double value;
		fileStream.read((char*)value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		return value;
	}
}

unsigned char BinaryReader::readByte()
{
	fileStream.tellg();
	if (!fileStream.eof) {
		unsigned char value;
		fileStream.read((char*)value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		return value;
	}
}

unsigned char[] BinaryReader::readBytes(int count)
{
	if (!fileStream.eof) {
		unsigned char values[count];
		for (int i = 0; i < count; i++) {
			fileStream.tellg();
			fileStream.read((char*)values[i], sizeof(values[i]));
			counter++;
			fileStream.seekg(counter * sizeof(values[i]));
		}
		return values;
	}
}
