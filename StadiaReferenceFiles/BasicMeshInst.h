#pragma once
#include <string>
#include "IMeshInst.h"
namespace Scene {
    class BasicMeshInst : public IMeshInst {
    public:
        void        setName(std::string);
        std::string getName() const;

        void        setMesh(MeshHandle);
        MeshHandle  getMesh() const;

        void        setTransform(const Transform&);
        Transform   getTransform() const;
    private:
        std::string name;
        MeshHandle  mesh;
        Transform   transform;
    };
}