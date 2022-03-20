// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcMesh.generated.h"

UCLASS()
class AIDAN_API AProcMesh : public AActor
{
	GENERATED_BODY()
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D>UVs;
	FString materialPath = "/Game/Materials/";
	UPROPERTY()
	UProceduralMeshComponent* ProcMesh;
	UMaterial* mat;
	
public:	
	// Sets default values for this actor's properties
	AProcMesh();
	void CreateMesh(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs, FString materialName);
	

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

	virtual void BeginPlay() override;
};
