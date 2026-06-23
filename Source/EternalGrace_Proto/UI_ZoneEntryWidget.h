// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlendingWidget.h"
#include "UI_ZoneEntryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class ETERNALGRACE_PROTO_API UUI_ZoneEntryWidget : public UBlendingWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta =(BindWidget))
	UTextBlock* ZoneName;

public:
	UFUNCTION()
	void SetZoneName(FName Name);
	
};
