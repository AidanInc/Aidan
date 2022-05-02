#include "Writer.h"

#include <assert.h>
#include <stdio.h>

using namespace Ali;
using namespace std;

Writer::Writer() : haveWrittenAllMaterials(false),
	               haveWrittenAllLights(false) { };

void Writer::OpenFile(std::string path) {
	filePath = path;
	file.open(path.c_str(), std::ios::out | std::ios::binary);
}

void Writer::AddToFile(std::vector<unsigned char>* data) {
	char* buffer = NULL;
	buffer = (char*) malloc(data->size());
	if(buffer == NULL) throw std::exception("unable to allocate memory");
	for(int i=0; i<data->size(); i++) {
		buffer[i] = data->at(i);
	}
	file.write(buffer, data->size());
	free (buffer);
}

void Writer::CloseFile() {
	file.close();
}

void Writer::DeleteFile() {
	CloseFile();
	remove(filePath.c_str());
}


void Writer::WriteMaterial(MaterialData mat) {
	// properties are identified by a unique byte and have an expected
	// number and type of data members as documented here
	const unsigned char NAME = 50;
	    // integer name size
	    // chars name value
	const unsigned char ISTRANSPARENT = 51;
	    // byte indicating boolean
	const unsigned char MAINCOLOR = 52;
	    // double red
	    // double green
	    // double blue
	    // double alpha
	const unsigned char MAINTEXTURE = 53;
	    // double x tiling
	    // double y tiling
	    // double rotation in degrees
	    // integer extension string size (bytes)
	    // chars extension string (bytes)
	    // integer data size
	    // bytes data
	const unsigned char BUMPMAP = 54;
	    // double x tiling
	    // double y tiling
		// double rotation in degrees
	    // integer extension string size (bytes)
	    // chars extension string (bytes)
	    // integer data size
	    // bytes data
	    // double bump amount
	const unsigned char NORMALMAP = 55;
	    // double x tiling
	    // double y tiling
	    // double rotation in degrees
	    // integer extension string size (bytes)
	    // chars extension string (bytes)
	    // integer data size
	    // bytes data
	const unsigned char REFLECTIVITY = 56;
	    // double reflectivity


	// ensure that writing materials is still allowed
	assert(haveWrittenAllMaterials == false);
	// temporary container for binary data to write
	vector<unsigned char> data;
	data.push_back(Ali::MATERIAL);
	// WE WILL INSERT THE NUMBER OF PROPERTIES HERE AS A DOUBLE
	int numPropertiesWritten = 0;

	// name property
	data.push_back(NAME);
	AppendInt((int)mat.name.ByteCount(), &data);
	for(int i=0; i < mat.name.length(); i++) {
		data.push_back(mat.name[i]);
	}
	numPropertiesWritten++;

	// isTransparent property
	data.push_back(ISTRANSPARENT);
	AppendBool(mat.isTransparent, &data);
	numPropertiesWritten++;

	// mainColor
	data.push_back(MAINCOLOR);
	AppendDouble(mat.mainColor.r, &data);
	AppendDouble(mat.mainColor.g, &data);
	AppendDouble(mat.mainColor.b, &data);
	AppendDouble(mat.mainColor.a, &data);
	numPropertiesWritten++;

	// mainTexture
	if(mat.usesMainTexture) {
		data.push_back(MAINTEXTURE);
		AppendDouble(mat.mainTexture.xTiling, &data);
		AppendDouble(mat.mainTexture.yTiling, &data);
		AppendDouble(mat.mainTexture.rotation, &data);
		AppendInt((int)mat.mainTexture.extension.ByteCount(), &data);
		for(int i=0; i < mat.mainTexture.extension.ByteCount(); i++) {
			data.push_back(mat.mainTexture.extension[i]);
		}
		AppendInt((int)mat.mainTexture.data.size(), &data);
		for(int i=0; i < mat.mainTexture.data.size(); i++) {
			data.push_back(mat.mainTexture.data.at(i));
		}
		numPropertiesWritten++;
	}

	// bumpmap
	if(mat.usesBumpMap) {
		data.push_back(BUMPMAP);
		AppendDouble(mat.bumpMap.xTiling, &data);
		AppendDouble(mat.bumpMap.yTiling, &data);
		AppendDouble(mat.bumpMap.rotation, &data);
		AppendDouble(mat.bumpAmount, &data);
		AppendInt((int)mat.bumpMap.extension.ByteCount(), &data);
		for(int i=0; i < mat.bumpMap.extension.ByteCount(); i++) {
			data.push_back(mat.bumpMap.extension[i]);
		}
		AppendInt((int)mat.bumpMap.data.size(), &data);
		for(int i=0; i < mat.bumpMap.data.size(); i++) {
			data.push_back(mat.bumpMap.data.at(i));
		}
		numPropertiesWritten++;
	}

	// normal map
	if(mat.usesNormalMap) {
		data.push_back(NORMALMAP);
		AppendDouble(mat.normalMap.xTiling, &data);
		AppendDouble(mat.normalMap.yTiling, &data);
		AppendDouble(mat.normalMap.rotation, &data);
		AppendInt((int)mat.normalMap.extension.ByteCount(), &data);
		for(int i=0; i < mat.normalMap.extension.ByteCount(); i++) {
			data.push_back(mat.normalMap.extension[i]);
		}
		AppendInt((int)mat.normalMap.data.size(), &data);
		for(int i=0; i < mat.normalMap.data.size(); i++) {
			data.push_back(mat.normalMap.data.at(i));
		}
		numPropertiesWritten++;
	}
	// isTransparent property
	data.push_back(REFLECTIVITY);
	AppendDouble(mat.reflectivity, &data);
	numPropertiesWritten++;

	// insert number of properties after first indicator byte
	vector<unsigned char> numPropertiesWrittenData;
	int remainder = 0;
	int number = numPropertiesWritten;
	int j = 0;
	for(int j=0; j < 4; j++) {
		remainder = number % 256; // remainder
		number = number / 256; // rounded down
		numPropertiesWrittenData.push_back(remainder);
	}
	data.insert(data.begin()+1, numPropertiesWrittenData.begin(), numPropertiesWrittenData.end()), 
	AddToFile(&data);
}

