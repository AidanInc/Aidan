// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Aidan/Public/Test.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTest() {}
// Cross Module References
	AIDAN_API UClass* Z_Construct_UClass_UTest_NoRegister();
	AIDAN_API UClass* Z_Construct_UClass_UTest();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_Aidan();
// End Cross Module References
	void UTest::StaticRegisterNativesUTest()
	{
	}
	UClass* Z_Construct_UClass_UTest_NoRegister()
	{
		return UTest::StaticClass();
	}
	struct Z_Construct_UClass_UTest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Aidan,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTest_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Test.h" },
		{ "ModuleRelativePath", "Public/Test.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTest>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UTest_Statics::ClassParams = {
		&UTest::StaticClass,
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
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UTest_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTest_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTest()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UTest_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UTest, 363467384);
	template<> AIDAN_API UClass* StaticClass<UTest>()
	{
		return UTest::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UTest(Z_Construct_UClass_UTest, &UTest::StaticClass, TEXT("/Script/Aidan"), TEXT("UTest"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTest);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
