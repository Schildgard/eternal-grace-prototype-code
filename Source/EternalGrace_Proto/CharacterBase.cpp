// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "WeaponBase.h"
#include "ShieldBase.h"
#include "ShieldComponent.h"
#include "EternalGrace_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet//KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "EternalGrace_GameInstance.h"
#include "HealthComponent.h"
#include "ValueBarWidgetBase.h"
#include "NiagaraFunctionLibrary.h"
#include "VoiceComponent.h"
#include "StaggerComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SaveGameObject = nullptr;
	GroundSurfaceDataTable = nullptr;
	CurrentActionState = EActionState::Idle;

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FaceComp");
	HeadMesh->SetupAttachment(GetMesh());
	Hair = CreateDefaultSubobject<USkeletalMeshComponent>("Hair Component");
	Hair->SetupAttachment(HeadMesh);
	Hands = CreateDefaultSubobject<USkeletalMeshComponent>("Hands Component");
	Hands->SetupAttachment(GetMesh());

	LowerBody = CreateDefaultSubobject<USkeletalMeshComponent>("LowerBody Component");
	LowerBody->SetupAttachment(GetMesh());
	Feet = CreateDefaultSubobject<USkeletalMeshComponent>("Feet Component");
	Feet->SetupAttachment(LowerBody);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	HealthComponent->GetHitSoundComponent()->SetupAttachment(GetMesh());

	CharacterVoiceComponent = CreateDefaultSubobject<UVoiceComponent>("Character Voice Component");
	CharacterVoiceComponent->SetupAttachment(GetMesh(), "head");

	ShieldComponent = CreateDefaultSubobject<UShieldComponent>("Shield Component");
	ShieldComponent->SetupAttachment(GetMesh(), "s_hand_l");

	TimeStopDuration = 0.075f;

	CurrentGameInstance = nullptr;
	World = nullptr;
	bIsAlive = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();

	UGameInstance* GameInstanceReference = UGameplayStatics::GetGameInstance(GetWorld());
	CurrentGameInstance = Cast<UEternalGrace_GameInstance>(GameInstanceReference);

	SaveGameObject = CurrentGameInstance->GetCurrentSaveGame();

	if (ShieldComponent && ShieldComponent->GetCurrentShieldClass())
	{
		ShieldComponent->EquipShield(ShieldComponent->GetCurrentShieldClass());
	}

}

void ACharacterBase::SaveData_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("%s Saves its Data"), *GetName())
}

void ACharacterBase::LoadData_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("%s Loads its Data"), *GetName())
}

void ACharacterBase::MakeSaveCall()
{
	if (CurrentGameInstance)
	{
		CurrentGameInstance->RequestSave();
	}
}

void ACharacterBase::MakeLoadCall()
{
	if (CurrentGameInstance)
	{
		CurrentGameInstance->RequestLoad();
	}
}

UCapsuleComponent* ACharacterBase::GetHitBox_Implementation()
{
	return nullptr;
}

AWeaponBase* ACharacterBase::GetWeapon_Implementation()
{
	return nullptr;
}
AWeaponBase* ACharacterBase::GetOffhandWeapon_Implementation()
{
	return nullptr;
}
AShieldBase* ACharacterBase::GetShield_Implementation()
{
	return ShieldComponent->GetCurrentShieldObject();
}
void ACharacterBase::Attack_Implementation()
{
}

