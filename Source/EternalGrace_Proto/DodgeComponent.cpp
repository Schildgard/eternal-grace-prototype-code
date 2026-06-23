// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeComponent.h"
#include "EternalGrace_ProtoCharacter.h"
#include "EG_AnimInstance.h"
#include "StaminaComponent.h"

UDodgeComponent::UDodgeComponent() :
	DodgeDirection(EDodgeDirection::None),
	DodgeSectionName(FName(TEXT(""))),
	ResetDodgeDirectionTimeRate(0.1f)
{
	PrimaryComponentTick.bCanEverTick = true;
	DodgeMontage = nullptr;
	PlayerCharacter = nullptr;

	DodgeSoundComponent = CreateDefaultSubobject<UAudioComponent>("Dodge Sound");
}

void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AEternalGrace_ProtoCharacter>(GetOwner());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("DodgeComponent Failed to cast character"))
	}

}


void UDodgeComponent::OnDodgeMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	PlayerCharacter->SetCurrentActionState(EActionState::Idle);
	DodgeDirection = EDodgeDirection::None;
}

void UDodgeComponent::OnDodgeMontageBlendedInEnded(UAnimMontage* Montage)
{
	UStaminaComponent* PlayersStaminaComponent = PlayerCharacter->GetStaminaComponent();
	PlayersStaminaComponent->ConsumeStamina(PlayersStaminaComponent->StaminaCostDodge);
		if (DodgeSoundComponent)
		{
			DodgeSoundComponent->Play();
		}
}

void UDodgeComponent::ResetDodgeDirection()
{
}

void UDodgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//todo: Set a Timer that resets the last input

}

void UDodgeComponent::SendMovementVector(FVector2D MovementVector)
{
	SetDodgeDirection(MovementVector);

	GetWorld()->GetTimerManager().SetTimer(ResetDodgeDirectionTimerHandle, this, &UDodgeComponent::ResetDodgeDirection, ResetDodgeDirectionTimeRate);
}

void UDodgeComponent::SetDodgeDirection(FVector2D MovementVector)
{
	if (MovementVector.Y > 0)
	{
		DodgeDirection = EDodgeDirection::Dodge_Forward;
	}
	else if (MovementVector.Y < 0)
	{
		DodgeDirection = EDodgeDirection::Dodge_Backward;
	}
	else if (MovementVector.X < 0)
	{
		DodgeDirection = EDodgeDirection::Dodge_Leftward;
	}
	else if (MovementVector.X > 0)
	{
		DodgeDirection = EDodgeDirection::Dodge_Rightward;
	}
	else
	{
		DodgeDirection = EDodgeDirection::None;
	}
}

void UDodgeComponent::DirectionalDodge(AEternalGrace_ProtoCharacter* Player)
{

	switch (DodgeDirection)
	{
	case EDodgeDirection::Dodge_Forward:
		DodgeSectionName = "Dodge_Forward";
		break;
	case EDodgeDirection::Dodge_Backward:
		DodgeSectionName = "Dodge_Backward";
		break;
	case EDodgeDirection::Dodge_Leftward:
		DodgeSectionName = "Dodge_Leftward";
		break;
	case EDodgeDirection::Dodge_Rightward:
		DodgeSectionName = "Dodge_Rightward";
		break;
	default:
		DodgeSectionName = "Dodge_Backward";
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Dodge Direction is: %s"), *DodgeSectionName.ToString())

		UAnimInstance* AnimationInstance = Player->GetMesh()->GetAnimInstance();
	if (AnimationInstance)
	{
		if (DodgeMontage)
		{
			PlayerCharacter->SetCurrentActionState(EActionState::Dodging);

			PlayerCharacter->EGAnimInstance->bCanContinueAttack = false;
			AnimationInstance->Montage_Play(DodgeMontage);
			AnimationInstance->Montage_JumpToSection(DodgeSectionName);

			OnMontageBlendedInEnded.BindUObject(this, &UDodgeComponent::OnDodgeMontageBlendedInEnded);
			OnMontageBlendingOutStarted.BindUObject(this, &UDodgeComponent::OnDodgeMontageBlendingOut);

			AnimationInstance->Montage_SetBlendedInDelegate(OnMontageBlendedInEnded, DodgeMontage);
			AnimationInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted, DodgeMontage);


		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dodge Component Failed to Get Anim Instance"))
	}

}

void UDodgeComponent::ForwardDodge(AEternalGrace_ProtoCharacter* Player)
{

	if (DodgeDirection == EDodgeDirection::Dodge_Backward || DodgeDirection == EDodgeDirection::None)
	{
		DodgeSectionName = "Dodge_Backward";
	}
	else
	{
		DodgeSectionName = "Dodge_Forward";
	}


	UAnimInstance* AnimationInstance = Player->GetMesh()->GetAnimInstance();
	if (AnimationInstance && DodgeMontage)
	{
		PlayerCharacter->SetCurrentActionState(EActionState::Dodging);
		PlayerCharacter->EGAnimInstance->bCanContinueAttack = false;


		AnimationInstance->Montage_Play(DodgeMontage);
		AnimationInstance->Montage_JumpToSection(DodgeSectionName);

		OnMontageBlendedInEnded.BindUObject(this, &UDodgeComponent::OnDodgeMontageBlendedInEnded);
		OnMontageBlendingOutStarted.BindUObject(this, &UDodgeComponent::OnDodgeMontageBlendingOut);

		AnimationInstance->Montage_SetBlendedInDelegate(OnMontageBlendedInEnded, DodgeMontage);
		AnimationInstance->Montage_SetBlendingOutDelegate(OnMontageBlendingOutStarted, DodgeMontage);

	}
}

