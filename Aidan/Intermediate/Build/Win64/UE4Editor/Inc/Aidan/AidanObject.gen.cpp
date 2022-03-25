// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Aidan/Public/AidanObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAidanObject() {}
// Cross Module References
	AIDAN_API UClass* Z_Construct_UClass_AAidanObject_NoRegister();
	AIDAN_API UClass* Z_Construct_UClass_AAidanObject();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Aidan();
// End Cross Module References
	void AAidanObject::StaticRegisterNativesAAidanObject()
	{
	}
	UClass* Z_Construct_UClass_AAidanObject_NoRegister()
	{
		return AAidanObject::StaticClass();
	}
	struct Z_Construct_UClass_AAidanObject_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAidanObject_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Aidan,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAidanObject_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AidanObject.h" },
		{ "ModuleRelativePath", "Public/AidanObject.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAidanObject_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAidanObject>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAidanObject_Statics::ClassParams = {
		&AAidanObject::StaticClass,
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
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAidanObject_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAidanObject_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAidanObject()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAidanObject_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAidanObject, 1223596055);
	template<> AIDAN_API UClass* StaticClass<AAidanObject>()
	{
		return AAidanObject::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAidanObject(Z_Construct_UClass_AAidanObject, &AAidanObject::StaticClass, TEXT("/Script/Aidan"), TEXT("AAidanObject"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAidanObject);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
