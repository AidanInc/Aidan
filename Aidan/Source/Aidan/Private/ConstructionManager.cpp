// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionManager.h"
#include <Runtime/Engine/Public/ImageUtils.h>




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
    TArray<TArray<int32>> allTriangles;
    FString MaterialName;
    int num_submeshes = 0;
    TArray<TArray<int32>> tris_per_submesh;
    TArray<FString> materialNames;
    pos = FVector(0, 0, 0);
    rot = FRotator(0, 0, -90);
    AProcMesh* currentMesh = GetWorld()->SpawnActor<AProcMesh>(AProcMesh::StaticClass(), pos, rot, spawnParams);
   // currentMesh->SetActorLabel(mesh.name.c_str());
    // Lets try merging this into 1 single procedural mesh instead.
    //Could be a verticie issuse
    for (int i = 0; i < mesh.verts.size(); i++) {
        //Mention how vertices that are really close to each other vary in value (causing the warping)
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

        allTriangles.Add(triangle);
        triangle.Empty();
        materialNames.Add(currentSubmesh.materialName.c_str());
        //tris_per_submesh.Add(triangle);

    }
    if (allTriangles.Num() <= 3) {
        //hi
    }
    currentMesh->CreateMesh(allVerticies, Uvs, materialNames, num_submeshes, allTriangles, genMats);// Insert Data into here
    genMeshes.Add(currentMesh);


}
void AConstructionManager::buildMaterial(Material matdata) {
    //Code was obtained from: https://isaratech.com/ue4-programmatically-create-a-new-material-and-inner-nodes/
    UE_LOG(LogTemp, Warning, TEXT("generating %s "), matdata.name.c_str());
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

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

    FStringAssetReference DefaultMatPath;
    bool textureAsset;
    bool hasBumpMap;
    bool hasNormalMap;
    //auto MyAsset = MyAssetPath.TryLoad();
    UObject* DefaultMat;
    //Some materials don't come with textures.
    if (matdata.textureMap.extension == "") {
        DefaultMatPath = ("/Game/Materials/DefaultMaterial.DefaultMaterial");
        textureAsset = false;
    }
    else {
        DefaultMatPath = ("/Game/Materials/DefaultTextureMaterial.DefaultTextureMaterial");
        textureAsset = true;
    }
    if (matdata.normalMap.extension == "") {
        hasNormalMap = false;
    }
    else {
        hasNormalMap = true;
    }
    if (matdata.bumpMap.extension == "") {
        hasBumpMap = false;
    }
    else {
        hasBumpMap = true;
    }


    if (DefaultMatPath.TryLoad() != nullptr) {
        DefaultMat = DefaultMatPath.TryLoad();
    }
    else {
        DefaultMat = nullptr;
        //This is bad
    }

    UMaterial* genMat = Cast<UMaterial>(DefaultMat);
    UMaterialInstanceDynamic* customMaterial = UMaterialInstanceDynamic::Create(genMat, this);

    //Setting the opacity of the material
    if (matdata.transparency) {
        customMaterial->SetScalarParameterValue("Transparency", 0);
    }
    else {
        customMaterial->SetScalarParameterValue("Transparency", 1);

    }
    customMaterial->SetScalarParameterValue("Reflectivity", 1 - matdata.reflectivity);
    if (!textureAsset) {
        FLinearColor baseColor;
        auto* colorPtr = &baseColor;
        colorPtr->A = matdata.color.a;
        colorPtr->B = matdata.color.b;
        colorPtr->G = matdata.color.g;
        colorPtr->R = matdata.color.r;

        customMaterial->SetVectorParameterValue("Color", baseColor);
    }
    if (textureAsset) {

        /*FString dir = FPaths::ProjectDir().Append("ali/model.ALI");
        UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *dir);
        std::string path(TCHAR_TO_UTF8(*dir));
        */
        //texture Map

		FString TextureDir = FPaths::ProjectDir().Append("textures");
		if (!PlatformFile.DirectoryExists(*TextureDir)) {
			PlatformFile.CreateDirectory(*TextureDir);
			UE_LOG(LogTemp, Warning, TEXT("DIRECRORY TEXTURES CREATED"));
		}


        std::string baseTexturePath = "textures/" + matdata.name + matdata.textureMap.extension;
        FString TexturePath = (baseTexturePath).c_str();
        FString TestTexture = FPaths::ProjectDir().Append("textures/test.png");
        std::string path(TCHAR_TO_UTF8(*TestTexture));
        UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *TestTexture);
      
       // std::ofstream outfileTexture(path, std::ios::out | std::ios::binary);
        std::ofstream outfileTexture("C:/Users/malik/OneDrive/Desktop/Software Engineering Capstone/Capstone 3/test_folder/" + matdata.name + matdata.textureMap.extension, std::ios::out | std::ios::binary);
        outfileTexture.write(&matdata.textureMap.data[0], matdata.textureMap.data.size());
        outfileTexture.close();

        //FStringAssetReference DefaultTexturePath(TextureDir);

        //DefaultTexturePath.TryLoad();
        
       /* UObject* matTexture;
        if (DefaultTexturePath.TryLoad() != nullptr) {
            matTexture = DefaultMatPath.TryLoad();
        }
        else {
            matTexture = nullptr;
            //This is bad
        }*/
        //Converting the image into a texture
       // UTexture2D* genTexture = Cast<UTexture2D>(matTexture);
        
        customMaterial->SetScalarParameterValue("X-Tilling", matdata.textureMap.xTiling);
        customMaterial->SetScalarParameterValue("Y-Tilling", matdata.textureMap.yTiling);
        UTexture2D* genTexture = FImageUtils::ImportFileAsTexture2D(path.c_str());
        customMaterial->SetTextureParameterValue("Texture", genTexture);
    }

    //Normal Map
    std::string baseNormalMapPath = "materials/normalMaps/";
    std::string baseNormalMapPathstr = baseNormalMapPath + matdata.name + matdata.normalMap.extension;
    FString NormalPath = baseNormalMapPathstr.c_str();
    FString NormalDir = FPaths::ProjectDir().Append(NormalPath);
    std::string path2(TCHAR_TO_UTF8(*NormalDir));
    UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *NormalDir);

   // std::ofstream outfileNormal("C:/Users/malik/OneDrive/Desktop/Software Engineering Capstone/Capstone 3/test_folder/"+ matdata.name + matdata.normalMap.extension, std::ios::out | std::ios::binary);
    //outfileNormal.write(&matdata.normalMap.data[0], matdata.normalMap.data.size());

    //Bump Map
    std::string baseBumpMapPath = "materials/bumpMaps/";
    std::string baseBumpMapPathstr = baseBumpMapPath + matdata.name + matdata.bumpMap.extension;
    FString BumpPath = baseBumpMapPathstr.c_str();
    FString BumpDir = FPaths::ProjectDir().Append(BumpPath);

    std::string path3(TCHAR_TO_UTF8(*BumpDir));

    UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *BumpDir);

    //std::ofstream outfileBump("C:/Users/malik/OneDrive/Desktop/Software Engineering Capstone/Capstone 3/test_folder/" + matdata.name + matdata.bumpMap.extension, std::ios::out | std::ios::binary);
    //outfileBump.write(&matdata.bumpMap.data[0], matdata.bumpMap.data.size());

    genMats.Add(MaterialName, customMaterial);


}

