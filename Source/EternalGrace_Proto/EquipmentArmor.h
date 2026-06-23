// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentBase.h"
#include "EquipmentArmor.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALGRACE_PROTO_API UEquipmentArmor : public UEquipmentBase
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	bool bIsHeavyArmor;

	void GetInteractedWith(AEternalGrace_ProtoCharacter* Interactor) override;

	
};
