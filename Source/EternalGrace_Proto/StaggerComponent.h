// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackDirection.h"
#include "StaggerComponent.generated.h"

class UVoiceComponent;
class UCharacterAnimInstanceBase;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ETERNALGRACE_PROTO_API UStaggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaggerComponent();

	UFUNCTION()
	void GetStaggered(bool bIsBlocking, EAttackDirection Direction);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseValues, meta = (AllowPrivateAccess))
	float MaxPoise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stagger, meta = (AllowPrivateAccess))
	TArray<UAnimMontage*> StaggerAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stagger, meta = (AllowPrivateAccess))
	UAnimMontage* BlockStaggerAnimation;

	UPROPERTY()
	UCharacterAnimInstanceBase* CharacterAnimInstance;

	UVoiceComponent* CharacterVoiceComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseValues, meta = (AllowPrivateAccess))
	float CurrentPoise;

	UFUNCTION()
	void PlayStaggerSound(UAnimMontage* Montage);

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
