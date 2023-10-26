// Fill out your copyright notice in the Description page of Project Settings.


#include "Act_Buildings.h"


// Sets default values
AAct_Buildings::AAct_Buildings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(Root);

}

// Called when the game starts or when spawned
void AAct_Buildings::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AAct_Buildings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Moving the buildings
	SetActorLocation(GetActorLocation() + FVector(0,MoveSpeed*DeltaTime, 0));

	if (GetActorLocation().Y < -1 * (PillarGap * NumPillars + 300))
	{
		SetActorLocation(GetActorLocation() + FVector(0, PillarGap * NumPillars + ScreenWidth, 0));
		RandomizePillars();
	}
}

void AAct_Buildings::SpawnPillars()
{
	UE_LOG(LogTemp,Warning, TEXT("Spawned"));
	
	for (size_t i = 0; i < Pillars.Num(); i++) 
	{
		if (Pillars[i])
		{
			Pillars[i]->DestroyComponent();
		}
	}
	Pillars.Empty();

	for (size_t i = 0; i < NumPillars; i++)
	{
		UStaticMeshComponent* smc = (UStaticMeshComponent*)AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform(), true);

		if (smc)
		{
			smc->RegisterComponent();
			smc->SetMobility(EComponentMobility::Movable);
			smc->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			smc->SetWorldLocation(GetActorLocation() + FVector(0, PillarGap * i, 0));
			smc->SetStaticMesh(PillarMesh);
			Pillars.Add(smc);

		}

	}
	RandomizePillars();

}

void AAct_Buildings::RandomizePillars()
{
	for (size_t i = 0; i < NumPillars; i++)
	{
		Pillars[i]->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, 6)));
	}
}

void AAct_Buildings::OnConstruction(const FTransform& Transform)
{
	SpawnPillars();
}