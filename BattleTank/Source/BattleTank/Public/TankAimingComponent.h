// Flynn's rad copyright.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//This is a forward declaration. It allows us to avoid chains of dependencies from #includes.
class UTankBarrel;
class UTankTurret;

//Holds barrel's properties and Elevate method.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    void SetBarrelReference(UTankBarrel* BarrelToSet); //This is a setter for our private "Barrel" variable below.
    
    void SetTurretReference(UTankTurret* TurretToSet);
    
    //TODO add SetTurretReference
    
    void AimAt(FVector HitLocation, float LaunchSpeed);
    
private:
    UTankBarrel* Barrel = nullptr; //This knows what a UTankBarrel is thanks to our forward declaration.
    
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
    
    void MoveTurretTowards(FVector AimDirection);
};
