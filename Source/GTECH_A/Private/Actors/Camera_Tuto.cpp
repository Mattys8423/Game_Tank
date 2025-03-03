// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera_Tuto.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACamera_Tuto::ACamera_Tuto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}

// Called when the game starts or when spawned
void ACamera_Tuto::BeginPlay()
{
	Super::BeginPlay();
	
	Camera->SetActive(false);
}

// Called every frame
void ACamera_Tuto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Is_zoom) {
	//	float NewFOV = FMath::FInterpTo(Camera->FieldOfView, TargetFOV, DeltaTime, FOVInterpSpeed);
	//	Camera->SetFieldOfView(NewFOV);
	//	Is_zoom = false;
	//}
}

void ACamera_Tuto::ActivateCamera(float number_of_camera){
	if (number_of_camera == number) {
		if (Camera)
		{
			Camera->SetActive(true);
			Camera->SetFieldOfView(90.0f);
			//Is_zoom = true;
		}
	}
}

