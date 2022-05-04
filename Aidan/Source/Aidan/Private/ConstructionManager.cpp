// Fill out your copyright notice in the Description page of Project Settings.

/*
General Idea of the structure:
The ConstructionManager, as the name implies, handles the construction of the ingame model based on what is read in from the binary reader
The ConstructionManager gives the binary reader the Path to the ALI file, and calls on different methods as data is being given to it.
Since the ALI file is composed of 3 different types of Data, there has to be 3 differnt methods to create and store each object that will be spawned in the world.

Note: the reason why I did not create a seperate material class is because due to how many times the program
asks for a material object it will be overall faster to store all of the materials in a dictionary that the mesh object can read and grab the neccesary material when it is being created.

*/
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

}
//Calls on the C++ binary reader (Reader.h) to begin reading in data from the stored ALI file.
void AConstructionManager::beginReading() {

    FString dir = FPaths::ProjectDir().Append("ali/model.ALI"); // Path that holds the ALI file
    UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *dir);
    std::string path(TCHAR_TO_UTF8(*dir));
    binaryReader = Aidan::Reader(path);
    //Continuously reads in bytes until it reaches the end of the file
    while (!(binaryReader.endOfFile())) {
        //Reads the next set of bytes (which constitues an asset)
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
            //If we reach here we either reached the end of the file, or the file is corrupt
            break;
        }
    }
}
//Builds Point lights in Unreal based on Data read from ALI file
void AConstructionManager::buildLight(Light light) {
    FActorSpawnParameters spawnParams;
    FVector pos = FVector(light.pos.x, light.pos.y, light.pos.z);
    FRotator rot = FRotator(0, 0, 0);
    AProcLight* currentLight = GetWorld()->SpawnActor<AProcLight>(AProcLight::StaticClass(), pos, rot, spawnParams); // Spawning the light actor in the world
    FLinearColor color = FLinearColor(light.color.r, light.color.g, light.color.b, light.color.a); //Format: RGBA

    currentLight->buildLight(pos, color, light.intensity * 10); // Calls on AProc Light class to build the light object
    genlights.Add(currentLight); // Storing the generated light in an array

}

