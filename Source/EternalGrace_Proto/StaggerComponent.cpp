// Fill out your copyright notice in the Description page of Project Settings.


#include "StaggerComponent.h"
#include "CharacterAnimInstanceBase.h"
#include "CharacterBase.h"
#include "VoiceComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UStaggerComponent::UStaggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxPoise = 100.0f;
	CurrentPoise = MaxPoise;
	CharacterVoiceComponent = nullptr;
	CharacterAnimInstance = nullptr;
}

void UStaggerComponent::GetStaggered(bool bIsBlocking, EAttackDirection Direction)
{
	UAnimMontage* StaggerAnimation;

	if(!bIsBlocking)
	{
		int StaggerAnimationIndex = 0;
		switch (Direction)
		{
		case EAttackDirection::Front:
				StaggerAnimationIndex = 0;
			break;
		case EAttackDirection::Back:
				StaggerAnimationIndex = 1;
				break;
		case EAttackDirection::Right:
				StaggerAnimationIndex = 2;;
			break;
		case EAttackDirection::Left:
				StaggerAnimationIndex = 3;
			break;
		}
		StaggerAnimation = StaggerAnimations[StaggerAnimationIndex];
		UE_LOG(LogTemp, Warning, TEXT("Choose Regular Stagger (StaggerComponent)"))

	}

	else
	{
		StaggerAnimation = BlockStaggerAnimation;
		UE_LOG(LogTemp, Warning, TEXT("Choose Block Stagger (StaggerComponent)"))
	}


		CharacterAnimInstance->Montage_Play(StaggerAnimation);
		CurrentPoise = MaxPoise;

		FOnMontageBlendedInEnded BlendInDelegate;
		BlendInDelegate.BindUObject(this, &UStaggerComponent::PlayStaggerSound);
		CharacterAnimInstance->Montage_SetBlendedInDelegate(BlendInDelegate, StaggerAnimation);

		FOnMontageBlendingOutStarted BlendOutDelegate;
		BlendOutDelegate.BindUObject(CharacterAnimInstance, &UCharacterAnimInstanceBase::ResetCharacterState);
		CharacterAnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, StaggerAnimation);
}


// Called when the game starts
void UStaggerComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	if(Character)
	{
		CharacterAnimInstance = Cast<UCharacterAnimInstanceBase>(Character->GetMesh()->GetAnimInstance());
		CharacterVoiceComponent = Character->GetVoiceComponent();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Failed to get Character (StaggerComponent)"), *GetOwner()->GetFName().ToString())
	}
	
}

void UStaggerComponent::PlayStaggerSound(UAnimMontage* Montage)
{
	UE_LOG(LogTemp, Display, TEXT("Enter PlayStaggerSound Function (Stagger Component"))

		FString StaggerSoundName = FMath::RandBool() ? "Pain01" : "Pain02";
		if(CharacterVoiceComponent)
		{
			CharacterVoiceComponent->PlayVoiceSound(StaggerSoundName);
		}

}


// Called every frame
//void UStaggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

