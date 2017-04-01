// Flynn's rad copyright.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this line.

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    void AimAt(FVector Hitlocation);
    
    UFUNCTION(BlueprintCallable, Category = Setup) //No semicolon on this macro.
    void SetBarrelReference(UStaticMeshComponent* BarrelToSet); //This is the setter for our private "Barrel".
    
protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    // Sets default values for this pawn's properties
    ATank();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 100000; //TODO Find a sensible default.
};
