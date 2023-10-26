// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "PW_Bird.generated.h"

UCLASS()
class FLAPPYBIRD_API APW_Bird : public APawn
{
	GENERATED_BODY()


private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float JumpForce = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WidgetClass;

public:
	// Sets default values for this pawn's properties
	APW_Bird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Jump();


	UFUNCTION()
	void OnBirdHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
