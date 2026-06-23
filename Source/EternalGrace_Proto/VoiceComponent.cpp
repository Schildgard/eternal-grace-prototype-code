// Fill out your copyright notice in the Description page of Project Settings.


#include "VoiceComponent.h"

UVoiceComponent::UVoiceComponent()
{
	VoiceMap.Add("Pain01", nullptr);
	VoiceMap.Add("Pain02", nullptr);
	VoiceMap.Add("Death", nullptr);
}

TMap<FString, USoundBase*> UVoiceComponent::GetVoiceMap()
{
	return VoiceMap;
}

void UVoiceComponent::PlayVoiceSound(FString SoundName)
{
	UE_LOG(LogTemp, Warning, TEXT("Execute Play Voice Sound Function"))
	USoundBase* VoiceSound = *VoiceMap.Find(SoundName);
	if(VoiceSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found VoiceLine! Now Set Parameter and Trigger"))
		SetObjectParameter(FName("VoiceLine"), VoiceSound);
		Play();
		SetTriggerParameter("PlayVoiceLine");
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find VoiceLine"))
	}
}
