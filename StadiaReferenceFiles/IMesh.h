#pragma once
#include <string>
#include <memory>
#include "DataTypes.h"

namespace Scene {
    class IMesh {
    public:
        virtual ~IMesh() {};
        virtual std::string    getName() const =0;
        virtual void           setName(std::string) =0;

        virtual void           addSubmesh(const Submesh&) =0;
    };

    typedef std::shared_ptr<IMesh> MeshHandle;
}