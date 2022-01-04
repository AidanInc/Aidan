#pragma once
#include <DirectXMath.h>
namespace GPU {
    // describe the format of a single vertex in the vertex buffer
    // Must match VertexDescription.h and VertexShaderInput in shader source
    struct Vertex {
        DirectX::XMFLOAT3 position; // xyz
        DirectX::XMFLOAT3 uv;    // rgb
    };
}