void ACharacterBase::GetDamage_Implementation(FDamage DamageContainer)
{

	if (HealthComponent->CurrentHealth <= 0) return;
	bool bIsBlocked = CurrentActionState == EActionState::Guarding && DamageContainer.DamageDirection != EAttackDirection::Back;
	//Check if here if Damage goes through Block or something
	if (bIsBlocked)
	{
		/*
		UE_LOG(LogTemp, Warning, TEXT("%s Blocks Attack. Original Damage: %f, Original Poise Damage: %f "), *GetFName().ToString(), DamageContainer.DamageValue, DamageContainer.PoiseDamageValue)

			float ReducedDamage = DamageContainer.DamageValue - ((DamageContainer.DamageValue / 100) * ShieldComponent->BlockValue);
		HealthComponent->CurrentHealth -= ReducedDamage;
		UE_LOG(LogTemp, Warning, TEXT("Damage reduced to %f"), ReducedDamage);

		float ReducesPoiseDamage = DamageContainer.PoiseDamageValue - ((DamageContainer.PoiseDamageValue / 100) * ShieldComponent->Balance);
		StaggerComponent->CurrentPoise -= ReducesPoiseDamage;
		UE_LOG(LogTemp, Warning, TEXT("PoiseDamage reduced to %f. Current Poise is : %f"), ReducesPoiseDamage, StaggerComponent->CurrentPoise);

		UGameplayStatics::SpawnSoundAtLocation(World, ShieldComponent->GetBlockSound(), DamageContainer.HitLocation, DamageContainer.HitRotation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, ShieldComponent->GetBlockEffect(), DamageContainer.HitLocation, DamageContainer.HitRotation);

		if (StaggerComponent->CurrentPoise > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Play Normal Block Reaction (CharacterBase)"))
			GetMesh()->GetAnimInstance()->Montage_Play(ShieldComponent->GetNormalBlockAnimation());
		//	FOnMontageBlendedInEnded BlendInDelegate;
		//	BlendInDelegate.BindUObject(this, &ACharacterBase::PlayBlockingVoice);
		//	GetMesh()->GetAnimInstance()->Montage_SetBlendedInDelegate(BlendInDelegate, ShieldComponent->GetNormalBlockAnimation());
		}
	*/
		BlockDamage(DamageContainer);
	}
	else
	{
		HealthComponent->GetDamage(DamageContainer.Attacker, DamageContainer.DamageValue, DamageContainer.PoiseDamageValue, DamageContainer.DamageDirection, DamageContainer.HitLocation, DamageContainer.HitRotation);
		StaggerComponent->CurrentPoise -= DamageContainer.PoiseDamageValue;
	}
	HealthComponent->UpdateHPBar();

	if (StaggerComponent->CurrentPoise <= 0)
	{
		GetStaggered(bIsBlocked, DamageContainer.DamageDirection);
	}

	if (HealthComponent->CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s call Die Implementation"), *GetFName().ToString())
			HealthComponent->CurrentHealth = 0;
		IDamageable::Execute_Die(this);
	}
}

void ACharacterBase::PlayBlockingVoice(UAnimMontage* Montage)
{
	FString VoiceSoundName = FMath::RandBool() ? "Block01" : "Block02";
	CharacterVoiceComponent->PlayVoiceSound(VoiceSoundName);
}

UNiagaraSystem* ACharacterBase::GetHitEffectSystem_Implementation()
{
	return HealthComponent->GetHitEffect();
}

UAudioComponent* ACharacterBase::GetHitSoundComponent_Implementation()
{
	return HealthComponent->GetHitSoundComponent();
}

void ACharacterBase::Die_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is defeated"), *GetFName().ToString())
		if (HealthComponent && HealthComponent->GetDeathAnimation())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(HealthComponent->GetDeathAnimation());
			GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		}
}

TArray<TEnumAsByte<EObjectTypeQuery>> ACharacterBase::GetHittableObjectTypes_Implementation()
{
	return HittableObjectTypes;
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

EActionState ACharacterBase::GetCurrentActionState()
{
	return CurrentActionState;
}

void ACharacterBase::CancelGuard()
{
	if (CurrentActionState == EActionState::Guarding)
	{
		CurrentActionState = EActionState::Idle;
	}
	else return;
}

void ACharacterBase::SetCurrentActionState(EActionState ActionState)
{
	CurrentActionState = ActionState;
	//Also Update ActionState of AnimInstance
}

void ACharacterBase::PlayFootStepSound(FName FootSocket)
{
	UE_LOG(LogTemp, Warning, TEXT("No override for PlayFootStepSound (Character Base Class) %s"), *GetFName().ToString())
}

UPhysicalMaterial* ACharacterBase::GetGroundMaterial()
{
	FVector ActorLocation = GetActorLocation();
	FVector ScanDirection = FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z - GroundScanDistance);
	FHitResult OutHit;;

	bool Hit = UKismetSystemLibrary::LineTraceSingle(World, ActorLocation, ScanDirection, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, {}, EDrawDebugTrace::None, OutHit, true);

	if (!Hit)
	{
		return nullptr;
	}
	UPhysicalMaterial* HitMaterial = OutHit.PhysMaterial.Get();
	return HitMaterial;
}

