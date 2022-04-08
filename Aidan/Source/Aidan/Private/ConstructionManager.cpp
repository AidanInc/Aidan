// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionManager.h"




// Sets default values
AConstructionManager::AConstructionManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
   

}

// Called when the game starts or when spawned
void AConstructionManager::BeginPlay()
{
	Super::BeginPlay();
    beginReading();
    //beginReading();
	
}


template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
{
    if (Path == NAME_None) return nullptr;

    return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), nullptr, *Path.ToString()));
}

static FORCEINLINE UMaterial* LoadMaterialFromPath(const FName& Path)
{
    if (Path == NAME_None) return nullptr;

    return LoadObjFromPath<UMaterial>(Path);
}

void AConstructionManager::beginReading() {

    FString dir = FPaths::ProjectDir().Append("ali/model.ALI");
	UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *dir);
    std::string path(TCHAR_TO_UTF8(*dir));
    binaryReader = Aidan::Reader(path);

    while (!(binaryReader.endOfFile())) {
        currentAsset = binaryReader.peekNextAsset();
        if (currentAsset == Aidan::AssetType::MATERIAL) {
            auto material = binaryReader.readMaterial();
            buildMaterial(material);

        }
        else if (currentAsset == Aidan::AssetType::MESH) {
            auto mesh = binaryReader.readMesh();
                buildMesh(mesh);
        }
        
        else if (currentAsset == Aidan::AssetType::LIGHT) {
            auto Light = binaryReader.readLight();
            buildLight(Light);

        }
        else if (currentAsset == Aidan::AssetType::CAMERA) {

        }
        else {
            //Break here
        }
    }
}
void AConstructionManager::buildLight(Light light) {
    FActorSpawnParameters spawnParams;
    FVector pos = FVector(light.pos.x, light.pos.y, light.pos.z);
    FRotator rot = FRotator(0, 0, 0);
    AProcLight* currentLight = GetWorld()->SpawnActor<AProcLight>(AProcLight::StaticClass(), pos, rot, spawnParams);
    FLinearColor color = FLinearColor(light.color.r, light.color.g, light.color.b, light.color.a);

    currentLight->buildLight(pos, color, light.intensity);
    genlights.Add(currentLight);

}
void AConstructionManager::buildMesh(Mesh mesh) {
    FActorSpawnParameters spawnParams;
    FVector pos;
    FRotator rot;
    FVector verticie;
    TArray<FVector> allVerticies;
    FVector2D uv;
    TArray<FVector2D> Uvs;
    TArray<int32> triangle;
    TArray<FVector> allTriangles;
    FString MaterialName;
    int num_submeshes = 0;
    TArray<TArray<int32>> tris_per_submesh;
    TArray<FString> materialNames;
    pos = FVector(0, 0, 0);
    rot = FRotator(0, 0, -90);
    AProcMesh* currentMesh = GetWorld()->SpawnActor<AProcMesh>(AProcMesh::StaticClass(), pos, rot, spawnParams);
    for (int i = 0; i < mesh.verts.size(); i++) {

        verticie.X = mesh.verts[i].x;
        verticie.Y = mesh.verts[i].y;
        verticie.Z = mesh.verts[i].z;
        allVerticies.Add(verticie);
    }
    for (int j = 0; j < mesh.uverts.size(); j++) {
        uv.X = mesh.uverts[j].x;
        uv.Y = mesh.uverts[j].y;
        Uvs.Add(uv);
    }
    //Main Problem. Some of the triangles are still not being set correctly. (only for walls)
    UE_LOG(LogTemp, Warning, TEXT("generating %s "), mesh.name.c_str());
    for (int i = 0; i < mesh.submeshes.size(); i++) {
        num_submeshes += 1;
        auto currentSubmesh = mesh.submeshes[i];

        for (int k = 0; k < currentSubmesh.tris.size(); k++) {

            triangle.Add(mesh.submeshes[i].tris[k]);
        }

        materialNames.Add(currentSubmesh.materialName.c_str());
        //tris_per_submesh.Add(triangle);



    }
    currentMesh->CreateMesh(allVerticies, Uvs, materialNames, num_submeshes, triangle, genMats);// Insert Data into here
    genMeshes.Add(currentMesh);


}
void AConstructionManager::buildMaterial(Material matdata) {
    //Code was obtained from: https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
    UE_LOG(LogTemp, Warning, TEXT("generating %s "), matdata.name.c_str());

    // Determining Shaders from material properties
    //                           Color | TextureMap | Transparent | Reflective
    // Transparent Reflective -----x-------------------------x----------x------
    // Transparent Colored --------x-------------------------x-----------------
    // Diffuse Textured ----------------------x--------------------------------
    // Diffuse Colored ------------x-------------------------------------------
    // Default ----------------------------------------------------------------
    //
    // a physical parrallel of our process: Given a childs block of unknown shape, we try to push it though
    // increasingly generic holes. So we would try the Small 10 pointed star hole (transparenty specular) before the
    // large round hole (simple diffuse color).  We push it through (use the shader of) the first hole it will fit.
    // The chart above is sorted from most specialized on top, to most generic on bottom. This is the order we will
    // use to test shaders.
    // Our job here is to create a Unity Material for the material handed from us.
    // the 2 is appended to AliDocument is because "AliDocument" is the namespace name.

    //Creating the material asset
    FString MaterialName = matdata.name.c_str(); // Swap this out for the name of the material we are reading in

    UMaterial* genMat = NewObject<UMaterial>();


    // FGlobalComponentReregisterContext RecreateComponents;

     //Setting the opacity of the material
    UMaterialExpressionConstant* OpacityExpression = NewObject<UMaterialExpressionConstant>(genMat);
    if (matdata.transparency) {
        OpacityExpression->R = 0;
    }
    else {
        OpacityExpression->R = 1;

    }

    genMat->Expressions.Add(OpacityExpression);
    genMat->Opacity.Expression = OpacityExpression;


    //Setting the Roughness / reflectiveness of the material 
    UMaterialExpressionConstant* RoughExpression = NewObject<UMaterialExpressionConstant>(genMat);
    RoughExpression->R = 1 - matdata.reflectivity;// Roughness and reflectiveness are inversly related
    genMat->Expressions.Add(RoughExpression);
    genMat->Roughness.Expression = RoughExpression;

    //Setting the base color of the material
    UMaterialExpressionConstant3Vector* BaseColorExpression = NewObject<UMaterialExpressionConstant3Vector>(genMat);
    UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(genMat);


    FLinearColor baseColor;
    auto* colorPtr = &baseColor;
    colorPtr->A = matdata.color.a;
    colorPtr->B = matdata.color.b;
    colorPtr->G = matdata.color.g;
    colorPtr->R = matdata.color.r;

    BaseColorExpression->Constant = baseColor;
    genMat->Expressions.Add(BaseColorExpression);
    genMat->BaseColor.Expression = BaseColorExpression;
    //Come back for tilling / shader stuff
    // 

      //The material will update itself if necessary
    genMat->PreEditChange(NULL);
    genMat->PostEditChange();
    // make sure that any static meshes, etc using this material will stop using the FMaterialResource of the original
    // material, and will use the new FMaterialResource created when we make a new UMaterial in place

    // UMaterialExpressionMultiply* Multiply = NewObject<UMaterialExpressionMultiply>(genMat);
     //genMat->Expressions.Add(Multiply);
    genMats.Add(MaterialName, genMat);

}

