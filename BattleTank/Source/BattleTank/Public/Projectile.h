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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    //AProjectile* ProjectileMovementComponent = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
