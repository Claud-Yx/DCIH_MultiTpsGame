// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "YG/Enum/YGE_InputSystem.h"
#include "YGDAB_InputDefinition.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API UYGDAB_InputDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	class UInputMappingContext* GetImc(EYG_InputMappingContext Name);
	
	UFUNCTION(BlueprintCallable)
	class UInputAction* GetIa(EYG_InputAction Name);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TMap<EYG_InputMappingContext, TObjectPtr<class UInputMappingContext>> IMCs;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<EYG_InputAction, TObjectPtr<class UInputAction>> IAs;
};
