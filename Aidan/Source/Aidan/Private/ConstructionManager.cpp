// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionManager.h"





// Sets default values
AConstructionManager::AConstructionManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //binaryReader = Reader("insert_Path_here");

}

// Called when the game starts or when spawned
void AConstructionManager::BeginPlay()
{
	Super::BeginPlay();
    //beginReading();
	
}


/*template <typename ObjClass>
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
   

    while (!(binaryReader.endOfFile())) {
        currentAsset = binaryReader.peekNextAsset();
        if (currentAsset == AssetType::MATERIAL) {
            auto material = binaryReader.readMaterial();
            buildMaterial(material);

        }
        else if (currentAsset == AssetType::MESH) {
            auto mesh = binaryReader.readMesh();

        }
        
        else if (currentAsset == AssetType::LIGHT) {
            auto Light = binaryReader.readLight();
            buildLight(Light);

        }
        else if (currentAsset == AssetType::CAMERA) {

        }
        else {
            //Break here
        }
    }
}
void AConstructionManager::buildLight(Light light) {

    AProcLight* currentLight = nullptr;
    FLinearColor color;
    color.A = light.color.a;
    color.B = light.color.b;
    color.R = light.color.r;
    color.G = light.color.g;
    FVector position;
    position[0] = light.pos.x;
    position[1] = light.pos.y;
    position[2] = light.pos.z;


    currentLight->buildLight(position,color,light.intensity); // Insert data here
    genlights.Add(currentLight);

}
void AConstructionManager::buildMesh(Mesh mesh) {
    //AProcMesh* currentMesh;
    FVector verticie;
    TArray<FVector> allVerticies;
    FVector uv;
    TArray<FVector2D> Uvs;
    TArray<int32> triangles;
    FString MaterialName;
    for (int i = 0; i < mesh.verts.size(); i++) {
        verticie.X = mesh.verts[i].x;
        verticie.Y = mesh.verts[i].y;
        verticie.Z = mesh.verts[i].z;
        allVerticies.Add(verticie);
    }
    for (int i = 0; i < mesh.uverts.size(); i++) {
        
    }
    
    //currentMesh->CreateMesh();// Insert Data into here
    //genMeshes.Add(currentMesh);
}
void AConstructionManager::buildMaterial(Material matdata) {
    //Code was obtained from: https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
    //    UE_LOG(LogTemp, Warning, TEXT("generating %s ", matdata.name));

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
    FString PackageName = "/Game/Materials"; // This is where we will store the materials (root directory is /Game/)
    PackageName += MaterialName;
    //Trying to load the material
    if (LoadMaterialFromPath(FName(*PackageName)) != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("This Material Already exists"));
        return;
    }
    UPackage* Package = CreatePackage(NULL, *PackageName); // Research this method (we don't want to create multiple of the same material
    auto MaterialFactory = NewObject<UMaterialFactoryNew>();
    UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, *MaterialName, RF_Standalone | RF_Public, NULL, GWarn);
    FAssetRegistryModule::AssetCreated(UnrealMaterial);
    Package->FullyLoad();
    Package->SetDirtyFlag(true);

    //The material will update itself if necessary
    UnrealMaterial->PreEditChange(NULL);
    UnrealMaterial->PostEditChange();
    // make sure that any static meshes, etc using this material will stop using the FMaterialResource of the original
    // material, and will use the new FMaterialResource created when we make a new UMaterial in place

    FGlobalComponentReregisterContext RecreateComponents;

    //Setting the opacity of the material
    UMaterialExpressionConstant* OpacityExpression = NewObject<UMaterialExpressionConstant>(UnrealMaterial);
    if (matdata.transparency) {
        OpacityExpression->R = 1;

    }
    else {
        OpacityExpression->R = 0;
    }
   
    UnrealMaterial->Expressions.Add(OpacityExpression);
    UnrealMaterial->Opacity.Expression = OpacityExpression;


    //Setting the Roughness / reflectiveness of the material 
    UMaterialExpressionConstant* RoughExpression = NewObject<UMaterialExpressionConstant>(UnrealMaterial);
    RoughExpression->R = 1 - matdata.reflectivity;// Roughness and reflectiveness are inversly related
    UnrealMaterial->Expressions.Add(RoughExpression);
    UnrealMaterial->Roughness.Expression = RoughExpression;

    //Setting the base color of the material
    UMaterialExpressionConstant3Vector* BaseColorExpression = NewObject<UMaterialExpressionConstant3Vector>(UnrealMaterial);
    UMaterialExpressionTextureSample* TextureExpression = NewObject<UMaterialExpressionTextureSample>(UnrealMaterial);


    FLinearColor baseColor;
    auto* colorPtr = &baseColor;
    colorPtr->A = matdata.color.a;
    colorPtr->B = matdata.color.b;
    colorPtr->G = matdata.color.g;
    colorPtr->R = matdata.color.r;

    BaseColorExpression->Constant = baseColor;
    UnrealMaterial->Expressions.Add(BaseColorExpression);
    UnrealMaterial->BaseColor.Expression = BaseColorExpression;
    //Come back for tilling / shader stuff

    /* UMaterialExpressionMultiply* Multiply = NewObject<UMaterialExpressionMultiply>(UnrealMaterial);
     UnrealMaterial->Expressions.Add(Multiply);
     

}
*/
