// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectType.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

struct FArmor;
struct FPants;
struct FHelmet;
struct FKeyItem;
class AWeaponBase;
class AArmorBase;
class AEG_PlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlobalData", meta = (AllowPrivateAccess))
	UDataTable* GlobalArmorInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlobalData", meta = (AllowPrivateAccess))
	UDataTable* GlobalKeyItemInventory;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LocalData", meta =(AllowPrivateAccess))
	TMap<FName, int> ArmorInventoryMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LocalData", meta = (AllowPrivateAccess))
	TMap<FName, int> KeyItemInventoryMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LocalData", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<AWeaponBase>> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LocalData", meta = (AllowPrivateAccess))
	TArray<TSubclassOf<AArmorBase>> ArmorInventory;

	UPROPERTY()
	AEG_PlayerController* OwningController;


	UFUNCTION()
	void ObtainArmor(TSubclassOf<AArmorBase> ArmorToObtain);
	UFUNCTION()
	void AddArmorToInventory(FArmor ArmorToAdd);
	UFUNCTION()
	void AddKeyItemToInventory(FKeyItem KeyItemToAdd);

	UFUNCTION()
	void AddWeaponToInventory(TSubclassOf<AWeaponBase> WeaponToAdd);
	UFUNCTION()
	void TryToObtainItem(FName ObjectName, EObjectType ItemCategory);

	UFUNCTION()
	void ShowObtainItemWidget(FName ObjectID, TSoftObjectPtr<UTexture2D> ThumpNail);

		
};
