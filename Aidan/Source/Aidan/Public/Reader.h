#pragma once
#include "ReaderData.h"
#include <fstream>

namespace Aidan {

    enum class AssetType {
        NONE,
        LIGHT,
        CAMERA,
        MATERIAL,
        MESH
    };

    class Reader {
    public:
        AssetType peekNextAsset();
        bool endOfFile();
        Light readLight();
        Camera readCamera();
        Material readMaterial();
        Mesh readMesh();
        Reader(std::string path);


    private:
        std::ifstream fs; //file
    };
}