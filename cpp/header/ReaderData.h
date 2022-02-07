#ifndef READERDATA_H
#define READERDATA_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Vector2 {
    public:
        float x, y;

        Vector2(float X, float Y);
}

class Vector3 {
    public:
        float x, y, z;

        Vector3(float X, float Y, float Z);
}

 class SubMeshData {
     public:
        list<int> tris;
        string materialName;

        SubMeshData();
 }

 class MeshData {
    public:
        string name;
        list<Vector3> verts;
        list<Vector2> uuverts;
        list<Vector2> uuverts2;
        list<SubMeshData> submeshes;

        MeshData();
 }

  class ColorData {
     public:
        double r;
        double g;
        double b;
        double a;

        ColorData();
 }

 class LightData {
     public:
        double x;
        double y;
        double z;
        double intensity;
        ColorData colorData;

        LightData();
 }

 class MapData {
     public:
        double xTiling;
        double yTiling;
        double rotation;
        list<byte> data;
        string extension;

        MapData();
 }

 class MaterialData {
    public:
        string name;
        bool isTransparent;
        double reflectivity;
        ColorData mainColor;
        MapData textureMap;
        MapData bumpMap;
        MapData normalMap;

        MaterialData();
 }

 class CameraData {
     public:
        string name;
        double xLocation, yLocation, zLocation;
        double xRotation, yRotation, zRotation;

        CameraData();
 }