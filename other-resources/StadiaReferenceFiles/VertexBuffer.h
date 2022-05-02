#pragma once
#include <vector>
#include "GPUBuffer.h"
#include "Vertex.h"
namespace GPU {
    // inherits implementation from GPUBuffer
    class VertexBuffer : private GPUBuffer {
    public:
        void                 create(std::vector<Vertex>& data, GraphicsDevice&);
        void                 update(std::vector<Vertex>& data, GraphicsDevice&);
        unsigned int         size() const;
        ID3D11Buffer* const  getBuffer();
    };
}