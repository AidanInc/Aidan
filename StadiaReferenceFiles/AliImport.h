#pragma once
#include "RenderManager.h"
#include "SceneManager.h"
// code not shared with any other project
// supplimentary functions which extend the Ali namespace

namespace Ali {
    // import ali file from path to scene
    void importFile(std::string path,
                    Scene::SceneManager& scene,
                    GPU::RenderManager& renderManager);
}