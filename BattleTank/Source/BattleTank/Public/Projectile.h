// Flynn's rad copyright.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void LaunchProjectile(float Speed);

private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;
	
};
