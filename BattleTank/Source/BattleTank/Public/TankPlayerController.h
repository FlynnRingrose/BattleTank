// Flynn's rad copyright.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include; a quirk of Unreal headers.

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
    virtual void BeginPlay() override; //"virtual" will allow this variable to be overidden later if need be.
    
    virtual void Tick( float DeltaTime ) override; //"Override checks that there is a method with exactly the same name in the parent class.
    
private:
    
    ATank* GetControlledTank() const;
    
    //Start the tank moving the barrel so that a shot would hit where
    //the crosshair instersects the world.
    void AimTowardsCrosshair();
    
    //Return an OUT parameter, true if it hits landscape.
    bool GetSightRayHitLocation(FVector& HitLocation) const; //This will mutate an FVector.
    
    UPROPERTY (EditAnywhere)
    float CrosshairXLocation = 0.5; //These are used to divide the dimensions of the viewport by two and three.
    UPROPERTY (EditAnywhere)
    float CrosshairYLocation = 0.3333;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0;
};
