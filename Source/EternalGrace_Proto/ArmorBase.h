// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectType.h"
#include "Interactable.h"
#include "ArmorBase.generated.h"

class AEternalGrace_ProtoCharacter;
UCLASS()
class AArmorBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AArmorBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	EObjectType ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	USkeletalMesh* ArmorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FName ItemName;



public:	
	virtual void Tick(float DeltaTime) override;

	virtual void GetInteractedWith(AEternalGrace_ProtoCharacter* Interactor);
	FName GetItemName();
	EObjectType GetObjectType();
	TSoftObjectPtr<UTexture2D> GetIcon();

};
