#ifndef BINARYREADER_H
#define BINARYREADER_H
#endif // !BINARYREADER_H

#include <fstream>
#include <iostream>

using namespace std;
class BinaryReader {
public:
	int peekNext();
	int readInt();
	double readDouble();
	unsigned char readByte();
	unsigned char[] readBytes(int count);

	BinaryReader(string path);
	~BinaryReader();

private:
	ifstream fileStream;
	int counter;
};