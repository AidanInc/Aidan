#include "Ali.h"
#include "FileIO.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <assert.h>

using std::string;
using std::ifstream;
using std::ios;
using std::exception;

using namespace Ali;

const static unsigned char ASSET_TYPE_INFO      = 1;
const static unsigned char ASSET_TYPE_LIGHT     = 2;
const static unsigned char ASSET_TYPE_CAMERA    = 3;
const static unsigned char ASSET_TYPE_MATERIAL  = 4;
const static unsigned char ASSET_TYPE_MESH      = 5;
const static unsigned char ASSET_TYPE_MESHINST  = 6;

static char TEX_TYPE_BUMPMAP     = 20;
static char ASSET_TYPE_NORMALMAP = 21;

Reader::Reader(string path) {
    // open file as binary, position at beginning of file
    // ifstream is RAII. will close when Reader is destroyed
    f.open(path, ios::in | ios::binary | ios::beg);
    // invariant: Reader class has a valid file open and ready to read
    if(!f.is_open()) throw exception("file doesn't exist");
    // check file version
    int fileVersion = readInt(f);
    if(fileVersion != 7) throw exception("unknown .ali file version");
}

bool Reader::endOfFile() {
    return (f.eof() || f.peek() == EOF);
}

AssetType Reader::peekNextAsset() {
    if(endOfFile()) return AssetType::NONE;
    unsigned char assetType = peekByte(f);
    switch(assetType) {
    case ASSET_TYPE_INFO:
        return AssetType::INFO;
    case ASSET_TYPE_LIGHT:
        return AssetType::LIGHT;
    case ASSET_TYPE_CAMERA:
        return AssetType::CAMERA;
    case ASSET_TYPE_MATERIAL:
        return AssetType::MATERIAL;
    case ASSET_TYPE_MESH:
        return AssetType::MESH;
    case ASSET_TYPE_MESHINST:
        return AssetType::MESHINST;
    default:
        throw std::runtime_error("unknown asset type");
    }
}

Info Reader::readInfo() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_INFO) throw std::runtime_error("unexpected asset in .ali file");

    Info info;
    info.clientName =     readString(f);
    info.projectName =    readString(f);
    info.projectAddress = readString(f);
    info.projectStatus =  readString(f);
    info.latitude =       readFloat(f);
    info.longitude =      readFloat(f);
    info.solarAltitude =  readFloat(f);
    info.solarAzimuth =   readFloat(f);
    return info;
}

Light Reader::readLight() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_LIGHT) throw std::runtime_error("unexpected asset in .ali file");

    assert(0); //FUTURE implement
    return Light();
}

Camera Reader::readCamera() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_CAMERA) throw std::runtime_error("unexpected asset in .ali file");

    Camera camera;
    camera.name =     readString(f);
    camera.position = readVector3(f);
    camera.forward =  readVector3(f);
    camera.up =       readVector3(f);   
    return camera;
}
Material Reader::readMaterial() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_MATERIAL) throw std::runtime_error("unexpected asset in .ali file");

    Material mat;
    mat.name =         readString(f);
    mat.transparency = readByte(f);
    mat.color =        readColor(f);
    int texCount =     readInt(f);
    for(int i=0; i < texCount; i++) {
        assert(0); //FUTURE read textures
    }
    return mat;
}

Mesh Reader::readMesh() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_MESH) throw std::runtime_error("unexpected asset in .ali file");

    Mesh mesh;
    mesh.name =        readString(f);
    int submeshCount = readInt(f);
    for(int i = 0; i < submeshCount; i++) {
        mesh.submeshes.push_back(readSubmesh(f));;
    }
    return mesh;
}

MeshInst Reader::readMeshInst() {
    unsigned char nextAsset = readByte(f);
    if(nextAsset != ASSET_TYPE_MESHINST) throw std::runtime_error("unexpected asset in .ali file");

    MeshInst meshInst;
    meshInst.meshName = readString(f);
    Transform t;
    for(int row = 0; row < 4; row++) {
        for(int column = 0; column < 3; column++) {
            t[row][column] = readFloat(f);
        }
    }
    meshInst.transform = t;
    return meshInst;
}

//Dear Robert I am mezermized by the little dot that appears whenever I type a space
//right now I am waiting for you to get out of a curriculum committee meeting and 
//I am quite tired. Today was a very tiring day and I would do anything to just go 
// to sleep right here on your desk. Lori Brown is probably talking on and on. Yesterday
//in the reading room Barbara Opar called Jean-Francois "her boy." I almost died.