//Build procedural mesh based on data from ALI file.
void AConstructionManager::buildMesh(Mesh mesh) {
    FActorSpawnParameters spawnParams;
    FVector pos = FVector(0, 0, 0);// Position does not matter since the mesh is made up of a set of verticies that determine the shape and position of the mesh.
    FRotator rot = FRotator(0, 0, -90);// Had to rotate all of the meshes, because by default the model is rotated by 90 degrees on the z-axis
    FVector verticie; //Current verticie
    TArray<FVector> allVerticies; //All verticies related to a single mesh
    FVector2D uv; // Current UV
    TArray<FVector2D> Uvs; // Set of all UVs related to a single mesh
    TArray<int32> triangle;
    TArray<TArray<int32>> allTriangles;// Set of all triangles related to a single mesh
    FString MaterialName;// Name of the material as stated in the ALI file.
    int num_submeshes = 0; // Number of submeshes within the mesh.
    TArray<FString> materialNames;
    AProcMesh* currentMesh = GetWorld()->SpawnActor<AProcMesh>(AProcMesh::StaticClass(), pos, rot, spawnParams); // Spawning the mesh in the world
   // currentMesh->SetActorLabel(mesh.name.c_str()); (Displays the name of the mesh in the world outliner.This is here for debug purposes, but cannot be included in a packaged build.)

    UE_LOG(LogTemp, Warning, TEXT("generating %s "), mesh.name.c_str()); //Note due to some weird conversion with c++ to Fstring, the string does not display correctly.
    //This next section reads in all of the data associated with each aspect of the mesh, 
    //and converts them from c++ datatypes into Unreal Engine datatypes. 

    // Reading and storing all of the verticie data stored in the current mesh Object
    for (int i = 0; i < mesh.verts.size(); i++) {

        verticie.X = mesh.verts[i].x;
        verticie.Y = mesh.verts[i].y;
        verticie.Z = mesh.verts[i].z;
        allVerticies.Add(verticie);
    }
    // Reading and storing all of the UV data stored in the current mesh Object
    for (int j = 0; j < mesh.uverts.size(); j++) {
        uv.X = mesh.uverts[j].x;
        uv.Y = mesh.uverts[j].y;
        Uvs.Add(uv);
    }

    // Reading and storing all of the Triangle data for each submesh stored in the current mesh Object
    for (int i = 0; i < mesh.submeshes.size(); i++) {
        num_submeshes += 1;
        for (int k = 0; k < mesh.submeshes[i].tris.size(); k++) {
            triangle.Add(mesh.submeshes[i].tris[k]);
        }

        allTriangles.Add(triangle);
        triangle.Empty();
        materialNames.Add(mesh.submeshes[i].materialName.c_str());

    }
    currentMesh->CreateMesh(allVerticies, Uvs, materialNames, num_submeshes, allTriangles, genMats);// Creating a procedural mesh based on the data.
    genMeshes.Add(currentMesh); // Storing the generated mesh in an Array


}
//Builds Unreal Materials based on Data from the ALI file.
void AConstructionManager::buildMaterial(Material matdata) {

    UE_LOG(LogTemp, Warning, TEXT("generating %s "), matdata.name.c_str());
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile(); // Gets the current directory of the project.


    //Core idea of build material
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


    FString MaterialName = matdata.name.c_str();

    FStringAssetReference DefaultMatPath; // Path to the current material
    bool textureAsset; // Checks wether the material has a texture or not
    bool hasBumpMap;// Checks if the material has a bump map
    bool hasNormalMap;// Checks if the mat
    UObject* DefaultMat;


    //Some materials don't come with textures (Those that don't have an empty image extension).
    if (matdata.textureMap.extension == "") {
        //Default material that is stored in the editor 
        /*
        * Includes:
        * Base Color Vector Parameter (Called "Color" in material editor)
        * Reflectivity (Default value is 1)
        * Transparency (Default value is 1)
        */
        DefaultMatPath = ("/Game/Materials/DefaultMaterial.DefaultMaterial");
        textureAsset = false;
    }

    else {
        // Default Texture material that is stored in the editor
            /*
            * Includes:
            * Texture2D Vector Parameter(Called "Texture" in material editor): This will apply the texture image to the material
            * X-Tilling & Y-Tilling: determines how often the texture is repeated on a mesh
            * NormalMap Vector Parameter: This will apply the NormalMap image to the material
            * Reflectivity (Default value is 1)
            * Transparency (Default value is 1)
            */
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
    //Loads the correct material based on data of the current material
    if (DefaultMatPath.TryLoad() != nullptr) {
        DefaultMat = DefaultMatPath.TryLoad();
    }
    else {

        DefaultMat = nullptr; // Should not happen as long as the program finds the base materials

    }
    //Grabbing the material from the specified path
    UMaterial* genMat = Cast<UMaterial>(DefaultMat);
    /*Dynamically creates a material Object that inherits all of the properties of the corresponding base material in the editor
    *This is needed because we need to manipulate the attributes of the base material to match the data stored in the ALI file.
    */
    UMaterialInstanceDynamic* customMaterial = UMaterialInstanceDynamic::Create(genMat, this);

    //Setting the opacity of the material based on a true / false value of the material (Note: Opacity and transparency are inversely related)
    if (matdata.transparency) {
        customMaterial->SetScalarParameterValue("Transparency", 0);
    }
    else {
        customMaterial->SetScalarParameterValue("Transparency", 1);

    }
    //Refelctivity and roughness are inversely related, so you have to subtract 1 to get the roughness.
    customMaterial->SetScalarParameterValue("Reflectivity", 1 - matdata.reflectivity);
    //If the material does not have a texture, then we base the material on its color.
    if (!textureAsset) {
        //Converting c++ data to Unreal Data
        FLinearColor baseColor;
        auto* colorPtr = &baseColor;
        colorPtr->A = matdata.color.a;
        colorPtr->B = matdata.color.b;
        colorPtr->G = matdata.color.g;
        colorPtr->R = matdata.color.r;

        customMaterial->SetVectorParameterValue("Color", baseColor); // Applying the color
    }
    if (textureAsset) {

        FString TextureDir = FPaths::ProjectDir().Append("textures");
        //Creating a new path to store the texture images.
        if (!PlatformFile.DirectoryExists(*TextureDir)) {
            PlatformFile.CreateDirectory(*TextureDir);
            UE_LOG(LogTemp, Warning, TEXT("DIRECRORY TEXTURES CREATED"));
        }

        /*
        * This segment of code creates the texture image file using a binary writer and stores it in the textures directory.
        */
        std::string baseTexturePath = matdata.name + matdata.textureMap.extension;
        FString TexturePath = (baseTexturePath).c_str();
        TexturePath = TextureDir + "/" + TexturePath;
        std::string path(TCHAR_TO_UTF8(*TexturePath));
        UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *TexturePath);
        std::ofstream outfileTexture(path, std::ios::out | std::ios::binary);
        outfileTexture.write(&matdata.textureMap.data[0], matdata.textureMap.data.size());
        outfileTexture.close();

        //Setting the X and Y Tilling
        customMaterial->SetScalarParameterValue("X-Tilling", matdata.textureMap.xTiling);
        customMaterial->SetScalarParameterValue("Y-Tilling", matdata.textureMap.yTiling);

        //Converting the image into a texture file
        /*
        * Note: this does not work correctly. Currently This Unreal Engine method
          only supports 8 and 16 bit depth images to be imported, while the images we are creating are 64 bits.
          While the base image loads correctly because the Bit Depth is too large the textures appear miscolored.
          There is a blueprint within the scene that we tried to implement to import the 64 bit images at runtime
          but we could not get it working.
        */
        UTexture2D* genTexture = FImageUtils::ImportFileAsTexture2D(path.c_str());
        customMaterial->SetTextureParameterValue("Texture", genTexture);
    }

    //Normal Map

    if (hasNormalMap) {

        //Creating a new path to store the NormalMap images.
        FString normalDir = FPaths::ProjectDir().Append("normalMaps");
        if (!PlatformFile.DirectoryExists(*normalDir)) {
            PlatformFile.CreateDirectory(*normalDir);
            UE_LOG(LogTemp, Warning, TEXT("DIRECRORY NORMALMAPS CREATED"));
        }

        /*
         This segment of code creates the NormalMap image file using a binary writer
          and stores it in the NormalMap directory.
        */
        std::string baseNormalMapPath = "normalMaps/";
        std::string baseNormalMapPathstr = baseNormalMapPath + matdata.name + matdata.normalMap.extension;
        FString NormalPath = baseNormalMapPathstr.c_str();
        FString NormalDir = FPaths::ProjectDir().Append(NormalPath);
        std::string path2(TCHAR_TO_UTF8(*NormalDir));
        UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *NormalDir);
        std::ofstream outfileNormal(path2 + matdata.name + matdata.normalMap.extension, std::ios::out | std::ios::binary);
        outfileNormal.write(&matdata.normalMap.data[0], matdata.normalMap.data.size());
        //Note since the current ALI file does not have any normalMaps, this will do nothing.
        UTexture2D* genNormal = FImageUtils::ImportFileAsTexture2D(path2.c_str());
        customMaterial->SetTextureParameterValue("NormalMap", genNormal);

    }
    //Bump Map
    if (hasBumpMap) {
        //Creating a new path to store the BumpMap images.
        FString bumpMapDir = FPaths::ProjectDir().Append("bumpMaps");
        if (!PlatformFile.DirectoryExists(*bumpMapDir)) {
            PlatformFile.CreateDirectory(*bumpMapDir);
            UE_LOG(LogTemp, Warning, TEXT("DIRECRORY BUMPMAPS CREATED"));
        }
        /*
         This segment of code creates the BumpMap image file using a binary writer
         and stores it in the BumpMap directory.
       */
        std::string baseBumpMapPath = "bumpMaps/";
        std::string baseBumpMapPathstr = baseBumpMapPath + matdata.name + matdata.bumpMap.extension;
        FString BumpPath = baseBumpMapPathstr.c_str();
        FString BumpDir = FPaths::ProjectDir().Append(BumpPath);
        std::string path3(TCHAR_TO_UTF8(*BumpDir));
        UE_LOG(LogTemp, Warning, TEXT("DIRECRORY %s "), *BumpDir);
        std::ofstream outfileBump(path3 + matdata.name + matdata.bumpMap.extension, std::ios::out | std::ios::binary);
        outfileBump.write(&matdata.bumpMap.data[0], matdata.bumpMap.data.size());

        //I havent changed the Material to include BumpMaps, because the Current ALI file does not have any bumpMaps.
        //So this section of code does nothing currently.
    }

    genMats.Add(MaterialName, customMaterial); // Storing the created material
}


