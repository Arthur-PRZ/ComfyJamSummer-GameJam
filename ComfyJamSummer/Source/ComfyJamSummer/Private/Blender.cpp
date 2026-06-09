// Fill out your copyright notice in the Description page of Project Settings.


#include "Blender.h"

ABlender::ABlender()
{
    fillHitBox = CreateDefaultSubobject<UBoxComponent>("FillHitBox");
    fillHitBox->SetupAttachment(root);

    fillHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    fillHitBox->SetCollisionObjectType(ECC_WorldDynamic);
    fillHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    fillHitBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); // overlap avec ingrédient
    fillHitBox->SetGenerateOverlapEvents(true);
    fillHitBox->OnComponentBeginOverlap.AddDynamic(this, &ABlender::OnIngredientOverlap);
}

void ABlender::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("FillHitBox: enabled=%d extent=%s overlap=%d"),
        (int)fillHitBox->GetCollisionEnabled(),
        *fillHitBox->GetUnscaledBoxExtent().ToString(),
        fillHitBox->GetGenerateOverlapEvents());
}

void ABlender::OnIngredientOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("OVERLAP FIRED: %s / comp=%s"),
        *GetNameSafe(OtherActor),*GetNameSafe(OtherComp));
    if (OtherComp->GetName() != TEXT("HitBox"))
        return;
    UE_LOG(LogTemp, Warning, TEXT("TOUCHE"));
    if (OtherActor && OtherActor->IsA(AIngredients::StaticClass()))
    {
        AIngredients *ingredient = Cast<AIngredients>(OtherActor);
        EIngredientsTypes ingredientType = ingredient->getIngredientType();

        UE_LOG(LogTemp, Warning, TEXT("TOUCHE INGREDIENT"));
        if (!currentIngredients.Contains(ingredientType))
        {
            currentIngredients.Add(ingredientType);
            UE_LOG(LogTemp, Warning, TEXT("INGREDIENT ADDED"));
        }
        else
            UE_LOG(LogTemp, Warning, TEXT("INGREDIENT ALREADY THERE"));
    }
}