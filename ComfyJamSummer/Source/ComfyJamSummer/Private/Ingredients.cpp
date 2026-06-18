// Fill out your copyright notice in the Description page of Project Settings.

#include "Ingredients.h"
#include "Kismet/GameplayStatics.h"
#include "Alien.h"


void AIngredients::BeginPlay()
{
    Super::BeginPlay();

    hitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // comme le blendertop, pas QueryAndPhysics
    hitBox->SetCollisionObjectType(ECC_WorldDynamic);
    hitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    hitBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    hitBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
    hitBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
    hitBox->SetGenerateOverlapEvents(true);

    UE_LOG(LogTemp, Warning, TEXT("INGREDIENT %s: WorldStatic resp=%d, enabled=%d, genOverlap=%d"),
        *GetName(),
        (int)hitBox->GetCollisionResponseToChannel(ECC_WorldStatic),
        (int)hitBox->GetCollisionEnabled(),
        hitBox->GetGenerateOverlapEvents() ? 1 : 0);
}

AIngredients::AIngredients()
{
    fillSprite = CreateDefaultSubobject<UPaperSpriteComponent>("FillSprite");
    fillSprite->SetupAttachment(root);
    fillSprite->SetHiddenInGame(true);

    hitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    hitBox->SetCollisionObjectType(ECC_WorldDynamic);
    hitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    hitBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    hitBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	hitBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
    hitBox->SetGenerateOverlapEvents(true);
}
	
const EIngredientsTypes &AIngredients::getIngredientType() const
{
    return ingredientType;
}


void AIngredients::OnGrabbed()
{
    if (ingredientType == EIngredientsTypes::gasoline)
    {
        if (AAlien* Alien = Cast<AAlien>(
            UGameplayStatics::GetActorOfClass(GetWorld(), AAlien::StaticClass())))
        {
            Alien->OnGasolineGrab();
            Alien->bGasolineInUse = true;
        }
    }
}

void AIngredients::OnReleased()
{
    if (ingredientType == EIngredientsTypes::gasoline)
    {
        if (AAlien* Alien = Cast<AAlien>(
            UGameplayStatics::GetActorOfClass(GetWorld(), AAlien::StaticClass())))
        {
            Alien->bGasolineInUse = false;
        }
    }
}