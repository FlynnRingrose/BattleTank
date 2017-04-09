// Flynn's rad copyright.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate= false; //Don't launch on construction.
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
    UE_LOG(LogTemp, Warning, TEXT("Firing projectile at %f!"), Speed);
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate(); //Reactivate so that the projectile can fire.
}
