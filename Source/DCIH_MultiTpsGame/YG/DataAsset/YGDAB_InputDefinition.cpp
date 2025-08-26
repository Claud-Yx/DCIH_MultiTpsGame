// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/DataAsset/YGDAB_InputDefinition.h"


class UInputMappingContext* UYGDAB_InputDefinition::GetImc(EYG_InputMappingContext Name)
{
	return IMCs[Name];
}

class UInputAction* UYGDAB_InputDefinition::GetIa(EYG_InputAction Name)
{
	return IAs[Name];
}
