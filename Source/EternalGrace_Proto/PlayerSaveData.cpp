// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSaveData.h"

FPlayerSaveData::FPlayerSaveData()
{

}

void FPlayerSaveData::UpdatePlayerData(FTransform NewTransform, FName Armor, FName Pants, FName Helmet, FName Gloves, FName Boots, FName Cape, TMap<FName, int>* ArmorDataToSave, TArray<TSubclassOf<AWeaponBase>>* WeaponMapToSave, TSubclassOf<AWeaponBase>*  CurrentWeaponToSave, TSubclassOf<AWeaponBase>* CurrentOffHandWeaponToSave, TMap<FName, int>* KeyItemsToSave)
{
	//Save Player Data
	PlayerTransform = NewTransform;
	CurrentBreastArmorName = Armor;
	CurrentPantsName = Pants;
	CurrentHelmetsName = Helmet;
	CurrentGlovesName = Gloves;
	CurrentBootsName = Boots;
	CurrentCapeName = Cape;


	SavedArmorDataMap = *ArmorDataToSave;

	SavedWeaponInventory = *WeaponMapToSave;
	CurrentWeapon = *CurrentWeaponToSave;
	CurrentOffHandWeapon = *CurrentOffHandWeaponToSave;

	SavedKeyItemDataMap = *KeyItemsToSave;
}

