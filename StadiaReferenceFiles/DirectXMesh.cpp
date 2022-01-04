#include "DirectXMesh.h"
#include "GraphicsDevice.h"
using namespace GPU;

DirectXMesh::DirectXMesh(GraphicsDevice& gd) 
    : graphicsDevice(gd) {}

std::string DirectXMesh::getName() const {
	return name;
}
void DirectXMesh::setName(std::string n) {
	name = n;
}

void DirectXMesh::addSubmesh(const Submesh& s) {
    // convert submesh to renderable
    Renderable renderable;
    // add vertices
    std::vector<Vertex> vertexData(s.vertices.size());
    // convert from Submesh vertex format to DirectX vertex format
    for(unsigned int i=0; i < s.vertices.size(); i++) {
        Vector3 vert = s.vertices[i];
        Vector2 uv = s.uvs[i];
        DirectX::XMFLOAT3 position(vert.x, vert.y, vert.z);
        DirectX::XMFLOAT3 textureUV(uv.u, uv.v, 1.0f);
        vertexData[i] = { position, textureUV };
    }
    renderable.vertexBuffer.create(vertexData, graphicsDevice);

    // add indices
    std::vector<short> indexData(s.tris.size() * 3);
    // convert from Submesh index format to DirectX index format
    for(auto t : s.tris) {
        indexData.push_back(t.a);
        indexData.push_back(t.b);
        indexData.push_back(t.c);
    }
    renderable.indexBuffer.create(indexData, graphicsDevice);

    // add material
    renderable.material = s.material;
    submeshes.push_back(renderable);
}

int DirectXMesh::submeshCount() const {
    return submeshes.size();
}

Renderable DirectXMesh::getSubmesh(unsigned int i) const {
    return submeshes.at(i);
}