#pragma once

#include <vector>
#include <string>
#include "IMesh.h"
#include "Renderable.h"
// forward decalare
namespace GPU {
    class GraphicsDevice;
}

//TODO put in Scene namespace
class DirectXMesh : public Scene::IMesh {
public:
    DirectXMesh(GPU::GraphicsDevice&);
	std::string             getName() const;
	void                    setName(std::string);

    void                    addSubmesh(const Submesh&);
    int                     submeshCount() const;
    Renderable              getSubmesh(unsigned int i) const; // index to submesh

private:
	std::string             name;
    std::vector<Renderable> submeshes;
    GPU::GraphicsDevice&    graphicsDevice;
};