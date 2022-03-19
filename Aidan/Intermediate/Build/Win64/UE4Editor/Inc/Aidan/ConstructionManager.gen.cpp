// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Aidan/Private/ConstructionManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeConstructionManager() {}
// Cross Module References
	AIDAN_API UClass* Z_Construct_UClass_AConstructionManager_NoRegister();
	AIDAN_API UClass* Z_Construct_UClass_AConstructionManager();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Aidan();
// End Cross Module References
	void AConstructionManager::StaticRegisterNativesAConstructionManager()
	{
	}
	UClass* Z_Construct_UClass_AConstructionManager_NoRegister()
	{
		return AConstructionManager::StaticClass();
	}
	struct Z_Construct_UClass_AConstructionManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AConstructionManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Aidan,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AConstructionManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ConstructionManager.h" },
		{ "ModuleRelativePath", "Private/ConstructionManager.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AConstructionManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AConstructionManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AConstructionManager_Statics::ClassParams = {
		&AConstructionManager::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AConstructionManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AConstructionManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AConstructionManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AConstructionManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AConstructionManager, 1463850788);
	template<> AIDAN_API UClass* StaticClass<AConstructionManager>()
	{
		return AConstructionManager::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AConstructionManager(Z_Construct_UClass_AConstructionManager, &AConstructionManager::StaticClass, TEXT("/Script/Aidan"), TEXT("AConstructionManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AConstructionManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
