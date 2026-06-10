// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveableSprite.h"
#include "IngredientsTypes.h"
#include "Ingredients.h"
#include "BlenderTop.generated.h"

/**
 * 
 */
UCLASS()
class COMFYJAMSUMMER_API ABlenderTop : public AMoveableSprite
{
	GENERATED_BODY()
	
	private:

	UPROPERTY()
	TArray<EIngredientsTypes> currentIngredients;

	UFUNCTION()
	void OnIngredientOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	public :

	ABlenderTop();
	UPROPERTY(VisibleAnywhere)
	UBoxComponent *fillHitBox;

	const TArray<EIngredientsTypes>& getCurrentIngredients() const;
	void clearCurrentIngredients();
};
