#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this line.

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
    
public:
    // Sets default values for this pawn's properties
    ATank();
    
    virtual void BeginPlay() override;
    
    //Called by the engine when actor damage is dealt.
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
    
    //Return current health as a percentage of starting health between 0 and 1.
    UFUNCTION(BlueprintPure, Category = "Health") //BlueprintPure is sort of like Blueprint's version of Const.
    float GetHealthPercent() const;
    
    FTankDelegate OnDeath;
    
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100;
    
    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth; //Initialized in BeginPlay.
    
};

