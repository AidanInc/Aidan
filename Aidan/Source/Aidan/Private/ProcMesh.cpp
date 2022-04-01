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


void AProcMesh::CreateMesh(TArray<FVector> readVerticies, TArray<FVector2D> readUVs, TArray<FString> MaterialNames, int num_submeshes, TArray<int32> readTriangles)
{


	/*for (int i = 0; i < mesh.verts.size(); i++) {

		verticie.X = mesh.verts[i].x;
		verticie.Y = mesh.verts[i].y;
		verticie.Z = mesh.verts[i].z;
		allVerticies.Add(verticie);
	}
	for (int i = 0; i < mesh.uverts.size(); i++) {
		uv.X = mesh.uverts[i].x;
		uv.Y = mesh.uverts[i].y;
		Uvs.Add(uv);
	}
	for (int i = 0; i < mesh.submeshes.size(); i++) { // The triangles are in reverse ordrer
		auto submesh = mesh.submeshes[i];
		triangles.Add(submesh.tris[0]);
		triangles.Add(submesh.tris[1]);
		triangles.Add(submesh.tris[2]);
	}*/
	//Reading in verticies
	/*for (int i = 0; i < readVerticies.Num(); i++) {
		Vertices.Add(readVerticies[i]);
	}
	/*
	Vertices.Add(FVector(-50, 0, 50));
	Vertices.Add(FVector(-50, 0, -50));
	Vertices.Add(FVector(50, 0, 50));
	Vertices.Add(FVector(50, 0, -50));
	*/
	//Reading in Uvs
	/*for (int i = 0; i < readUVs.Num(); i++) {
		UVs.Add(readUVs[i]);
	}*/

	/*
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(0, 1));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));
	*/
	//Reading in Triangles
	/*for (int i = 0; i < readTriangles.Num(); i++) {
		Triangles.Add(readTriangles[i]);
	}*/
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
	//mat = nullptr;
	ProcMesh->CreateMeshSection(0, readVerticies, readTriangles, TArray<FVector>(), readUVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);

	for (int i = 0; i < num_submeshes; i++) {

		materialPath += MaterialNames[i].TrimChar(' '); // Removing whiteSpace
		//mat = LoadMaterialFromPath(FName(*materialPath)); // Checking if the associated material exists
		//mat = nullptr;
		if (mat != nullptr)
		{
			ProcMesh->SetMaterial(i, mat);
		}
		materialPath = baseMaterialPath;
	}





}
/*TArray<FVector4> calculateTangents(TArray<FVector> readVerticies, TArray<int32> readTriangles, TArray<FVector2D> readUVs) {

	int triangleCount = readTriangles.Num()/3;
	int vertexCount = readVerticies.Num();

	TArray<FVector> tan1;
	TArray<FVector> tan2;

	TArray<FVector4> tangents;

	for (long a = 0; a < triangleCount; a += 3) {
		long i1 = readTriangles[a + 0];
		long i2 = readTriangles[a + 1];
		long i3 = readTriangles[a + 2];

		FVector v1 = readVerticies[i1];
		FVector v2 = readVerticies[i2];
		FVector v3 = readVerticies[i3];

		FVector2D w1 = readUVs[i1];
		FVector2D w2 = readUVs[i2];
		FVector2D w3 = readUVs[i3];

		float x1 = v2.X - v1.X;
		float x2 = v3.X - v1.X;
		float y1 = v2.Y - v1.Y;
		float y2 = v3.Y - v1.Y;
		float z1 = v2.Z - v1.Z;
		float z2 = v3.Z - v1.Z;

		float s1 = w2.X - w1.X;
		float s2 = w3.X - w1.X;
		float t1 = w2.Y - w1.Y;
		float t2 = w3.Y - w1.Y;

		float r = 1.0f / (s1 * t2 - s2 * t1);

		FVector sdir = FVector((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
		FVector tdir = FVector((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	int current_set_of_triangles = 0;
	for (long a = 0; a < vertexCount; ++a) {
		FVector n = calculateNormals(readTriangles, current_set_of_triangles);
		FVector t = tan1[a];

		FVector tmp = (t - n * FVector::DotProduct(n, t));
		tmp.Normalize();
		tangents[a] = FVector4(tmp.X, tmp.Y, tmp.Z);


		tangents[a].W= (FVector::DotProduct(FVector::CrossProduct(n, t), tan2[a]) < 0.0f) ? -1.0f : 1.0f; // If it is less than 0 return -1 else return 1
		current_set_of_triangles += 3;
	}

	return tangents;
}*/

/*FVector calculateNormals(TArray<int32> readTriangles, int current_set) {
	FVector First = readTriangles[1] - readTriangles[0];
	FVector Second = readTriangles[2] - readTriangles[0];
	return FVector::CrossProduct(First, Second);


}*/






