#include "Components/HealthComponent.h"
#include "Pawns/BasePawn.h"
#include "Particles/ParticleSystemComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	CurrentHealth -= Damage;
	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		auto TowerKilled = Cast<ABasePawn>(GetOwner());
		TowerKilled->Explosion->Activate();
		GetOwner()->Destroy();
	}
}

float UHealthComponent::GetCurrentHealth() const{
	return this->CurrentHealth;
}

