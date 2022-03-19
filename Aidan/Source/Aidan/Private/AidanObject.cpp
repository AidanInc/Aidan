// Fill out your copyright notice in the Description page of Project Settings.


#include "AidanObject.h"
// Sets default values
AAidanObject::AAidanObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAidanObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAidanObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

