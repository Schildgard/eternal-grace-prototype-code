// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnComponent.h"
#include "Enemy.h"
#include "EnemyDataWidget.h"
#include "EnemySelectWidget.h"
#include "NiagaraComponent.h"
#include "Components/Button.h"

// Sets default values for this component's properties
UEnemySpawnComponent::UEnemySpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("SpawnPositionMarker");

}


// Called when the game starts
void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UEnemySpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemySpawnComponent::SpawnEnemies()
{
	FVector SpawnLocation = NiagaraComponent->GetComponentLocation();
	FRotator SpawnRotation = NiagaraComponent->GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("SpawnLocation: %f . %f. %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
	GetWorld()->SpawnActor<AEnemy>(EnemyClassToSpawn, SpawnLocation, SpawnRotation);
}

void UEnemySpawnComponent::SpawnSkeleton()
{
	EnemyClassToSpawn = SelectWidgetInstance->Enemy01Data->EnemyClass;
	SpawnEnemies();
}

void UEnemySpawnComponent::SpawnHammerSkeleton()
{
	EnemyClassToSpawn = SelectWidgetInstance->Enemy02Data->EnemyClass;
	SpawnEnemies();
}

void UEnemySpawnComponent::SpawnSkeletonKnight()
{
	EnemyClassToSpawn = SelectWidgetInstance->Enemy03Data->EnemyClass;
	SpawnEnemies();
}

void UEnemySpawnComponent::ShowSelectionWidget(APlayerController* OwningController)
{
	if (EnemySelectWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("(EnemySpawnComponent) Create Widget!"))
			SelectWidgetInstance = CreateWidget<UEnemySelectWidget>(OwningController, EnemySelectWidgetClass);
		if (SelectWidgetInstance)
		{
			SelectWidgetInstance->AddToPlayerScreen();
			SelectWidgetInstance->SetFocus();

			SelectWidgetInstance->Enemy01Data->GetWidgetButton()->OnClicked.AddDynamic(this, &UEnemySpawnComponent::SpawnSkeleton);
			SelectWidgetInstance->Enemy02Data->GetWidgetButton()->OnClicked.AddDynamic(this, &UEnemySpawnComponent::SpawnHammerSkeleton);
			SelectWidgetInstance->Enemy03Data->GetWidgetButton()->OnClicked.AddDynamic(this, &UEnemySpawnComponent::SpawnSkeletonKnight);
		}
	}

}