void Writer::WriteLight(LightData light) {
	assert(haveWrittenAllLights == false);
	// to enforce file order, dissallow writing any more materials
	haveWrittenAllMaterials = true;
	// an ordered set of double values
	vector<unsigned char> data;
	data.push_back(Ali::LIGHT);
	AppendDouble(light.xPos, &data);
	AppendDouble(light.yPos, &data);
	AppendDouble(light.zPos, &data);
	AppendDouble(light.rColor, &data);
	AppendDouble(light.gColor, &data);
	AppendDouble(light.bColor, &data);
	AppendDouble(light.intensity, &data);
	AddToFile(&data);
}

void Writer::WriteMesh(MeshData mesh) {
	vector<unsigned char> data;
	// to enforce file order, dissallow writing any more materials or lights
	haveWrittenAllMaterials = true;
	haveWrittenAllLights = true;
	// we will record data to a vector of bytes before writing
	// it all to disk at once.
	// write indicator byte
	data.push_back(Ali::MESH);
	// write mesh name size indicator
	AppendInt((int)mesh.name.ByteCount(), &data);
	// write name data
	for(int i=0; i < mesh.name.length(); i++) {
		data.push_back(mesh.name[i]);
	}
	// write number of vertices
	AppendInt( ((int)mesh.verts.size()/7) , &data);
	// write verts
	assert(mesh.verts.size() % 7 == 0); // groups of 7 (x y z u1 v1 u2 v2)
	for(int i=0; i < mesh.verts.size(); /*incremented in loop*/) {
		AppendDouble(mesh.verts[i], &data);
		i++;
	}
	// write number of submeshes
	AppendInt((int)mesh.submeshes.size(), &data);
	// write submeshes
	for(int submesh=0; submesh < mesh.submeshes.size(); submesh++) {
		// write submesh material name size
		AppendInt((int)mesh.submeshes[submesh].materialName.ByteCount(), &data);
		// write material name
		for(int i=0; i < mesh.submeshes[submesh].materialName.length(); i++) {
			data.push_back((mesh.submeshes[submesh].materialName[i]));
		}
		// write number of triangles
		AppendInt( ((int)mesh.submeshes[submesh].tris.size()/3) , &data);
		// write each tri
		assert(mesh.submeshes[submesh].tris.size() % 3 == 0); // groups of 3 (x y z)
		for(int tri=0; tri < mesh.submeshes[submesh].tris.size(); tri++) {
			AppendInt(mesh.submeshes[submesh].tris[tri], &data);
		}
	}
	AddToFile(&data);
}

void Writer::AppendInt(int i, vector<unsigned char>* data) {
	// convert input i to little-endian,  two's compliment
	// signed number representation.
	if(i > 2147483647) throw std::runtime_error("integer is too long");
	int remainder = 0;
	int number = i;
	// our strategy: http://mathforum.org/library/drmath/view/55738.html
	int j = 0;
	for(int j=0; j < 4; j++) {
		remainder = number % 256; // remainder
		number = number / 256; // rounded down
		data->push_back(remainder);
	}
}

void Writer::AppendDouble(double d, vector<unsigned char>* data) {
	// get memory representation of double
	char charArray[8];
	memcpy(charArray, &d, 8);
	for(int i=0; i<8; i++) {
	data->push_back(charArray[i]); 
	}
	// charArray deleted when it goes out of scope
}

void Writer::AppendBool(bool b, vector<unsigned char>* data) {
	data->push_back(b);
}