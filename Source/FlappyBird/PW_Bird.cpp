// Fill out your copyright notice in the Description page of Project Settings.


#include "PW_Bird.h"

// Sets default values
APW_Bird::APW_Bird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setting the root component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(Root);

	//Setting up the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->BodyInstance.bLockXTranslation = true;
	Mesh->BodyInstance.bLockXRotation = true;
	Mesh->BodyInstance.bLockYTranslation = true;
	Mesh->BodyInstance.bLockYRotation = true;
	
	//------


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 600.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APW_Bird::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetSimulatePhysics(true);
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh->OnComponentHit.AddDynamic(this, &APW_Bird::OnBirdHit);
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	
}

// Called every frame
void APW_Bird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APW_Bird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APW_Bird::Jump);

}

void APW_Bird::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
	Mesh->BodyInstance.SetLinearVelocity(FVector::UpVector * JumpForce, false);
}

void APW_Bird::OnBirdHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString HitActorName = OtherActor->GetFName().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *HitActorName);
	 
	GetWorld()->GetFirstPlayerController()->Pause();

	UUserWidget* WBP_Retry = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);
	WBP_Retry->AddToViewport();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}

