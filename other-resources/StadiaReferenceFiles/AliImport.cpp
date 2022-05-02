#include "AliImport.h"
#include <vector>
#include "Ali.h"
#include "SceneManager.h"
#include "DirectXMesh.h"

using std::vector;
using namespace Ali;

void Ali::importFile(std::string path, Scene::SceneManager & scene, GPU::RenderManager & renderManager) {
    vector<MeshInst> meshInstances; // keep here until all meshes are imported
    Reader ali(path);
    while(!ali.endOfFile()) {
        AssetType nextAsset = ali.peekNextAsset();
        if(nextAsset == AssetType::INFO) {
            ali.readInfo(); //FUTURE implement
        } else if(nextAsset == AssetType::LIGHT) {
            ali.readLight(); //FUTURE implement
        } else if(nextAsset == AssetType::CAMERA) {
            //FUTURE handle multiple cameras
            Camera aliCamera = ali.readCamera();
            Scene::CameraHandle camera = scene.getActiveCamera();
            camera->setName(aliCamera.name);
            camera->setPosition(aliCamera.position);
            camera->setForwardDirection(aliCamera.forward);
            //FUTURE setting the up direction makes the camera behave unusually
            //camera->setUpDirection(aliCamera.up);
        } else if(nextAsset == AssetType::MATERIAL) {
            Material aliMat = ali.readMaterial();
            Scene::MaterialHandle mat = scene.addMaterial();
            mat->setName(aliMat.name);
            mat->setTransparency(aliMat.transparency);
            mat->setColor(aliMat.color);
        } else if(nextAsset == AssetType::MESH) {
            Mesh aliMesh = ali.readMesh();
            Scene::MeshHandle mesh(new DirectXMesh(renderManager.getGraphicsDevice()));
            scene.addMesh(mesh);
            mesh->setName(aliMesh.name);
            for(auto submesh : aliMesh.submeshes) {
                mesh->addSubmesh(std::move(submesh));
            }
        } else if(nextAsset == AssetType::MESHINST) {
            meshInstances.push_back(ali.readMeshInst());
        } else {
            throw std::runtime_error("encountered unknown asset type");
        }
    }
    // copy mesh instances to the scene only if they refer to a mesh
    for(unsigned int i=0; i < meshInstances.size(); i++) {
        if(scene.hasMesh(meshInstances[i].meshName)) {
            Scene::MeshInstHandle meshInst = scene.addMeshInst();
            Scene::MeshHandle m = scene.getMesh(meshInstances[i].meshName);
            meshInst->setMesh(m);
            meshInst->setTransform(meshInstances[i].transform);
        }
    }
}
