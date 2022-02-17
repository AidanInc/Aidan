#include "BinaryReader.h"

BinaryReader::BinaryReader(string path)
{
	counter = 0;
	fileStream.open(path, ios::binary | ios::in);
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
	if (!fileStream.eof()) {

		int value = 0;
		fileStream.read((char*)&value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		std::cout << "Counter: " << counter << std::endl;
		return value;
	}
	return NULL;
}

double BinaryReader::readDouble()
{
	fileStream.tellg();
	if (!fileStream.eof()) {
		double value = NULL;
		fileStream.read((char*)&value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		return value;
	}
	return NULL;
}

unsigned char BinaryReader::readByte()
{
	fileStream.tellg();
	if (!fileStream.eof()) {
		unsigned char value = NULL;
		fileStream.read((char*)value, sizeof(value));
		counter++;
		fileStream.seekg(counter * sizeof(value));
		return value;
	}
	return NULL;
}

char* BinaryReader::readBytes(const int count)
{
	if (!fileStream.eof()) {
	    char* values = new char[count](); //dynamically allocate a new array must be deleted after. 
		for (int i = 0; i < count; i++) {
			fileStream.tellg();
			fileStream.read((char*)values[i], sizeof(values[i]));
			counter++;
			fileStream.seekg(counter * sizeof(values[i]));
		}
		return values;
		delete& values;
	}
	return NULL;
}

bool BinaryReader::endOfFile() {
	return fileStream.eof();
}