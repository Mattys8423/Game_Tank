#include "Dialogue_Box.h"
#include "Camera_Tuto.h"
//#include "Pawns/Tank.h"
#include "Components/BoxComponent.h" 

// Sets default values
ADialogue_Box::ADialogue_Box()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void ADialogue_Box::BeginPlay()
{
	Super::BeginPlay();

	Show_Dialogue();

	//BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADialogue_Box::OnComponentBeginOverlap);
}

// Called every frame
void ADialogue_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ADialogue_Box::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
//
//	if (Has_activated == false) {
//		auto Tank_class = Cast<ATank>(GetOwner());
//		if (OtherActor && OtherActor == Tank_class)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Change_text");
//			auto Camera = Cast<ACamera_Tuto>(GetOwner());
//			//Tank_class->SetCamera(false);
//			//Tank_class->SetCamera_Turret(false);
//			//Camera->ActivateCamera(number);
//			ChangeText(number);
//			Has_activated = true;
//		}
//	}
//}

void ADialogue_Box::Set_HasActivated(bool Active) {
	if (Has_activated) {
		Has_activated = Active;
	}
}



