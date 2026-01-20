// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/Weapon/Shotgun.h"

AShotgun::AShotgun()
{
	CurAmmo = 8;
	MaxAmmo = 8;
	Damage = 30.f;
}

void AShotgun::Fire()
{
	Super::Fire();

}
