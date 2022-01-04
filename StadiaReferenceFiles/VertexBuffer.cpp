#include "VertexBuffer.h"
#include <assert.h>
using namespace GPU;

void VertexBuffer::create(std::vector<Vertex>& data, GraphicsDevice& graphicsDevice) {
    assert(data.size() > 0); // invariant: data has 1 or more elements
    BufferUse bufferUse = BufferUse::VERTEX;
    void* dataPtr = &data[0]; // ponter to first element
    // ok to do because std::vector promises to maintian elements contiguously in memory
    unsigned int size = (unsigned int)data.size() * sizeof(data[0]);  // size in bytes
    // call implementation class
    allocateBuffer(bufferUse, dataPtr, size, graphicsDevice);
}

void VertexBuffer::update(std::vector<Vertex>& data, GraphicsDevice& graphicsDevice) {
    assert(data.size() > 0); // invariant: data has 1 or more elements
    assert(data.size() == this->size());
    void* dataPtr = &data[0];                           // ponter to first element
    unsigned int size = (unsigned int)data.size() * sizeof(data[0]);  // size in bytes
    // call implementation class
    updateBuffer(dataPtr, size, graphicsDevice);
}

unsigned int VertexBuffer::size() const {
    return GPUBuffer::sizeInBytes() / sizeof(Vertex);
}

ID3D11Buffer* const  VertexBuffer::getBuffer() {
    return GPUBuffer::getBuffer();
}