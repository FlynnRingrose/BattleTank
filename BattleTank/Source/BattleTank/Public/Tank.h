#pragma once

#include "GameFramework/Pawn.h"
#include "TankBarrel.h"
#include "Tank.generated.h" //Put new includes above this line.

//Forward declarations.
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Setup) //No semicolon on this macro.
    void SetBarrelReference(UTankBarrel* BarrelToSet); //This is the setter for our private "Barrel".
    
    UFUNCTION(BlueprintCallable, Category = Setup) //You're so cool.
    void SetTurretReference(UTankTurret* TurretToSet);
    
    void AimAt(FVector Hitlocation);
    
    UFUNCTION(BlueprintCallable, Category = Firing) //Fire ze missiles!
    void Fire();
    
protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    // Sets default values for this pawn's properties
    ATank();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 4000;
    
    UPROPERTY(EditAnywhere, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint; //Unlike UClass*, this will only make the projectile available in the editor.
    
    //Local barrel reference to spawning projectile.
    UTankBarrel* Barrel = nullptr;
    
};
