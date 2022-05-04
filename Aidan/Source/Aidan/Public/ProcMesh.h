// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ProcMesh.generated.h"
UCLASS()
class AIDAN_API AProcMesh : public AActor
{
	//Try using Custom Mesh component instead of Procedural mesh component
	GENERATED_BODY()
		TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D>UVs;
	UPROPERTY()
		UProceduralMeshComponent* ProcMesh;
	//These two variables dont do anything, but are needed to create a procedural mesh
	TArray<FVector> normals;
	TArray<FProcMeshTangent> tangents;

	UMaterialInstanceDynamic* currentMat;

public:
	// Sets default values for this actor's properties
	AProcMesh();
	//void CreateMesh(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs, FString materialName, int sectionIndex);
	void CreateMesh(TArray<FVector> readVerticies, TArray<FVector2D> readUVs, TArray<FString> MaterialNames, int num_submeshes, TArray<TArray<int32>> Alltriangles, TMap<FString, UMaterialInstanceDynamic*> allMats);


protected:
	// Called when the game starts or when spawned

};
