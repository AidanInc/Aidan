// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <ProcLight.h>
#include "ProcMesh.h"
#include "Reader.h"
#include "BinaryReader.h"
#include "ReaderData.h"
#include <Runtime/Engine/Classes/Materials/MaterialExpressionConstant3Vector.h>
#include <Editor/UnrealEd/Classes/Factories/MaterialFactoryNew.h>
#include <Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h>
#include <Runtime/Engine/Classes/Materials/MaterialExpressionConstant.h>
#include "ConstructionManager.generated.h"




UCLASS()
class AIDAN_API AConstructionManager : public AActor
{
	GENERATED_BODY()
		TArray<AProcLight*> genlights;
	TArray<AProcMesh*> genMeshes;

public:
	// Sets default values for this pawn's properties
	AConstructionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	void buildMaterial(); // insert matData object here
	void buildLight(FVector4 Color, float lightIntensity, FVector lightPosition); //Insert Data in the format: FVector4 Color (R,G,B,A), float lightIntensity,FVector lightPosition
	void buildMesh(TArray<Fvector> verticies, TArray<int32> Triangles, TArray<FVector2D> UVs, FString MaterialName); // Insert Data in the format: TArray<FVector> Verticies, TArray<int32> Triangles, TArray<FVector2D> UVs, FString materialName

	

};
