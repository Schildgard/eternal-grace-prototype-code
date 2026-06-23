// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Saveable.h"
#include "GameFramework/Character.h"
#include "ActionState.h"
#include "Attackable.h"
#include "Damageable.h"
#include "AttackDirection.h"
#include "Staggerable.h"
#include "Damage.h"
#include "CharacterBase.generated.h"

class AWeaponBase;
class UCapsuleComponent;
class UEternalGrace_SaveGame;
class UEternalGrace_GameInstance;
class UHealthComponent;
class UStaggerComponent;
class UShieldComponent;
class UVoiceComponent;
UCLASS()
class ETERNALGRACE_PROTO_API ACharacterBase : public ACharacter, public ISaveable, public IAttackable, public IDamageable
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UWorld* World;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UDataTable* GroundSurfaceDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(AllowPrivateAccess))
	USkeletalMeshComponent* HeadMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	USkeletalMeshComponent* Hair;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	USkeletalMeshComponent* LowerBody;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	USkeletalMeshComponent* Hands;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	USkeletalMeshComponent* Feet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaggerComponent* StaggerComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UVoiceComponent* CharacterVoiceComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	UShieldComponent* ShieldComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess))
	FName ObjectID;

	//Save Interface Implementations
	UFUNCTION(CallInEditor, Category = "SaveGame")
	virtual void SaveData_Implementation()override;
	UFUNCTION(CallInEditor, Category = "SaveGame")
	virtual void LoadData_Implementation()override;
	UFUNCTION(CallInEditor, Category = "SaveGame")
	void MakeSaveCall();
	UFUNCTION(CallInEditor, Category = "SaveGame")
	void MakeLoadCall();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess))
	TArray<TEnumAsByte<EObjectTypeQuery>> HittableObjectTypes;

	//Attackable Interface Implementations
	UFUNCTION()
	virtual UCapsuleComponent* GetHitBox_Implementation()override;
	UFUNCTION()
	virtual TArray<TEnumAsByte<EObjectTypeQuery>> GetHittableObjectTypes_Implementation() override;
	UFUNCTION()
	virtual AWeaponBase* GetWeapon_Implementation()override;
	UFUNCTION()
	virtual AWeaponBase* GetOffhandWeapon_Implementation()override;
	UFUNCTION()
	virtual AShieldBase* GetShield_Implementation()override;
	UFUNCTION()
	virtual void Attack_Implementation()override;

	//Damageable Interface Implementations
	UFUNCTION()
	virtual void GetDamage_Implementation(FDamage DamageContainer)override;

	void PlayBlockingVoice(UAnimMontage* Montage);
	UFUNCTION()
	UNiagaraSystem* GetHitEffectSystem_Implementation()override;
	UFUNCTION()
	UAudioComponent* GetHitSoundComponent_Implementation()override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta =(AllowPrivateAccess))
	float TimeStopDuration;

public:

	UPROPERTY()
	bool bIsAlive;
	UFUNCTION()
	virtual void Die_Implementation()override;
protected:



	UPROPERTY()
	UEternalGrace_GameInstance* CurrentGameInstance;
	UPROPERTY()
	UEternalGrace_SaveGame* SaveGameObject;

	UPROPERTY()
	EActionState CurrentActionState;


public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	EActionState GetCurrentActionState();

	UFUNCTION()
	virtual void CancelGuard();

	UFUNCTION(BlueprintCallable)
	virtual void SetCurrentActionState(EActionState ActionState);

	//FootSteps
	UFUNCTION(BlueprintCallable)
	virtual void PlayFootStepSound(FName FootSocket);
	UFUNCTION()
	UPhysicalMaterial* GetGroundMaterial();
	const float GroundScanDistance = 150.0f;

	UFUNCTION()
	void RotateTowardsTarget(AActor* Target);

	UFUNCTION()
	UHealthComponent* GetHealthComponent();

	UFUNCTION()
	void UnequipShield();

	UFUNCTION()
	void StartHitStop();

	UFUNCTION()
	void StopHitStop();

	UVoiceComponent* GetVoiceComponent();

	UFUNCTION()
	virtual void GetStaggered(bool bIsBlocking, EAttackDirection Direction);

	UFUNCTION()
	virtual void BlockDamage(FDamage DamageContainer);

};
