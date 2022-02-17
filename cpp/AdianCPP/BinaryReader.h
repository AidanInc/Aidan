#pragma once


#include <fstream>
#include <iostream>

using namespace std;
class BinaryReader {
public:
	int peekNext();
	int readInt();
	double readDouble();
	unsigned char readByte();
	char* readBytes(const int count);
	bool endOfFile();

	BinaryReader(string path);
	~BinaryReader();

private:
	ifstream fileStream;
	int counter;
};