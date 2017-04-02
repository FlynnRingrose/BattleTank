// Flynn's rad copyright.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay(); //"Super" makes sure that the default BeginPlay() from further up the tree is called.
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    
    FVector HitLocation; //Out parameter.
    if (GetSightRayHitLocation(HitLocation)) //Has side-effect - is going to line trace.
    {
        GetControlledTank()->AimAt(HitLocation);
    }
}

//Get world location of linetrace through crosshair -- true if it hits landscape.
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const //Waiting for a reference to an FVector.
{
    //Find the crosshair position in pixel coordinates.
    int32 ViewportSizeX, ViewportSizeY; //Instantiated on next line into dimensions of viewport.
    GetViewportSize(ViewportSizeX, ViewportSizeY); //The engine uses out parameters like this often.
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation); //We can do this calculation right inside the FVector2D constructor.
    
    //"Deproject" the screen position of the crosshair to a world direction.
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        //Line-trace along that LookDirection, and see what we hit (up to max range).
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if (GetWorld()->LineTraceSingleByChannel(
            HitResult,
            StartLocation,
            EndLocation,
            ECollisionChannel::ECC_Visibility)
        )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false; //Line trace didn't succeed.
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; //To be discarded but it must be passed in.
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection //"If this works, do something.
    );
}
