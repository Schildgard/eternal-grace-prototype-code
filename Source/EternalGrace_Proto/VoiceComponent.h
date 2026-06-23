// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "VoiceComponent.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALGRACE_PROTO_API UVoiceComponent : public UAudioComponent
{
	GENERATED_BODY()
	UVoiceComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess))
	TMap<FString, USoundBase*> VoiceMap;

public:

	TMap<FString, USoundBase*> GetVoiceMap();

	void PlayVoiceSound(FString SoundName);
	
};
