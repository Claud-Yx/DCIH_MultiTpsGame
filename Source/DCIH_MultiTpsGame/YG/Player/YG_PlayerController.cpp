// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YG_PlayerController.h"

#include "YG/Component/YGC_InputSystemManager.h"


AYG_PlayerController::AYG_PlayerController()
	:Super()
{
	InputSystemManager = CreateDefaultSubobject<UYGC_InputSystemManager>(TEXT("InputSystemManager"));
}
