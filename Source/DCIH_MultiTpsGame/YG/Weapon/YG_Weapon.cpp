// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Weapon/YG_Weapon.h"


// Sets default values
AYG_Weapon::AYG_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYG_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYG_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

