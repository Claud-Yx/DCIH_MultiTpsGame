// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/MT_PlayerController.h"
#include "YG_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API AYG_PlayerController : public AMT_PlayerController
{
	GENERATED_BODY()
public:
	AYG_PlayerController();

protected:
	// Manager
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UYGC_InputSystemManager> InputSystemManager;
};
