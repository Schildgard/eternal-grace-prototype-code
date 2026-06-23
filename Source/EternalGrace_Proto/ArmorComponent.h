// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectType.h"
#include "Components/ActorComponent.h"
#include "ArmorComponent.generated.h"



class UEquipmentArmor;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ETERNALGRACE_PROTO_API UArmorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UArmorComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	UDataTable* ArmorTable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentBreastplateName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentGauntletsName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentBootsName;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentCapeName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentPantsName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess))
	FName CurrentHelmetsName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess))
	UAudioComponent* ArmorSoundComponent;


public:
	UPROPERTY()
	UEquipmentArmor* CurrentArmor;
	UPROPERTY()
	UEquipmentArmor* CurrentGloves;
	UPROPERTY()
	UEquipmentArmor* CurrentPants;
	UPROPERTY()
	UEquipmentArmor* CurrentBoots;
	UPROPERTY()
	UEquipmentArmor* CurrentHelmet;
	UPROPERTY()
	UEquipmentArmor* CurrentCape;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsWearingHeavyArmor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsHidingHair;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsHidingFeet;

	UFUNCTION()
	UAudioComponent* GetArmorSoundComponent();

	UFUNCTION(BlueprintCallable)
	void EquipArmor(FName ArmorName);

	UFUNCTION()
	FName GetCurrentArmorName(EObjectType ArmorSlot);

};
