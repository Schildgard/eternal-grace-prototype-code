// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CharacterBase.h"
#include "PlayerSaveData.h"
#include "Playable.h"
#include "Staggerable.h"
#include "ObjectType.h"
#include "WeaponType.h"
#include "InputType.h"
#include "EternalGrace_ProtoCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UArmorComponent;
class UInventoryComponent;
class UWeaponComponent;
class AWeaponBase;
class UEquipmentArmor;
class UEG_AnimInstance;
class UInputBufferComponent;
class ULockOnComponent;
class UStaggerComponent;
class UDodgeComponent;
class UStaminaComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AEternalGrace_ProtoCharacter : public ACharacterBase, public IPlayable, public IStaggerable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClimbAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HoldOnLedgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NormalAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NormalOffhandAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LockOnAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchTargetAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta =(AllowPrivateAccess))
	UWeaponComponent* WeaponComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UInputBufferComponent* InputBufferingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	ULockOnComponent* LockOnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStaminaComponent* StaminaComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UDodgeComponent* DodgeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* BodyArmorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* LowerBodyArmorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* FootArmorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* HandsArmorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* HeadArmorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Equipment, meta = (AllowPrivateAccess = "true"))
	UEquipmentArmor* BackArmorComponent;


public:
	AEternalGrace_ProtoCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UEG_AnimInstance* EGAnimInstance;
	

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Saveable Implementations
	virtual void SaveData_Implementation()override;
	virtual void LoadData_Implementation()override;
	//Playable Implementations
	virtual void Interact_Implementation()override;
	virtual void ShowInteractUI_Implementation(AActor* ActorToInteractWith)override;
	virtual void HideInteractUI_Implementation()override;
	//Attackable Implementations
	virtual UCapsuleComponent* GetHitBox_Implementation()override;
	virtual AWeaponBase* GetWeapon_Implementation()override;
	virtual AWeaponBase* GetOffhandWeapon_Implementation()override;
	//Damageable Implementations
	virtual void Die_Implementation()override;
	//Stagerable Implementation
	virtual void Stagger_Implementation(EAttackDirection Direction, float PoiseDamage, AActor* DamageInstigator)override;
	//FootStep Sound
	virtual void PlayFootStepSound(FName FootSocket)override;


	void CancelGuard()override;
	void Jump()override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer", meta = (AllowPrivateAccess))
	int32 PlayerIndex;

	UPROPERTY()
	FPlayerSaveData SaveDataInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess))
	UArmorComponent* ArmorComponent;


	UFUNCTION()
	void ShowInventory();

	UFUNCTION()
	void NormalAttack();
	void PerformNormalAttack(UAnimMontage* CurrentAttack);
	void PlayAttackVoiceSound(UAnimMontage* Montage);
	UFUNCTION()
	void PerformDodgeAttack();
	UFUNCTION()
	void PerformOffhandAction();
	UFUNCTION()
	void TriggerCurrentInteractable();

	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void Dodge(const FInputActionValue& Value);

	UFUNCTION()
	void LockOn();
	UFUNCTION()
	void SwitchTarget(const FInputActionValue& Value);

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess))
	UInventoryComponent* PlayerInventory;
	


protected:
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaSeconds)override;
	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BlockDamage(FDamage DamageContainer)override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void Equip(FName ArmorID);

	UFUNCTION()
	void CancelSprint();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta =(AllowPrivateAccess))
	float ZoomMultiplier;
	UFUNCTION()
	void Zoom(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	UArmorComponent* GetArmorComponent();

	UFUNCTION()
	UInventoryComponent* GetInventory();

	UFUNCTION()
	void ObtainArmor(FName ArmorName, EObjectType ItemCategory);

	//While Object ID is an Identifier for the Save Game, the PlayerIndex holds track to wether its Player 1 or 2
	UFUNCTION()
	void SetPlayerIndex(int AssigendPlayerIndex);
	UFUNCTION()
	int GetPlayerIndex();

	UFUNCTION()
	void EquipWeapon(TSubclassOf<AWeaponBase> WeaponToEquip);

	UFUNCTION()
	void EquipOffhandWeapon(TSubclassOf<AWeaponBase> WeaponToEquip);

	UFUNCTION(BlueprintCallable)
	void FireBufferedInput(EInputType BufferedInput);

	UFUNCTION()
	UInputBufferComponent* GetInputBufferComponent();
	UFUNCTION()
	void SetLockOn(bool Value);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess))
	float ScanDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess))
	float CapsuleHeightOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess))
	float WallDistanceOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Movement", meta = (AllowPrivateAccess))
	UAnimMontage* ClimpAnimation;
	UPROPERTY()
	bool bIsCurrentlyClimbingUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess))
	USoundBase* AttachToWallSound;
	UFUNCTION()
	void ClimpCheckForward();
	UFUNCTION()
	void ClimpCheckUpward(FVector HitLocation, FVector HitNormal);
	UPROPERTY()
	TArray<AActor*> ClimpActorsToIgnore;
	UFUNCTION()
	void HangOnLedge(FVector SnappingPosition, FVector WallNormal, FVector HeightLocation);

	UFUNCTION()
	void Climb();
	UFUNCTION()
	void DropFromLedge();
	UFUNCTION()
	void FinishClimbing(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	void LateInitialization();

	UFUNCTION()
	void CheckAreaVolumeOnSpawn();

	UFUNCTION()
	UStaminaComponent* GetStaminaComponent();


	 virtual void Landed(const FHitResult& Hit)override;
	 void SetCurrentActionState(EActionState ActionState)override;

};

