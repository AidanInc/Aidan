// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ProcLight.h>
#include "ProcMesh.h"
#include "Reader.h"
#include <Runtime/Engine/Public/ImageUtils.h>
#include <iostream>
#include <fstream>
#include "ConstructionManager.generated.h"

UCLASS()
class AIDAN_API AConstructionManager : public AActor
{
	GENERATED_BODY()
		TArray<AProcLight*> genlights;
	TArray<AProcMesh*> genMeshes;
	Aidan::Reader binaryReader; //Binary reader object
	Aidan::AssetType currentAsset;// Will store the current object stored in the ALI file
	TMap<FString, UMaterialInstanceDynamic*> genMats; // Dictonary that stores all of the Materials in the ALI file.
public:
	// Constructor function. 
	AConstructionManager();
	//Builds Unreal Materials based on Data from the ALI file.
	void buildMaterial(Material matData);
	//Builds Point lights in Unreal based on Data read from ALI file
	void buildLight(Light light);
	//Build procedural mesh based on data from ALI file.
	void buildMesh(Mesh mesh);
	// Starts the binary reader.
	void beginReading();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};