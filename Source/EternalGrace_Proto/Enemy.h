// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBase.h"
#include "Staggerable.h"
#include "AttackDirection.h"
#include "Enemy.generated.h"

/**
 * 
 */
class UValueBarWidgetBase;
class UWidgetComponent;
class UDespawningValueBarWidget;
UCLASS()
class ETERNALGRACE_PROTO_API AEnemy : public ANPCBase, public IStaggerable
{
	GENERATED_BODY()

protected:
	AEnemy();


	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void NoticePlayer(APawn* SpottedPawn)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess))
	USoundBase* NoticePlayerSound;

	virtual AWeaponBase* GetWeapon_Implementation()override;
	virtual void Stagger_Implementation(EAttackDirection Direction, float PoiseDamage, AActor* DamageInstigator)override;
	virtual void GetDamage_Implementation(FDamage DamageContainer)override;


	//This pointers are used to project the HPBar of the Enemy to both players independently
	UPROPERTY()
	UDespawningValueBarWidget* TemporaryHPBarInstance1;

	UPROPERTY()
	UDespawningValueBarWidget* TemporaryHPBarInstance2;

	UFUNCTION()
	UDespawningValueBarWidget* ShowTemporaryBar(int PlayerIndex);

	UFUNCTION()
	void UpdateTemporaryHPBarValues();

	UFUNCTION()
	void UpdateHealthbarPosition();

public:
	static int ObjectIDCounter;
};
