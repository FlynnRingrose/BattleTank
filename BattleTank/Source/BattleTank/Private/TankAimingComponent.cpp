// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) //This function takes a pointer to a static mesh and names it "BarrelToSet".
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
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace //Parameter must be present to prevent bug.
    );
    
    if (bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //This turns the velocity into a directional unit vector.
        MoveBarrelTowards(AimDirection);
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), Time);
    }
    else
    {
        auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
    }
    //If no solution is found, do nothing.
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    //Work out the difference between current barrel rotation and AimDirection.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //Retrieves the forward vector of the barrel and converts that into an FRotator.
    auto AimAsRotator = AimDirection.Rotation(); //Converts the AimDirection from bHaveAimSolution to an FRotator.
    auto DeltaRotator = AimAsRotator - BarrelRotator; //Delta meaning "difference".
    //UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString())
    
    Barrel->Elevate(5); //TODO Remove magic number.
}
