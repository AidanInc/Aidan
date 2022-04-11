// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMesh.generated.h"



UCLASS()
class AIDAN_API AProcMesh : public AActor
{
	//Try using Custom Mesh component instead of Procedural mesh component
	GENERATED_BODY()
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D>UVs;
	FString materialPath = "/Game/Materials/DefaultMaterial_Inst";
	//FString materialPath = "/Game/Materials/";
	FString baseMaterialPath = "/Game/Materials/";
	UPROPERTY()
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> normals;
	TArray<FProcMeshTangent> tangents;
	UMaterial* currentMat;
	UMaterialInterface* material;
	UMaterial** currentMatPtr;

public:
	// Sets default values for this actor's properties
	AProcMesh();
	//void CreateMesh(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs, FString materialName, int sectionIndex);
	void CreateMesh(TArray<FVector> readVerticies, TArray<FVector2D> readUVs, TArray<FString> MaterialNames, int num_submeshes, TArray<int32> triangles, TMap<FString, UMaterial*> allMats);
	//TArray<FVector4> calculateTangents(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs);
	//Vector calculateNormals(TArray<int32> readTriangles, int current_set);

protected:
	// Called when the game starts or when spawned

};
