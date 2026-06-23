// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorComponent.h"
#include "Armor.h"
#include "Pants.h"
#include "Helmet.h"
#include "EquipmentArmor.h"

UArmorComponent::UArmorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ArmorTable = nullptr;
	ArmorSoundComponent = CreateDefaultSubobject<UAudioComponent>("ArmorSoundComponent");

	bIsWearingHeavyArmor = false;
	bIsHidingHair = false;
	bIsHidingFeet = false;
}

UAudioComponent* UArmorComponent::GetArmorSoundComponent()
{
	return ArmorSoundComponent;
}

void UArmorComponent::EquipArmor(FName ArmorName)
{
	//Search general DataTable for ArmorData and Set Data
	static const FString ContextString(TEXT("NewArmorContext"));
	FArmor* ArmorData = ArmorTable->FindRow<FArmor>(ArmorName, ContextString);
	if (ArmorData)
	{
		UEquipmentArmor* EquipmentSlot = nullptr;
		switch (ArmorData->ObjectType)
		{
		case EObjectType::BodyEquipment:
			EquipmentSlot = CurrentArmor;
			bIsWearingHeavyArmor = ArmorData->bIsHeavyArmor;
			break;
		case EObjectType::LegEquipment:
			EquipmentSlot = CurrentPants;
			break;
		case EObjectType::HeadEquipment:
			EquipmentSlot = CurrentHelmet;
			bIsHidingHair = ArmorData->bIsHidingHair;
			break;
		case EObjectType::ArmEquipment:
			EquipmentSlot = CurrentGloves;
			break;
		case EObjectType::FootEquipment:
			EquipmentSlot = CurrentBoots;
			bIsHidingFeet = ArmorData->bIsHidingFeet;
			break;
		case EObjectType::CapeEquipment:
			EquipmentSlot = CurrentCape;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("(Armor Component) No valid ObjectType for %s"), *ArmorName.ToString())
			break;
		}

		EquipmentSlot->SetSkeletalMesh(ArmorData->BreastplateMesh.LoadSynchronous());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s was not found in BreastPlateArmorTable"), *ArmorName.ToString())
	}
}

FName UArmorComponent::GetCurrentArmorName(EObjectType ArmorSlot)
{
	FName ArmorName = "None";
	switch (ArmorSlot)
	{
			case EObjectType::BodyEquipment:
				ArmorName = CurrentBreastplateName;
				break;
			case EObjectType::LegEquipment:
				ArmorName = CurrentPantsName;
				break;
			case EObjectType::HeadEquipment:
				ArmorName = CurrentHelmetsName;
				break;
			case EObjectType::ArmEquipment:
				ArmorName = CurrentGauntletsName;
				break;
			case EObjectType::FootEquipment:
				ArmorName = CurrentBootsName;
				break;
			case EObjectType::CapeEquipment:
				ArmorName = CurrentCapeName;
				break;
			default:
					break;
	}

	return ArmorName;

}

