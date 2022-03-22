// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "ProcLight.generated.h"

UCLASS()
class AIDAN_API AProcLight : public AActor
{
	GENERATED_BODY()
	
	
	
	
	
public:	
	// Sets default values for this actor's properties
	AProcLight();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UPointLightComponent* procLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor lightColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float intensity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector position;

	UFUNCTION()
		void buildLight(FVector lightPosition,FLinearColor genLightColor, float lightIntensity);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
