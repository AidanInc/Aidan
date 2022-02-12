#ifndef READER_H
#define READER_H
#include "ReaderData.h"
#include "BinaryReader.h"

using namespace std;
class Reader {
public:
    bool NextElementIsMaterial();
    bool NextElementIsLight();
    bool NextElementIsMesh();
    MeshData NextMesh();
    LightData NextLight();
    MaterialData NextMaterial();

    Reader(string path);


private:
    /**
     * @todo These values may not work and will need to be changed as we test
     *
     */
    const char MATERIAL = (char)1;
    const char LIGHT = (char)2;
    const char MESH = (char)4;

    BinaryReader r;
};

