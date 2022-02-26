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
	//int fileVersion = readInt(fs); //first byte of the file is 1025 in our case	
	//for (int i = 0; i < 10; i++) {
		//std::cout << readInt(fs) << std::endl;
	//}
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

		//throw std::runtime_error("Asset type not found");
	};
}

Light Reader::readLight() {
	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_LIGHT) throw std::runtime_error("Expecting to read light info failed!");

	Light l;
	l.color = readColor(fs);
	l.intensity = readFloat(fs);
	l.pos = readVector3(fs);
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

	int subMeshCount = readInt(fs);
	for (int i = 0; i < subMeshCount; i++) {
		m.submeshes.push_back(readSubMesh(fs));
	}
	return m;
}

Material Reader::readMaterial() {
	unsigned char nextAsset = readByte(fs);
	if (nextAsset != ASSET_TYPE_MATERIAL) throw std::runtime_error("Expecting to read material info failed!");

	Material m;
	m.transparency = readByte(fs);
	m.color = readColor(fs);
	m.name = readString(fs);
	return m;
}

bool Reader::endOfFile() {
	return fs.eof() || fs.peek() == EOF;
}