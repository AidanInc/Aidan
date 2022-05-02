#include "FileIO.h"
// source shared between AliReview and Renerer - patch changes
#include <assert.h>
#include <memory>

using std::string;
using std::ofstream;
using std::ifstream;

unsigned char Ali::peekByte(ifstream& f) {
    // unsigned char acts like byte from 0-255
    unsigned char b = 0;
    int nextInt = f.peek();
    b = static_cast<unsigned char>(nextInt);
    return b;
}

unsigned char Ali::readByte(ifstream& f) {
    // unsigned char acts like byte from 0-255
    unsigned char b = 0;
    f.read(reinterpret_cast<char*>(&b), 1); // one byte
    return b;
}

int Ali::readInt(ifstream& f) {
    int i = 0;
    // very non-portable and implementation dependent
    // expect 4 byte, little endian, twos compliment, signed integer
    assert(sizeof(i) == 4);
    f.read(reinterpret_cast<char*>(&i), 4);
    return i;
}

float Ali::readFloat(ifstream& f) {
    float fl = 0;
    // very non-portable and implementation dependant
    // expect 4 byte floating point number
    assert(sizeof(fl) == 4);
    f.read(reinterpret_cast<char*>(&fl), 4);
    return fl;
}

string Ali::readString(ifstream& f) {
    int len = readInt(f);
    std::unique_ptr<char[]> buf{ new char[len] };
    f.read(buf.get(), len);
    string str(buf.get(), len);
    return str;
}

Color Ali::readColor(ifstream& f) {
    Color color;
    color.r = readByte(f);
    color.g = readByte(f);
    color.b = readByte(f);
    return color;
}

Vector2 Ali::readVector2(ifstream& f) {
    Vector2 vec; // to return
    vec.u = readFloat(f);
    vec.v = readFloat(f);
    return vec;
}

Vector3 Ali::readVector3(ifstream& f) {
    Vector3 vec; // to return
    vec.x = readFloat(f);
    vec.y = readFloat(f);
    vec.z = readFloat(f);
    return vec;
}

Triangle Ali::readTriangle(ifstream& f) {
    Triangle tri; // to return
    tri.a = readInt(f);
    tri.b = readInt(f);
    tri.c = readInt(f);
    return tri;
}

Submesh Ali::readSubmesh(ifstream& f) {
    Submesh submesh; // to return
    submesh.material = readString(f);
    // read vertices
    int vertCount = readInt(f);
    for(int i=0; i < vertCount; i++) {
        submesh.vertices.push_back(readVector3(f));
    }
    // read uvs - same number as vertices
    for(int i=0; i < vertCount; i++) {
        submesh.uvs.push_back(readVector2(f));
    }
    // read triangles
    int triCount = readInt(f);
    for(int i=0; i < triCount; i++) {
        submesh.tris.push_back(readTriangle(f));
    }
    return submesh;
}

void Ali::write(std::ofstream& f, bool b) {
    f.put((char)b);
}

void Ali::write(std::ofstream& f, unsigned char c) {
    f.put(c);
}

void Ali::write(std::ofstream& f, int i) {
    // convert input i to little-endian,  two's compliment
    if(i > 2147483647) throw std::runtime_error("integer is too long");
    int remainder = 0;
    int number = i;
    // stragety:  http://mathforum.org/library/drmath/view/55738.html
    char integer[4]; // four byte length
    for(int j=0; j < 4; j++) {
        remainder = number % 256;
        number = number/256; // round down
        integer[j] = remainder;
    }
    // signed number representation.
    f.write(integer, sizeof(integer)); // 4 bytes
}

void Ali::write(std::ofstream& f, float fl) {
    //WARNING windows specific
    assert(sizeof(fl) == 4);
    f.write(reinterpret_cast<const char*>(&fl), 4); // 4 bytes
}

void Ali::write(std::ofstream& f, std::string s) {
    int length = s.length();
    write(f, length);
    const char* str = s.c_str();
    for(int i=0; i < length; i++) {
        write(f, (unsigned char)*str++);
    }
}

void Ali::write(std::ofstream& f, Color c) {
    write(f, c.r);
    write(f, c.g);
    write(f, c.b);
}

void Ali::write(std::ofstream& f, Vector2 vec) {
    write(f, vec.u);
    write(f, vec.v);
}

void Ali::write(std::ofstream& f, Vector3 vec) {
    write(f, vec.x);
    write(f, vec.y);
    write(f, vec.z);
}

void Ali::write(std::ofstream& f, Triangle t) {
    write(f, t.a);
    write(f, t.b);
    write(f, t.c);
}

void Ali::write(std::ofstream& f, Submesh s) {
    write(f, s.material);
    int vertCount = s.vertices.size();
    write(f, vertCount);
    for(int i=0; i < vertCount; i++) {
        write(f, s.vertices[i]);
    }
    int uvCount = vertCount;
    for(int i=0; i < uvCount; i++) {
        write(f, s.uvs[i]);
    }
    int triCount = s.tris.size();
    for(int i=0; i < triCount; i++) {
        write(f, s.tris[i]);
    }
}

void Ali::write(std::ofstream& f, Transform t) {
    for(int row = 0; row < 4; row++) {
        // 4th column is truncated (assumed to be 0,0,0,1)
        for(int column = 0; column < 3; column++) {
            write(f, t[row][column]);
        }
    }
}