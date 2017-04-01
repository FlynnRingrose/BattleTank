// Flynn's rad copyright.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    void SetBarrelReference(UStaticMeshComponent* BarrelToSet); //This is a setter for our private "Barrel" variable below.
    
    //TODO add SetTurretReference
    
    void AimAt(FVector HitLocation, float LaunchSpeed);
    
private:
    UStaticMeshComponent* Barrel = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
};
