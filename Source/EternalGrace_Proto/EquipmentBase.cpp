// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentBase.h"
#include "EternalGrace_ProtoCharacter.h"

UEquipmentBase::UEquipmentBase()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UEquipmentBase::GetInteractedWith(AEternalGrace_ProtoCharacter* Interactor)
{
	UE_LOG(LogTemp, Display, TEXT("Use %s"), *GetFName().ToString())
}

FName UEquipmentBase::GetItemName()
{
	return ItemName;
}

EObjectType UEquipmentBase::GetObjectType()
{
	return ObjectType;
}

TSoftObjectPtr<UTexture2D> UEquipmentBase::GetIcon()
{
	return Icon;
}

