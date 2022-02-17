#include "Reader.h"

Reader::Reader(string path) {
	try {
		r = new BinaryReader(path);
	}
	catch (...) {
		cout << "Error initializing Binary reader" << endl;
	}

}

bool Reader::NextElementIsMaterial() {
	int next = r->peekNext();
	return (next == MATERIAL);
}

bool Reader::NextElementIsLight() {
	int next = r->peekNext();
	return (next == LIGHT);
}

bool Reader::NextElementIsMesh() {
	int next = r->peekNext();
	return (next == MESH);
}

MeshData* Reader::NextMesh() {
	try {
		MeshData* meshData = new MeshData();
		if (r->readByte() != MESH) throw;
		int nameSize = r->readInt();

		std::string name(r->readBytes(nameSize));

		meshData->name = name;
		int numVerts = r->readInt();
		for (int i = 0; i < numVerts; i++) {
			meshData->verts.push_back(new Vector3((float)r->readDouble(), (float)r->readDouble(), (float)r->readDouble()));
			meshData->uuverts.push_back(new Vector2((float)r->readDouble(), (float)r->readDouble()));
		}
		return meshData;
	}
	catch (...) {}
	return NULL;
}

bool Reader::endOfFile() {
	return r->endOfFile();
}
//MaterialData* Reader::NextMaterial() {
//	const char NAME = 50;
//	const char ISTRANSPARENT = 51;
//	const char MAINCOLOR = 52;
//	const char MAINTEXTURE = 53;
//	//const char BUMPMAP = 54;
//	//const char NORMALMAP = 55;
//	const char REFLECTIVITY = 56;
//}