// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldComponent.h"
#include "ShieldBase.h"
#include "CharacterBase.h"
#include "NiagaraSystem.h"


UShieldComponent::UShieldComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Balance = 0.f;
	BlockValue = 50.0f;

	BlockEffect = nullptr;
	BlockSound = nullptr;
	CurrentShieldObject = nullptr;
	OwningCharacter = nullptr;
	ShieldBashAttack = nullptr;
}


void UShieldComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<ACharacterBase>(GetOwner());
	if (!OwningCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Cast Owning Character (ShieldComponent"));
	}
}


void UShieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UShieldComponent::EquipShield(TSubclassOf<AShieldBase> ShieldToEquip)
{
	UE_LOG(LogTemp, Error, TEXT("Equip Shield (ShieldComponent)"));
	if (CurrentShieldObject)
	{
		CurrentShieldObject->Destroy();
		CurrentShieldObject = nullptr;
		BlockValue = 0.0f;
		Balance = 0.0f;
	}
	CurrentShieldClass = ShieldToEquip;
	CurrentShieldObject = GetWorld()->SpawnActor<AShieldBase>(CurrentShieldClass);
	if (!CurrentShieldObject)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Spawn Shield Object (ShieldComponent"));
		return;
	}
	CurrentShieldObject->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "s_hand_l");
	BlockValue = CurrentShieldObject->BlockValue;
	Balance = CurrentShieldObject->Balance;
	//BlockAnimations = 
	UE_LOG(LogTemp, Error, TEXT("Set Shield Values (ShieldComponent) BlockValue: %f, Balance: %f"), BlockValue, Balance);
}

USoundBase* UShieldComponent::GetBlockSound()
{
	return BlockSound;
}

UNiagaraSystem* UShieldComponent::GetBlockEffect()
{
	return BlockEffect;
}

UAnimMontage* UShieldComponent::GetNormalBlockAnimation()
{
	if (BlockAnimations.Num() >= 1)
	{
		return BlockAnimations[0];
	}

	return nullptr;
}

TSubclassOf<AShieldBase> UShieldComponent::GetCurrentShieldClass()
{
	return CurrentShieldClass;
}

AShieldBase* UShieldComponent::GetCurrentShieldObject()
{
	return CurrentShieldObject;
}

UAnimMontage* UShieldComponent::GetShieldAttack()
{
	return ShieldBashAttack;
}

void UShieldComponent::Unequip()
{
	if (CurrentShieldObject)
	{
		CurrentShieldObject->Destroy();
	}
	CurrentShieldClass = nullptr;
	CurrentShieldObject = nullptr;

	BlockValue = 50.f;
	Balance = 0.0f;
}

