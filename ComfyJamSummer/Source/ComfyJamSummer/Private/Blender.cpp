// Fill out your copyright notice in the Description page of Project Settings.


#include "Blender.h"

ABlender::ABlender()
{
    completeBlenderSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CompliteBlenderSprite"));
    completeBlenderSprite->SetupAttachment(root);

    blender = CreateDefaultSubobject<USceneComponent>(TEXT("Blender"));
    blender->SetupAttachment(root);

    fillHitBox = CreateDefaultSubobject<UBoxComponent>("FillHitBox");
    blenderHitBox = CreateDefaultSubobject<UBoxComponent>("BlenderHitBox");
    blenderSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BlenderSprite");

    fillHitBox->SetupAttachment(moveable);
    blenderHitBox->SetupAttachment(blender);
    blenderSprite->SetupAttachment(blender);

    fillHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    fillHitBox->SetCollisionObjectType(ECC_WorldDynamic);
    fillHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    fillHitBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap); 
    fillHitBox->SetGenerateOverlapEvents(true);
    fillHitBox->OnComponentBeginOverlap.AddDynamic(this, &ABlender::OnIngredientOverlap);

    blenderHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    blenderHitBox->SetCollisionObjectType(ECC_WorldStatic);
    blenderHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    blenderHitBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    blenderHitBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
    blenderHitBox->SetGenerateOverlapEvents(true);
}

void ABlender::BeginPlay()
{
    Super::BeginPlay();
}

void ABlender::OnIngredientOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

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