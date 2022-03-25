// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Aidan/Public/ProcLight.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProcLight() {}
// Cross Module References
	AIDAN_API UClass* Z_Construct_UClass_AProcLight_NoRegister();
	AIDAN_API UClass* Z_Construct_UClass_AProcLight();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Aidan();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	ENGINE_API UClass* Z_Construct_UClass_UPointLightComponent_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AProcLight::execbuildLight)
	{
		P_GET_STRUCT(FVector,Z_Param_lightPosition);
		P_GET_STRUCT(FLinearColor,Z_Param_genLightColor);
		P_GET_PROPERTY(FFloatProperty,Z_Param_lightIntensity);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->buildLight(Z_Param_lightPosition,Z_Param_genLightColor,Z_Param_lightIntensity);
		P_NATIVE_END;
	}
	void AProcLight::StaticRegisterNativesAProcLight()
	{
		UClass* Class = AProcLight::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "buildLight", &AProcLight::execbuildLight },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AProcLight_buildLight_Statics
	{
		struct ProcLight_eventbuildLight_Parms
		{
			FVector lightPosition;
			FLinearColor genLightColor;
			float lightIntensity;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_lightPosition;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_genLightColor;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_lightIntensity;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_lightPosition = { "lightPosition", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ProcLight_eventbuildLight_Parms, lightPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_genLightColor = { "genLightColor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ProcLight_eventbuildLight_Parms, genLightColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_lightIntensity = { "lightIntensity", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ProcLight_eventbuildLight_Parms, lightIntensity), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AProcLight_buildLight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_lightPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_genLightColor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AProcLight_buildLight_Statics::NewProp_lightIntensity,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AProcLight_buildLight_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AProcLight_buildLight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AProcLight, nullptr, "buildLight", nullptr, nullptr, sizeof(ProcLight_eventbuildLight_Parms), Z_Construct_UFunction_AProcLight_buildLight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AProcLight_buildLight_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AProcLight_buildLight_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AProcLight_buildLight_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AProcLight_buildLight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AProcLight_buildLight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AProcLight_NoRegister()
	{
		return AProcLight::StaticClass();
	}
	struct Z_Construct_UClass_AProcLight_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_procLight_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_procLight;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_lightColor_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_lightColor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_intensity_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_intensity;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_position;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProcLight_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Aidan,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AProcLight_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AProcLight_buildLight, "buildLight" }, // 738959776
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProcLight_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ProcLight.h" },
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProcLight_Statics::NewProp_procLight_MetaData[] = {
		{ "Category", "ProcLight" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AProcLight_Statics::NewProp_procLight = { "procLight", nullptr, (EPropertyFlags)0x00100000000a001d, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AProcLight, procLight), Z_Construct_UClass_UPointLightComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AProcLight_Statics::NewProp_procLight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::NewProp_procLight_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProcLight_Statics::NewProp_lightColor_MetaData[] = {
		{ "Category", "ProcLight" },
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProcLight_Statics::NewProp_lightColor = { "lightColor", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AProcLight, lightColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(Z_Construct_UClass_AProcLight_Statics::NewProp_lightColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::NewProp_lightColor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProcLight_Statics::NewProp_intensity_MetaData[] = {
		{ "Category", "ProcLight" },
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AProcLight_Statics::NewProp_intensity = { "intensity", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AProcLight, intensity), METADATA_PARAMS(Z_Construct_UClass_AProcLight_Statics::NewProp_intensity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::NewProp_intensity_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProcLight_Statics::NewProp_position_MetaData[] = {
		{ "Category", "ProcLight" },
		{ "ModuleRelativePath", "Public/ProcLight.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AProcLight_Statics::NewProp_position = { "position", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AProcLight, position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_AProcLight_Statics::NewProp_position_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::NewProp_position_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AProcLight_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProcLight_Statics::NewProp_procLight,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProcLight_Statics::NewProp_lightColor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProcLight_Statics::NewProp_intensity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AProcLight_Statics::NewProp_position,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProcLight_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProcLight>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AProcLight_Statics::ClassParams = {
		&AProcLight::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AProcLight_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AProcLight_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProcLight_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProcLight()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AProcLight_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AProcLight, 694090421);
	template<> AIDAN_API UClass* StaticClass<AProcLight>()
	{
		return AProcLight::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AProcLight(Z_Construct_UClass_AProcLight, &AProcLight::StaticClass, TEXT("/Script/Aidan"), TEXT("AProcLight"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProcLight);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
