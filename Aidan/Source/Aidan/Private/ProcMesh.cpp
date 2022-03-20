// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMesh.h"

// Sets default values
AProcMesh::AProcMesh()
{
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh"); // Allows the mesh to spawn in the world
	RootComponent = ProcMesh;
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


void AProcMesh::CreateMesh(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs, FString materialName)
{	//Reading in verticies
	for (int i = 0; readVerticies.Num(); i++) {
		Vertices.Add(readVerticies[i]);
	}
	/*
	Vertices.Add(FVector(-50, 0, 50));
	Vertices.Add(FVector(-50, 0, -50));
	Vertices.Add(FVector(50, 0, 50));
	Vertices.Add(FVector(50, 0, -50));
	*/
	//Reading in Uvs
	for (int i = 0; readUVs.Num(); i++) {
		readUVs.Add(readUVs[i]);
	}
	/*
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));
	*/
	//Reading in Triangles
	for (int i = 0; readUVs.Num(); i++) {
		Triangles.Add(readTriangles[i]);
	}
	/*
	//Triangle1
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	//Triangle2
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(3);
	*/
	//Creating the mesh object
	ProcMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	materialPath += materialName;
	mat = LoadMaterialFromPath(FName(*materialPath)); // Checking if the associated material exists
	if (mat!=nullptr)
	{
		ProcMesh->SetMaterial(0, mat);
	}
}

// Called when the game starts or when spawned
void AProcMesh::BeginPlay()
{
	Super::BeginPlay();

//CreateMesh();
}


