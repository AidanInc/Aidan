// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <ProcLight.h>
#include "ProcMesh.h"
#include "Reader.h"
#include <Runtime/Engine/Classes/Materials/MaterialExpressionConstant3Vector.h>
#include <Editor/UnrealEd/Classes/Factories/MaterialFactoryNew.h>
#include <Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h>
#include <Runtime/Engine/Classes/Materials/MaterialExpressionConstant.h>
#include "Algo/Reverse.h"




#include "ConstructionManager.generated.h"

UCLASS()
class AIDAN_API AConstructionManager : public AActor
{
	GENERATED_BODY()
	TArray<AProcLight*> genlights;
	TArray<AProcMesh*> genMeshes;
	Aidan::Reader binaryReader;
	Aidan::AssetType currentAsset;
	

public:
	// Sets default values for this pawn's properties
	AConstructionManager();
	void buildMaterial(Material matData); // insert matData object here
	void buildLight(Light light); //Insert Data in the format: FVector4 Color (R,G,B,A), float lightIntensity,FVector lightPosition
	void buildMesh(Mesh mesh); // Insert Data in the format: TArray<FVector> Verticies, TArray<int32> Triangles, TArray<FVector2D> UVs, FString materialName
	void beginReading();
	bool stopMeshBuild;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};