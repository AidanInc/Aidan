#pragma once
// source shared between AliReview and Renerer - patch changes
#include <iostream>
#include <fstream>
#include <string>
#include "DataTypes.h"
namespace Ali {
// utility function declarations
    unsigned char peekByte(std::ifstream&);
    unsigned char readByte(std::ifstream&);
    int           readInt(std::ifstream&);
    float         readFloat(std::ifstream&);
    std::string   readString(std::ifstream&);
    Color         readColor(std::ifstream&);
    Vector2       readVector2(std::ifstream&);
    Vector3       readVector3(std::ifstream&);
    Triangle      readTriangle(std::ifstream&);
    Submesh       readSubmesh(std::ifstream&);

    void write(std::ofstream&, bool);
    void write(std::ofstream&, unsigned char);
    void write(std::ofstream&, int);
    void write(std::ofstream&, float);
    void write(std::ofstream&, std::string);
    void write(std::ofstream&, Color);
    void write(std::ofstream&, Vector2);
    void write(std::ofstream&, Vector3);
    void write(std::ofstream&, Triangle);
    void write(std::ofstream&, Submesh);
    void write(std::ofstream&, Transform);
}