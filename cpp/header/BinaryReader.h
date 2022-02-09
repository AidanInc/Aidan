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
	byte readByte();
	byte[] readBytes(count);

	BinaryReader(ifstream fs);

private:
	ifstream fileStream;
};