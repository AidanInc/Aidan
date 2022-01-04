#include "BasicMeshInst.h"
#include "IMesh.h"

using namespace Scene;
void BasicMeshInst::setMesh(MeshHandle m) {
	mesh = m;
}

MeshHandle BasicMeshInst::getMesh() const {
	return mesh;
}

void BasicMeshInst::setTransform(const Transform& t) {
    transform = t;
}

Transform BasicMeshInst::getTransform() const {
    return transform;
}