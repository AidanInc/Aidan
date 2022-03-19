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
	UPROPERTY()
	UProceduralMeshComponent* ProcMesh;

	void CreateMesh();
public:	
	// Sets default values for this actor's properties
	AProcMesh();
	

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;

	virtual void BeginPlay() override;
};
