#include "ReaderData.h"


Vector2::Vector2(float X, float Y) {
    x = X;
    y = Y;
}

Vector3::Vector3(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
}

SubMeshData::SubMeshData() {
    tris = new list<int>();
    materialName = "";
}

MeshData::MeshData() {
    verts = new list<Vector3>();
    uuverts = new list<Vector2>();
    uuverts2 = new list<Vector2>();
    submeshes = new list<SubMeshData>();
    name = "";
}

ColorData::ColorData() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

LightData::LightData() {
    x = 0;
    y = 0;
    z = 0;
    intensity = 0;
    colorData = new ColorData();
}

MapData::MapData() {
    xTiling = 0;
    yTiling = 0;
    rotation = 0;
    data = new list<byte>();
    extension = "";
}

MaterialData::MaterialData() {
    name = "";
    isTransparent = false;
    reflectivity = 0.0;
    mainColor = NULL;
    textureMap = NULL;
    bumpMap = NULL;
    normalMap = NULL;
}

CameraData::CameraData() {
    name = "";
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
}