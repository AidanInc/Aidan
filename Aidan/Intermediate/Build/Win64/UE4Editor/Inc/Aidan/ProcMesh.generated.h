// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AIDAN_ProcMesh_generated_h
#error "ProcMesh.generated.h already included, missing '#pragma once' in ProcMesh.h"
#endif
#define AIDAN_ProcMesh_generated_h

#define Aidan_Source_Aidan_Public_ProcMesh_h_13_SPARSE_DATA
#define Aidan_Source_Aidan_Public_ProcMesh_h_13_RPC_WRAPPERS
#define Aidan_Source_Aidan_Public_ProcMesh_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define Aidan_Source_Aidan_Public_ProcMesh_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProcMesh(); \
	friend struct Z_Construct_UClass_AProcMesh_Statics; \
public: \
	DECLARE_CLASS(AProcMesh, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Aidan"), NO_API) \
	DECLARE_SERIALIZER(AProcMesh)


#define Aidan_Source_Aidan_Public_ProcMesh_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAProcMesh(); \
	friend struct Z_Construct_UClass_AProcMesh_Statics; \
public: \
	DECLARE_CLASS(AProcMesh, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Aidan"), NO_API) \
	DECLARE_SERIALIZER(AProcMesh)


#define Aidan_Source_Aidan_Public_ProcMesh_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProcMesh(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProcMesh) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProcMesh); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProcMesh); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProcMesh(AProcMesh&&); \
	NO_API AProcMesh(const AProcMesh&); \
public:


#define Aidan_Source_Aidan_Public_ProcMesh_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProcMesh(AProcMesh&&); \
	NO_API AProcMesh(const AProcMesh&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProcMesh); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProcMesh); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProcMesh)


#define Aidan_Source_Aidan_Public_ProcMesh_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ProcMesh() { return STRUCT_OFFSET(AProcMesh, ProcMesh); } \
	FORCEINLINE static uint32 __PPO__Material() { return STRUCT_OFFSET(AProcMesh, Material); }


#define Aidan_Source_Aidan_Public_ProcMesh_h_10_PROLOG
#define Aidan_Source_Aidan_Public_ProcMesh_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_PRIVATE_PROPERTY_OFFSET \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_SPARSE_DATA \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_RPC_WRAPPERS \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_INCLASS \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Aidan_Source_Aidan_Public_ProcMesh_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_PRIVATE_PROPERTY_OFFSET \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_SPARSE_DATA \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_INCLASS_NO_PURE_DECLS \
	Aidan_Source_Aidan_Public_ProcMesh_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AIDAN_API UClass* StaticClass<class AProcMesh>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Aidan_Source_Aidan_Public_ProcMesh_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
