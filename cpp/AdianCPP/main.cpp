// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Reader.h"
int main()
{
    Aidan::Reader r = Aidan::Reader("model.ALI");


    while (!r.endOfFile()) {
        Aidan::AssetType type = r.peekNextAsset();

        if (type == Aidan::AssetType::MATERIAL) {
            Material m = r.readMaterial();
            std::cout << "Material Name: " << m.name << std::endl;
            std::cout << "Material Color R: " << m.color.r << std::endl;
            std::cout << "Material Color G: " << m.color.g << std::endl;
			std::cout << "Material Color B: " << m.color.b << std::endl;
			std::cout << "Material Color Alpha: " << m.color.a << std::endl;
			std::cout << "Material Transparency: " << m.transparency << std::endl;
            std::cout << "textureMap(char) size: " << m.textureMap.data.size() << std::endl;
            std::cout << "bumpMap(char) size: " << m.bumpMap.data.size() << std::endl;
            std::cout << "normalMap(char) size: " << m.normalMap.data.size() << std::endl;
            

            std::cout << std::endl;
        }

        if (type == Aidan::AssetType::MESH) {
            Mesh mesh = r.readMesh();
			std::cout << "Mesh Name: " << mesh.name << std::endl;
            // these are vectors lists

            std::cout << "verts (Vectors3) first item is: " 
                << "X:" << mesh.verts[0].x << " Y:" << mesh.verts[0].y << " Z:" << mesh.verts[0].z << std::endl;
            std::cout << "verts (Vectors3) size is: " << mesh.verts.size() << std::endl; 

            std::cout << "uverts(Vector2) first item is: "
                << "X:" << mesh.uverts[0].x << " Y:" << mesh.uverts[0].y << std::endl;
            std::cout << "uverts(Vector2) size is: " << mesh.uverts.size() << std::endl;

             
            for (SubMesh sm : mesh.submeshes) {
				std::cout << "Submesh Material Name: " << sm.materialName << std::endl;

                std::cout << "Submesh tris(int) first item: " << sm.tris[0] << std::endl;
                std::cout << "Submesh tris(int) size : " << sm.tris.size() << std::endl;

            }

			std::cout << std::endl;
        }

        if (type == Aidan::AssetType::LIGHT) {
            Light l = r.readLight();
			std::cout << "Light Intensity: " << l.intensity << std::endl;
			std::cout << "Light Color R: " << l.color.r << std::endl;
			std::cout << "Light Color G: " << l.color.g << std::endl;
			std::cout << "Light Color B: " << l.color.b << std::endl;			
            std::cout << "Light X: " << l.pos.x << std::endl;
			std::cout << "Light Y: " << l.pos.y << std::endl;
			std::cout << "Light Z: " << l.pos.z << std::endl;

			std::cout << std::endl;
        }
    }
    system("PAUSE");
}
