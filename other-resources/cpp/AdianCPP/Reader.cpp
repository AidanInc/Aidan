#include "Reader.h"
#include "BinaryReader.h"
#include <assert.h>

using namespace Aidan;

const unsigned char ASSET_TYPE_LIGHT = 2;
const unsigned char ASSET_TYPE_CAMERA = -1;
const unsigned char ASSET_TYPE_MATERIAL = 1;
const unsigned char ASSET_TYPE_MESH = 4;

Reader::Reader(std::string path) {
	fs.open(path, std::ios::in | std::ios::binary | std::ios::beg);
	if (!fs.is_open()) throw std::exception("File can't be found");
}

AssetType Reader::peekNextAsset() {
	if (endOfFile()) return AssetType::NONE;
	unsigned char asset = peekByte(fs);
	switch (asset)
	{
	case ASSET_TYPE_CAMERA:
		return AssetType::CAMERA;
	case ASSET_TYPE_LIGHT:
		return AssetType::LIGHT;
	case ASSET_TYPE_MATERIAL:
		return AssetType::MATERIAL;
	case ASSET_TYPE_MESH:
		return AssetType::MESH;
	default:
		std::cout << "Asset type not found" << std::endl;
	};
}

Light Reader::readLight() {
	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_LIGHT) throw std::runtime_error("Expecting to read light info failed!");

	Light l;
	l.pos = readVector3(fs);
	l.color = readColorLight(fs);
	l.intensity = readDouble(fs);
	return l;
}

Camera Reader::readCamera() {
	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_CAMERA) throw std::runtime_error("Expecting to read camera info failed!");

	Camera c;
	c.name = readString(fs);
	c.pos = readVector3(fs);
	c.rotation = readVector3(fs);
	return c;
}

Mesh Reader::readMesh() {
	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_MESH) throw std::runtime_error("Expecting to read mesh info failed!");

	Mesh m;
	m.name = readString(fs);

	int numVerts = readInt(fs);
	for (int i = 0; i < numVerts; i++) {
		m.verts.push_back(readVector3(fs));
		m.uverts.push_back(readVector2(fs));
	}

	int numSubMeshes = readInt(fs);
	for (int i = 0; i < numSubMeshes; i++) {
		SubMesh sm;
		sm.materialName = readString(fs);

		int numTris = readInt(fs);
		std::vector<int> tempTris;
		for (int j = 0; j < numTris * 3; j++) {
			tempTris.push_back(readInt(fs));
		}
		/**
		* This may be different than Unity and could cause issues later - BG
		*/
		for (int k = 0; k < tempTris.size(); k+= 3) {
			sm.tris.push_back(tempTris[k+2]);
			sm.tris.push_back(tempTris[k+1]);
			sm.tris.push_back(tempTris[k]);
		}
		m.submeshes.push_back(sm);
	}
	return m;
}

Material Reader::readMaterial() {
	/**
	 * bytes that are in the ali file
	 */
	const unsigned char NAME = 50;
	const unsigned char TRANSPARENT = 51;
	const unsigned char COLOR = 52;
	const unsigned char MAINTEXTURE = 53;
	//const unsigned char BUMPMAP = 54;
	//const unsigned char NORMALMAP = 55;
	const unsigned char REFLECTIVITY = 56;

	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_MATERIAL) throw std::runtime_error("Expecting to read material info failed!");

	Material m;

	int numProperties = readInt(fs);
	for (int i = 0; i < numProperties; i++) {
		char propertyIndicator = readByte(fs);

		switch (propertyIndicator) {
		case NAME:
			m.name = readString(fs);
			break;
		case TRANSPARENT:
			m.transparency = (readByte(fs) != 0); //0 is false everything else is true
			break;
		case COLOR:
			m.color = readColor(fs);
			break;
		case MAINTEXTURE:
			m.textureMap = readMapData(fs);
			break;
		case REFLECTIVITY:
			m.reflectivity = readDouble(fs);
			break;
		default:
			std::cout << "uh you shouldn't be here" << std::endl;
			break;
		}
	}
	return m;
}

bool Reader::endOfFile() {
	return fs.eof() || fs.peek() == EOF;
}