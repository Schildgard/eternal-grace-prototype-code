// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningStatue.h"
#include "EnemySpawnComponent.h"
#include "NiagaraComponent.h"
#include "EternalGrace_ProtoCharacter.h"
#include "EnemySelectWidget.h"

AEnemySpawningStatue::AEnemySpawningStatue()
{

	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>("Spawn Component");
	EnemySpawnComponent->NiagaraComponent->SetupAttachment(RootComponent);

}

void AEnemySpawningStatue::GetInteractedWith_Implementation(AEternalGrace_ProtoCharacter* InteractingPlayer)
{
//	if (EnemySpawnComponent->EnemyList.IsEmpty())
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Enemy List is Empty (EnemySpawningStatue"))
//			return;
//	}
//	UE_LOG(LogTemp, Display, TEXT("(EnemySpawningStatue) holds this enemy: %s"), *EnemySpawnComponent->EnemyList[0]->GetFName().ToString())
//
//		EnemySpawnComponent->SpawnEnemies();

	APlayerController* PlayerController = Cast<APlayerController>(InteractingPlayer->Controller);
	if(PlayerController)
	{
	EnemySpawnComponent->ShowSelectionWidget(PlayerController);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("(EnemySpawningStatue) Failed to Cast PlayerController"))
	}

}

void AEnemySpawningStatue::RegisterInteractionRadiusLeave(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	Super::RegisterInteractionRadiusLeave(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex);
	if (!EnemySpawnComponent) return;
	if (!EnemySpawnComponent->SelectWidgetInstance) return;
	if(EnemySpawnComponent->SelectWidgetInstance->IsInViewport())
	{
		EnemySpawnComponent->SelectWidgetInstance->RemoveFromParent();
	}
}
