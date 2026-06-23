// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaVolume.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "UI_ZoneEntryWidget.h"
#include "EternalGrace_ProtoCharacter.h"
#include "EternalGrace_GameInstance.h"

// Sets default values
AAreaVolume::AAreaVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VolumeCollision = CreateDefaultSubobject<UBoxComponent>("CollisionVolume");
	VolumeCollision->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;

	AreaEntryWidget = nullptr;
}

// Called when the game starts or when spawned
void AAreaVolume::BeginPlay()
{
	Super::BeginPlay();

	VolumeCollision->OnComponentBeginOverlap.AddDynamic(this, &AAreaVolume::RegisterVolumeEntry);
	VolumeCollision->OnComponentEndOverlap.AddDynamic(this, &AAreaVolume::RegisterVolumeLeave);

}

void AAreaVolume::RegisterVolumeEntry(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEternalGrace_ProtoCharacter* EnteringPlayer = Cast<AEternalGrace_ProtoCharacter>(OtherActor);
	if (!EnteringPlayer) return;

		TriggerPlayerEntry(EnteringPlayer);

}

void AAreaVolume::RegisterVolumeLeave(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	AEternalGrace_ProtoCharacter* EnteringPlayer = Cast<AEternalGrace_ProtoCharacter>(OtherActor);
	if (!EnteringPlayer) return;
		if (AudioComponent->IsPlaying())
		{
				AudioComponent->FadeOut(AudioFadingTime, 0.0f);
		}
}

void AAreaVolume::TriggerPlayerEntry(AEternalGrace_ProtoCharacter* EnteringPlayer)
{
	APlayerController* PlayerController = Cast<APlayerController>(EnteringPlayer->Controller);
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Cast PlayerController (AreaVolume Class)"))
			return;
	}

	if (AreaWidgetClass)
	{
		if (AreaEntryWidget && AreaEntryWidget->IsInViewport()) return;

		UE_LOG(LogTemp, Display, TEXT("Create Widget(AreaVolume)"))
			AreaEntryWidget = CreateWidget<UUI_ZoneEntryWidget>(PlayerController, AreaWidgetClass);
		if (AreaEntryWidget)
		{
			AreaEntryWidget->SetZoneName(AreaName);
			UE_LOG(LogTemp, Display, TEXT("Blend In Widget (AreaVolume)"))
				AreaEntryWidget->AddToPlayerScreen(EnteringPlayer->GetPlayerIndex());
			AreaEntryWidget->PlayAnimation(AreaEntryWidget->BlendingAnimation);
		}
	}

	ActivateBGM();
}

void AAreaVolume::ActivateBGM()
{
	UEternalGrace_GameInstance* CurrentGameInstance = Cast<UEternalGrace_GameInstance>(GetGameInstance());
	if(CurrentGameInstance && AudioComponent->GetSound())
	{
		CurrentGameInstance->ChangeBGM(AudioComponent,AudioFadingTime);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(AreaVolume) Failed to either cast GameInstance or Get Sound of AudioComponent"))
	}
}

