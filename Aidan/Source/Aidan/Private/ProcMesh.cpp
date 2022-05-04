// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMesh.h"


// Sets default values
AProcMesh::AProcMesh()
{
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh"); // Create a procedural mesh object
	RootComponent = ProcMesh;
}


void AProcMesh::CreateMesh(TArray<FVector> readVerticies, TArray<FVector2D> readUVs, TArray<FString> MaterialNames, int num_submeshes, TArray<TArray<int32>> allTriangles, TMap<FString, UMaterialInstanceDynamic*> allMats)
{
	//Iterates through all submeshes
	for (int i = 0; i < num_submeshes; i++) {
		//Unreal method that will create a section of a procedural mesh based on data.
		//Each submesh will occupy a mesh section
		ProcMesh->CreateMeshSection(i, readVerticies, allTriangles[i], TArray<FVector>(), readUVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
		currentMat = allMats.FindRef(MaterialNames[i]); // Grabbing the Material associated with the mesh section for the material dictionary
		//If the material is found, then it is applied to the mesh section.
		if (currentMat != nullptr)
		{
			ProcMesh->SetMaterial(i, currentMat);
		}
	}

}


