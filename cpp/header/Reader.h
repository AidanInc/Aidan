#ifndef READER_H
#define READER_H
#include "ReaderData.h"


class Reader {
    public:
        bool NextElementIsMaterial();
        bool NextElementIsLight();
        bool NextElementIsMesh();
        MeshData NextMesh();
        LightData NextLight();
        MaterialData NextMaterial();

        Reader();

        
    private:
    /**
     * @todo These values may not work and will need to be changed as we test
     * 
     */
        const char MATERIAL = (char) 1;
        const char LIGHT = (char) 2;
        const char MESH = (char) 4;
}

