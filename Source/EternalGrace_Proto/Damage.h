// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackDirection.h"
#include "Damage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDamage : public  FTableRowBase
{
	GENERATED_BODY()

public:
	FDamage() :DamageValue(0.0f), PoiseDamageValue(0.0f),DamageDirection(EAttackDirection::Front),HitLocation(0.0f),HitRotation(0.0f), Attacker(nullptr){};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float DamageValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	float PoiseDamageValue;

	EAttackDirection DamageDirection;
	FVector HitLocation;
	FRotator HitRotation;
	AActor* Attacker;
};
