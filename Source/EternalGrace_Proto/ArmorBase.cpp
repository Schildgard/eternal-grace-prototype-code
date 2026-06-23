// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorBase.h"

AArmorBase::AArmorBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AArmorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArmorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArmorBase::GetInteractedWith(AEternalGrace_ProtoCharacter* Interactor)
{
	UE_LOG(LogTemp, Display, TEXT("hoops %s"), *GetFName().ToString())
}
FName AArmorBase::GetItemName()
{
	return ItemName;
}
EObjectType AArmorBase::GetObjectType()
{
	return ObjectType;
}

TSoftObjectPtr<UTexture2D> AArmorBase::GetIcon()
{
	return Icon;
}

