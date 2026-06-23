// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AreaVolume.generated.h"

class UBoxComponent;
class UUI_ZoneEntryWidget;
class AEternalGrace_ProtoCharacter;

UCLASS()
class ETERNALGRACE_PROTO_API AAreaVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AAreaVolume();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess))
	UBoxComponent* VolumeCollision;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TSubclassOf<UUI_ZoneEntryWidget> AreaWidgetClass;

	UPROPERTY()
	UUI_ZoneEntryWidget* AreaEntryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FName AreaName;

	const float AudioFadingTime = 3.0f;

public:	

	UFUNCTION()
	void RegisterVolumeEntry(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void RegisterVolumeLeave(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

	UFUNCTION()
	void TriggerPlayerEntry(AEternalGrace_ProtoCharacter* EnteringPlayer);

	UFUNCTION()
	void ActivateBGM();

};
