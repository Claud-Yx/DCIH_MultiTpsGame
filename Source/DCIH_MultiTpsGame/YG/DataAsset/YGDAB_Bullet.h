// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YGDAB_Bullet.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API UYGDAB_Bullet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly )
	float Damage;
	
	
};
