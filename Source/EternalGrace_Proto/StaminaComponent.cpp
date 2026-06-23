// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaComponent.h"
#include "ValueBarWidgetBase.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StaminaBarClass = nullptr;
	StaminaBar = nullptr;
	MaxStamina = 100.f;
	CurrentStamina = MaxStamina;
	StaminaRegenRate = 15.0f;
	MaxExhaustionTime = 3.0f;
	RemainingExhaustionTime = MaxExhaustionTime;
	StaminaCostSprint = 5.f;
	StaminaCostDodge = 20.f;
	StaminaCostAttack = 20.f;
	StaminaCostBlock = 20.f;
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<AEternalGrace_ProtoCharacter>(GetOwner());
	if (!OwningCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("(Stamina Component) failed to cast Player Character"))
			return;
	}

}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentStamina < MaxStamina)
	{
		if (OwningCharacter->GetCurrentActionState() == EActionState::Idle)
		{
			RegStamina(DeltaTime);
		}
		else if (OwningCharacter->GetCurrentActionState() == EActionState::Guarding)
		{
			RegStamina(DeltaTime / 3);
		}
		UpdateStaminaBar();
	}
	if (CurrentStamina <= 0)
	{
		if(OwningCharacter->GetCurrentActionState() == EActionState::Running)
		{
			OwningCharacter->CancelSprint();
		}
		OwningCharacter->SetCurrentActionState(EActionState::Exhausted);
	}
	if (OwningCharacter->GetCurrentActionState() == EActionState::Exhausted)
	{
		CountdownExhaustion(DeltaTime);
	}
	if (OwningCharacter->GetCurrentActionState() == EActionState::Running)
	{
		if (OwningCharacter->GetVelocity().Size() < 90.f)
		{
			OwningCharacter->CancelSprint();
		}
		else
		{
			CurrentStamina -= (StaminaCostSprint * DeltaTime);
		}
	}
}

void UStaminaComponent::UpdateStaminaBar()
{
	if (StaminaBar)
	{
		StaminaBar->UpdateProgressBar(CurrentStamina, MaxStamina);
	}
}

float UStaminaComponent::GetMaxStamina()
{
	return MaxStamina;
}

void UStaminaComponent::RegStamina(float DeltaTime)
{
	CurrentStamina += StaminaRegenRate * DeltaTime;
}

void UStaminaComponent::CountdownExhaustion(float DeltaTime)
{
	RemainingExhaustionTime -= DeltaTime;
	if (RemainingExhaustionTime <= 0)
	{
		OwningCharacter->SetCurrentActionState(EActionState::Idle);
		RemainingExhaustionTime = MaxExhaustionTime;
	}
}

void UStaminaComponent::ConsumeStamina(float StaminaConsumptionAmount)
{
	CurrentStamina -= StaminaConsumptionAmount;
	if(CurrentStamina <= 0)
	{
		CurrentStamina = 0.0f;
	}
}

void UStaminaComponent::ShowStaminaBar(APlayerController* PlayerController)
{
	if (StaminaBarClass)
	{
		if (!StaminaBar)
		{
			StaminaBar = CreateWidget<UValueBarWidgetBase>(PlayerController, StaminaBarClass);
		}
		if (!StaminaBar->IsInViewport())
		{
			StaminaBar->AddToPlayerScreen();
		}

	}
}

