#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include; a quirk of Unreal headers.

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);
    
    UFUNCTION()
    void OnPossessedTankDeath();
    
private:
    virtual void BeginPlay() override; //"virtual" will allow this variable to be overidden later if need be.
    
    virtual void SetPawn(APawn* InPawn) override;
    
    virtual void Tick( float DeltaTime ) override; //"Override checks that there is a method with exactly the same name in the parent class.
    
    //Start the tank moving the barrel so that a shot would hit where
    //the crosshair instersects the world.
    void AimTowardsCrosshair();
    
    //Return an OUT parameter, true if it hits landscape.
    bool GetSightRayHitLocation(FVector& HitLocation) const; //This will mutate an FVector.
    
    UPROPERTY (EditDefaultsOnly)
    float CrosshairXLocation = 0.5; //These are used to divide the dimensions of the viewport by two and three.
    
    UPROPERTY (EditDefaultsOnly)
    float CrosshairYLocation = 0.3333;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0;
};
