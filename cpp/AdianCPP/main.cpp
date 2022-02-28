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

            std::cout << std::endl;
        }

        if (type == Aidan::AssetType::MESH) {
            Mesh mesh = r.readMesh();
			std::cout << "Mesh Name: " << mesh.name << std::endl;

             
            for (SubMesh sm : mesh.submeshes) {
				std::cout << "Submesh Material Name: " << sm.materialName << std::endl;

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
