// Fill out your copyright notice in the Description page of Project Settings.


#include "BlenderTop.h"

ABlenderTop::ABlenderTop()
{
    fillHitBox = CreateDefaultSubobject<UBoxComponent>("FillHitBox");
    fillHitBox->SetupAttachment(root);

    fillHitBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
    
    fillHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    fillHitBox->SetCollisionObjectType(ECC_WorldDynamic);
    fillHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    fillHitBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
    fillHitBox->SetGenerateOverlapEvents(true);
    fillHitBox->OnComponentBeginOverlap.AddDynamic(this, &ABlenderTop::OnIngredientOverlap);
    fillHitBox->OnComponentEndOverlap.AddDynamic(this, &ABlenderTop::OnIngredientEndOverlap);


    hitBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
}

const TArray<EIngredientsTypes> &ABlenderTop::getCurrentIngredients() const
{
    return currentIngredients;
}


void ABlenderTop::clearCurrentIngredients()
{
    currentIngredients.Empty();
}

void ABlenderTop::ValidateIngredient()
{
    EIngredientsTypes ingredientType = pendingIngredient->getIngredientType();

    currentIngredients.Add(ingredientType);
    UE_LOG(LogTemp, Warning, TEXT("INGREDIENT ADDED"));

}

void ABlenderTop::OnIngredientEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
    if (OtherActor == pendingIngredient)
    {
        GetWorld()->GetTimerManager().ClearTimer(IngredientTimer);
        pendingIngredient = nullptr;
    }
}

void ABlenderTop::OnIngredientOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
    if (OtherComp->GetName() != TEXT("HitBox"))
        return;
    if (OtherActor && OtherActor->IsA(AIngredients::StaticClass()))
    {
        AIngredients *ingredient = Cast<AIngredients>(OtherActor);
        pendingIngredient = ingredient;
        EIngredientsTypes ingredientType = pendingIngredient->getIngredientType();

        if (currentIngredients.Contains(ingredientType))
        {
            UE_LOG(LogTemp, Warning, TEXT("INGREDIENT ALREADY THERE"));
        }
        else
        {
            if (ingredientType == EIngredientsTypes::gasoline)
            {
                UE_LOG(LogTemp, Warning, TEXT("PUTING GASOLINEEE..."));
                GetWorld()->GetTimerManager().SetTimer(IngredientTimer, this, &ABlenderTop::ValidateIngredient, 3.0f, false);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("PUTING INGREDIENT..."));
                GetWorld()->GetTimerManager().SetTimer(IngredientTimer, this, &ABlenderTop::ValidateIngredient, 1.0f, false);
            }

        }
    }
}