#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "MaterialData.h"
#include "MeshData.h"
#include "LightData.h"

namespace Ali {
	
	static const unsigned char MATERIAL = 1;
	static const unsigned char LIGHT = 2;
	static const unsigned char MESH=  4;

	class Writer {
	public:
		Writer();
		void CloseFile();
		void OpenFile(std::string path);
		void DeleteFile();
		// you are expected to write materials first, then lights, then meshes.
		void WriteMaterial(MaterialData material);
		void WriteLight(LightData light);
		void WriteMesh(MeshData mesh);
	private:
		std::string filePath;
		std::fstream file;
		void AddToFile(std::vector<unsigned char>* data);
		bool haveWrittenAllMaterials;
		bool haveWrittenAllLights;
		// helper methods
		void AppendInt(const int i, std::vector<unsigned char>* data);
	    void AppendDouble(const double d, std::vector<unsigned char>* data);
		void AppendBool(const bool b, std::vector<unsigned char>* data);
	};
}