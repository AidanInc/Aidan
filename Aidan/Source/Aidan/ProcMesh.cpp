// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMesh.h"

// Sets default values
AProcMesh::AProcMesh()
{
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMesh");
	RootComponent = ProcMesh;
}

void AProcMesh::CreateMesh()
{
	Vertices.Add(FVector(-50, 0, 50));
	Vertices.Add(FVector(-50, 0, -50));
	Vertices.Add(FVector(50, 0, 50));
	Vertices.Add(FVector(50, 0, -50));

	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));

	//Triangle1
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	//Triangle2
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(3);

	ProcMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	if (Material)
	{
		ProcMesh->SetMaterial(0, Material);
	}
}

// Called when the game starts or when spawned
void AProcMesh::BeginPlay()
{
	Super::BeginPlay();

	CreateMesh();
}


