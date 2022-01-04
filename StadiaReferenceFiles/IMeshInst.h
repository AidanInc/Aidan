#pragma once
#include <string>
#include <memory>
#include "DataTypes.h"

namespace Scene {
    // forward declare
    class IMesh;
    typedef std::shared_ptr<IMesh> MeshHandle;

    class IMeshInst {
    public:
        virtual ~IMeshInst() {};

        virtual void          setMesh(MeshHandle) = 0;
        virtual MeshHandle    getMesh() const =0;

        virtual void          setTransform(const Transform&) =0;
        virtual Transform     getTransform() const =0;
    };

    typedef std::shared_ptr<IMeshInst> MeshInstHandle;
}