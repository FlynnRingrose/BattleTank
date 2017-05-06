// Flynn's rad copyright.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state.
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};

//This is a forward declaration. It allows us to avoid chains of dependencies from #includes.
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel's properties and Elevate method.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise (UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    void AimAt(FVector Hitlocation);
    
    UFUNCTION(BlueprintCallable, Category = "Firing") //Fire ze missiles!
    void Fire();
    
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int GetRoundsLeft() const;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
    
private:
    virtual void BeginPlay() override;
    
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    virtual void TickComponent (float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;
    
    void MoveBarrelTowards(FVector AimDirection);
    
    bool IsBarrelMoving();
    
    UTankBarrel* Barrel = nullptr; //This knows what a UTankBarrel is thanks to our forward declaration.
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint; //Unlike UClass*, this will only make the projectile available in the editor.
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
    double LastFireTime = 0;
    
    FVector AimDirection;
    
    int RoundsLeft = 3;
};
