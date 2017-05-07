// Flynn's rad copyright.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
    //So that first fire is after initial reload.
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    if (RoundsLeft <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
    //TODO Handle aiming and locked states.
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, 0.01); //Vectors are equal.
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return; }
    
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
        AimDirection = OutLaunchVelocity.GetSafeNormal(); //This turns the velocity into a directional unit vector.
        MoveBarrelTowards(AimDirection);
    }
    //If no solution is found, do nothing.
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    
    //Work out the difference between current barrel rotation and AimDirection.
    auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //Retrieves the forward vector of the barrel and converts that into an FRotator.
    auto AimAsRotator = AimDirection.Rotation(); //Converts the AimDirection from bHaveAimSolution to an FRotator.
    auto DeltaRotator = AimAsRotator - BarrelRotator; //Delta meaning "difference".
    //UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString())
    
    Barrel->Elevate(DeltaRotator.Pitch); //TODO Remove magic number.
    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
    Turret->Rotate(DeltaRotator.Yaw);
    }
    else //Avoid going the long way round.
    {
    Turret->Rotate(-DeltaRotator.Yaw);
    }
}

void UTankAimingComponent::Fire()
{

    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }
        //Spawn a projectile at the socket location on the barrel.
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                ProjectileBlueprint,
                Barrel->GetSocketLocation(FName("Projectile")),
                Barrel->GetSocketRotation(FName("Projectile"))
            );
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        RoundsLeft--;
    }
}
