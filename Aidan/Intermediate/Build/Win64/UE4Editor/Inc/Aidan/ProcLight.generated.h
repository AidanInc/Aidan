// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector4;
struct FVector;
#ifdef AIDAN_ProcLight_generated_h
#error "ProcLight.generated.h already included, missing '#pragma once' in ProcLight.h"
#endif
#define AIDAN_ProcLight_generated_h

#define Aidan_Source_Aidan_Public_ProcLight_h_13_SPARSE_DATA
#define Aidan_Source_Aidan_Public_ProcLight_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execbuildLight);


#define Aidan_Source_Aidan_Public_ProcLight_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execbuildLight);


#define Aidan_Source_Aidan_Public_ProcLight_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAProcLight(); \
	friend struct Z_Construct_UClass_AProcLight_Statics; \
public: \
	DECLARE_CLASS(AProcLight, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Aidan"), NO_API) \
	DECLARE_SERIALIZER(AProcLight)


#define Aidan_Source_Aidan_Public_ProcLight_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAProcLight(); \
	friend struct Z_Construct_UClass_AProcLight_Statics; \
public: \
	DECLARE_CLASS(AProcLight, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Aidan"), NO_API) \
	DECLARE_SERIALIZER(AProcLight)


#define Aidan_Source_Aidan_Public_ProcLight_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AProcLight(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AProcLight) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProcLight); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProcLight); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProcLight(AProcLight&&); \
	NO_API AProcLight(const AProcLight&); \
public:


#define Aidan_Source_Aidan_Public_ProcLight_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AProcLight(AProcLight&&); \
	NO_API AProcLight(const AProcLight&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AProcLight); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AProcLight); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AProcLight)


#define Aidan_Source_Aidan_Public_ProcLight_h_13_PRIVATE_PROPERTY_OFFSET
#define Aidan_Source_Aidan_Public_ProcLight_h_10_PROLOG
#define Aidan_Source_Aidan_Public_ProcLight_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Aidan_Source_Aidan_Public_ProcLight_h_13_PRIVATE_PROPERTY_OFFSET \
	Aidan_Source_Aidan_Public_ProcLight_h_13_SPARSE_DATA \
	Aidan_Source_Aidan_Public_ProcLight_h_13_RPC_WRAPPERS \
	Aidan_Source_Aidan_Public_ProcLight_h_13_INCLASS \
	Aidan_Source_Aidan_Public_ProcLight_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Aidan_Source_Aidan_Public_ProcLight_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Aidan_Source_Aidan_Public_ProcLight_h_13_PRIVATE_PROPERTY_OFFSET \
	Aidan_Source_Aidan_Public_ProcLight_h_13_SPARSE_DATA \
	Aidan_Source_Aidan_Public_ProcLight_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Aidan_Source_Aidan_Public_ProcLight_h_13_INCLASS_NO_PURE_DECLS \
	Aidan_Source_Aidan_Public_ProcLight_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AIDAN_API UClass* StaticClass<class AProcLight>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Aidan_Source_Aidan_Public_ProcLight_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
