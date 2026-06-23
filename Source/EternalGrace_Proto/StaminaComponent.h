// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionState.h"
#include "EternalGrace_ProtoCharacter.h"
#include "StaminaComponent.generated.h"

class UValueBarWidgetBase;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALGRACE_PROTO_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStaminaComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AEternalGrace_ProtoCharacter* OwningCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina", meta = (AllowPrivateAccess))
	TSubclassOf<UValueBarWidgetBase> StaminaBarClass;
	UPROPERTY()
	UValueBarWidgetBase* StaminaBar;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float MaxExhaustionTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	USoundBase* HeavyBreathingSound;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY()
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float StaminaRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float RemainingExhaustionTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaminaConsumption, meta = (AllowPrivateAccess))
	float StaminaCostSprint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaminaConsumption, meta = (AllowPrivateAccess))
	float StaminaCostDodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaminaConsumption, meta = (AllowPrivateAccess))
	float StaminaCostBlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaminaConsumption, meta = (AllowPrivateAccess))
	float StaminaCostAttack;


	UFUNCTION()
	void UpdateStaminaBar();

	UFUNCTION()
	float GetMaxStamina();

	UFUNCTION()
	void RegStamina(float DeltaTime);

	UFUNCTION()
	void CountdownExhaustion(float DeltaTime);

	UFUNCTION()
	void ConsumeStamina(float StaminaConsumptionAmount);

	UFUNCTION()
	void ShowStaminaBar(APlayerController* PlayerController);

		
};
