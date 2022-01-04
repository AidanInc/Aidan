#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "DataTypes.h"
// shared between Renderer and AliReview - patch changes

namespace Ali {
    enum class AssetType {NONE, INFO, LIGHT, CAMERA, MATERIAL, MESH, MESHINST};

    // forward declarations
    struct Info;
    struct Light;
    struct Camera;
    struct Material;
    struct Mesh;
    struct MeshInst;

    class Reader {
    public:
        // asset types
        Reader(std::string path);
        bool      endOfFile(); // return true when at end of file
        AssetType peekNextAsset();
        Info      readInfo();
        Light     readLight();
        Camera    readCamera();
        Material  readMaterial();
        Mesh      readMesh();
        MeshInst  readMeshInst();
    private:
        std::ifstream f; // file
    };

    struct Info {
        Info() : latitude(0), longitude(0),
                 solarAltitude(0), solarAzimuth(0) {};
        std::string clientName;
        std::string projectName;
        std::string projectAddress;
        std::string projectStatus;
        float       latitude;
        float       longitude;
        float       solarAltitude; // radians
        float       solarAzimuth; // radians
    };

    struct Light {
        Light() : intensity(0) {};
        Vector3 position;
        Color   color;
        float   intensity;
    };

    struct Camera {
        std::string   name;
        Vector3       position;
        Vector3       forward;
        Vector3       up;
    };

    struct Material {
        Material() : transparency(0) {};
        std::string   name;
        unsigned char transparency;
        Color         color;
        //std::vector<Texture> textures
    };

    struct Mesh {
        std::string          name;
        std::vector<Submesh> submeshes;
    };

    struct MeshInst {
        std::string meshName;
        Transform   transform;
    };
}