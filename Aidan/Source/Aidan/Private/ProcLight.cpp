// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcLight.h"

// Sets default values
AProcLight::AProcLight()
{

	procLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("light")); // Creating a Point Light object

	RootComponent = procLight;

}

// Called when the game starts or when spawned
void AProcLight::BeginPlay()
{
	Super::BeginPlay();
}
void AProcLight::buildLight(FVector lightPosition, FLinearColor genlightColor, float lightIntensity) {
	//Test parameters
	/*lightColor.R = 0;
	lightColor.B = 1;
	lightColor.G = 0;
	lightColor.A = 1;

	intensity = 1000000.0f;
	position.X = -250.0;
	position.Y = -250.0;
	position.Z = 400.0;


	*/
	//Setting the attributes of the light
	procLight->SetIntensity(lightIntensity);
	procLight->SetLightColor(genlightColor);
	procLight->SetWorldLocation(lightPosition);
	procLight->SetVisibility(true);
}


