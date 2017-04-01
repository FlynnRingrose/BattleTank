// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) //This function takes a pointer to a static mesh and names it "BarrelToSet".
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));//This will return the location of the barrel if it can't find a socket named "Projectile".
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity //Although this method has many parameters we can ignore those we wish to leave as default.
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );
    
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //This turns the velocity into a directional unit vector.
        MoveBarrelTowards();
    }
    //If no solution is found, do nothing.
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    //Work out the difference between current barrel rotation and AimDirection.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //Retrieves the forward vector of the barrel and converts that into an FRotator.
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator; //Delta meaning "difference".
    UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString())
    
    //Move the barrel the right amount this frame.
    //Given a maximum elevation speed and frame time.
}