void ACharacterBase::RotateTowardsTarget(AActor* Target)
{
	//GET LOOK ROTATION BETWEEN PLAYER AND TARGET
	FRotator Look = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	//BREAK LOOK ROTATION TO YAW ONLY
	FRotator DesiredRotation = FRotator(0, Look.Yaw, 0);
	SetActorRotation(DesiredRotation);
}

UHealthComponent* ACharacterBase::GetHealthComponent()
{
	return HealthComponent;
}

void ACharacterBase::UnequipShield()
{
	ShieldComponent->Unequip();
}

void ACharacterBase::StartHitStop()
{
	FTimerHandle StopDuration;

	CustomTimeDilation = 0.0f;

	GetWorld()->GetTimerManager().SetTimer(StopDuration, this, &ACharacterBase::StopHitStop, TimeStopDuration, false);

}

void ACharacterBase::StopHitStop()
{
	CustomTimeDilation = 1.0f;
}

UVoiceComponent* ACharacterBase::GetVoiceComponent()
{
	return CharacterVoiceComponent;
}

void ACharacterBase::GetStaggered(bool bIsBlocking, EAttackDirection Direction)
{
	if (!StaggerComponent) return;
	StaggerComponent->GetStaggered(bIsBlocking, Direction);
	SetCurrentActionState(EActionState::Staggered);
}

void ACharacterBase::BlockDamage(FDamage DamageContainer)
{

	UE_LOG(LogTemp, Warning, TEXT("%s Blocks Attack. Original Damage: %f, Original Poise Damage: %f "), *GetFName().ToString(), DamageContainer.DamageValue, DamageContainer.PoiseDamageValue)

		float ReducedDamage = DamageContainer.DamageValue - ((DamageContainer.DamageValue / 100) * ShieldComponent->BlockValue);
	HealthComponent->CurrentHealth -= ReducedDamage;
	UE_LOG(LogTemp, Warning, TEXT("Damage reduced to %f"), ReducedDamage);

	float ReducesPoiseDamage = DamageContainer.PoiseDamageValue - ((DamageContainer.PoiseDamageValue / 100) * ShieldComponent->Balance);
	StaggerComponent->CurrentPoise -= ReducesPoiseDamage;
	UE_LOG(LogTemp, Warning, TEXT("PoiseDamage reduced to %f. Current Poise is : %f"), ReducesPoiseDamage, StaggerComponent->CurrentPoise);

	UGameplayStatics::SpawnSoundAtLocation(World, ShieldComponent->GetBlockSound(), DamageContainer.HitLocation, DamageContainer.HitRotation);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, ShieldComponent->GetBlockEffect(), DamageContainer.HitLocation, DamageContainer.HitRotation);

	if (StaggerComponent->CurrentPoise > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Play Normal Block Reaction (CharacterBase)"))
			GetMesh()->GetAnimInstance()->Montage_Play(ShieldComponent->GetNormalBlockAnimation());
		//	FOnMontageBlendedInEnded BlendInDelegate;
		//	BlendInDelegate.BindUObject(this, &ACharacterBase::PlayBlockingVoice);
		//	GetMesh()->GetAnimInstance()->Montage_SetBlendedInDelegate(BlendInDelegate, ShieldComponent->GetNormalBlockAnimation());
	}
}

