// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Armor.h"
#include "Pants.h"
#include "Helmet.h"
#include "WeaponBase.h"
#include "KeyItem.h"
#include "EternalGrace_ProtoCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EG_PlayerController.h"
#include "ArmorBase.h"
// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	GlobalArmorInventory = nullptr;
	GlobalKeyItemInventory = nullptr;
}



void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	AEternalGrace_ProtoCharacter* Player = Cast<AEternalGrace_ProtoCharacter>(GetOwner());
	if (Player)
	{
		OwningController = Cast<AEG_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (!OwningController)
		{
			UE_LOG(LogTemp, Error, TEXT("Inventory Component failed to Cast PlayerController"))
		}
	}
}


void UInventoryComponent::ObtainArmor(TSubclassOf<AArmorBase> ArmorToObtain)
{
	ArmorInventory.Add(ArmorToObtain);
	AArmorBase* ReferenceObject = ArmorToObtain.GetDefaultObject();
	ShowObtainItemWidget(ReferenceObject->GetItemName(), ReferenceObject->GetIcon());

}

void UInventoryComponent::AddArmorToInventory(FArmor ArmorToAdd)
{
	if (!ArmorInventoryMap.Contains(ArmorToAdd.ArmorName))
	{
		ArmorInventoryMap.Add(ArmorToAdd.ArmorName, 0);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Inventory"), *ArmorToAdd.ArmorName.ToString())
	}
	else
	{
		ArmorInventoryMap[ArmorToAdd.ArmorName] += 1;
		UE_LOG(LogTemp, Warning, TEXT("Added 1 more object of %s to Inventory"), *ArmorToAdd.ArmorName.ToString())
	}

	ShowObtainItemWidget(ArmorToAdd.ArmorName, ArmorToAdd.ThumpNailImage);
}

void UInventoryComponent::AddKeyItemToInventory(FKeyItem KeyItemToAdd)
{
	if (!KeyItemInventoryMap.Contains(KeyItemToAdd.ItemName))
	{
		KeyItemInventoryMap.Add(KeyItemToAdd.ItemName, 0);
		UE_LOG(LogTemp, Warning, TEXT("Added %s to Inventory"), *KeyItemToAdd.ItemName.ToString())
	}
	else
	{
		KeyItemInventoryMap[KeyItemToAdd.ItemName] += 1;
		UE_LOG(LogTemp, Warning, TEXT("Added 1 more object of %s to Inventory"), *KeyItemToAdd.ItemName.ToString())
	}
	ShowObtainItemWidget(KeyItemToAdd.ItemName, KeyItemToAdd.ThumpnailImage);
}

void UInventoryComponent::AddWeaponToInventory(TSubclassOf<AWeaponBase> WeaponToAdd)
{
	WeaponInventory.Add(WeaponToAdd);
	AWeaponBase* ReferenceObject = WeaponToAdd.GetDefaultObject();
	ShowObtainItemWidget(ReferenceObject->GetWeaponName(), ReferenceObject->ThumpnailImage);
	//UE_LOG(LogTemp, Display, TEXT("Added to Inventory %s"), *WeaponToAdd->GetWeaponName().ToString());
}

void UInventoryComponent::TryToObtainItem(FName ObjectName, EObjectType ItemCategory)
{
	//This Function checks if this Item actually exists in global data base befor Adding it to inventory
	static const FString ContextString(TEXT("ObtainedArmorContext"));
	switch (ItemCategory)
	{
	case EObjectType::KeyItem:
	{
		FKeyItem* KeyItemContext = GlobalKeyItemInventory->FindRow<FKeyItem>(ObjectName, ContextString);
		if (KeyItemContext)
		{
			AddKeyItemToInventory(*KeyItemContext);
		}
		break;
	}
	default:
		FArmor* ArmorContext = GlobalArmorInventory->FindRow<FArmor>(ObjectName, ContextString);
		if (ArmorContext)
		{
			AddArmorToInventory(*ArmorContext);
		}
		break;
			return;
	}
}

void UInventoryComponent::ShowObtainItemWidget(FName ObjectID, TSoftObjectPtr<UTexture2D> ThumpNail)
{
	if (OwningController)
	{
		OwningController->ShowObtainWidget(ObjectID, ThumpNail);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Inventory Component could not Cast Player Controller, so it failed to show obtain Item function."))
	}
}

