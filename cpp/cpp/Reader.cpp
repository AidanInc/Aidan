#include "Reader.h"

Reader::Reader(string path) {
	try {
		r = new BinaryReader(path);
	}
	catch (...) {
		cout << "Error initializing Binary reader" << endl;
	}

}

Reader::NextElementIsMaterial() {
	int next = r.peekNext();
	return (next == MATERIAL);
}

Reader::NextElementIsLight() {
	int next = r.peekNext();
	return (next == LIGHT);
}

Reader::NextElementIsMesh() {
	int next = r.peekNext();
	return (next == MESH);
}

Reader::NextMesh() {
	try {
		MeshData meshData = new MeshData();
		if (r.readByte() != MESH) throw;
		int nameSize = r.readInt();

		meshData.name = str(r.readBytes(nameSize));
		int numVerts = r.readInt();
		for (int i = 0; I < numVerts; i++) {
			meshData.verts.push_back(new Vector3((float)r.readDouble(), (float)r.readDouble(), (float)r.readDouble()));
			meshData.uuverts.push_back(new Vector2((float)r.readDouble(), (float)r.readDouble()));
		}
	}
}

Reader::NextLight() {

}

Reader::NextMaterial() {
	const char NAME = 50;
	const char ISTRANSPARENT = 51;
	const char MAINCOLOR = 52;
	const char MAINTEXTURE = 53;
	//const char BUMPMAP = 54;
	//const char NORMALMAP = 55;
	const char REFLECTIVITY = 56;
}