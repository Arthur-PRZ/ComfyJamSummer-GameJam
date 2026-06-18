#include "PlayerHealth.h"

APlayerHealth::APlayerHealth()
{
    root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = root;
    for (int32 i = 0; i < 3; i++)
    {
        FName FullName = *FString::Printf(TEXT("HeartFull_%d"), i);
        FName EmptyName = *FString::Printf(TEXT("HeartEmpty_%d"), i);

        UPaperSpriteComponent* Full = CreateDefaultSubobject<UPaperSpriteComponent>(FullName);
        UPaperSpriteComponent* Empty = CreateDefaultSubobject<UPaperSpriteComponent>(EmptyName);

        Full->SetupAttachment(root);
        Empty->SetupAttachment(root);
        Empty->SetHiddenInGame(true);

        heartsFullArray.Add(Full);
        heartsEmptyArray.Add(Empty);
    }
}

void APlayerHealth::LoseLife(EDeathCause cause)
{
    if (lives <= 0)
        return;

    if (cause == EDeathCause::Arrest)
        arrestCount++;
    else if (cause == EDeathCause::Fired)
        firedCount++;

    lives--;
    UpdateHearts();

    if (lockedEnding == EDeathCause::None)
    {
        if (arrestCount >= strikesToLose)
            lockedEnding = EDeathCause::Arrest;
        else if (firedCount >= strikesToLose)
            lockedEnding = EDeathCause::Fired;
    }

    if (lives <= 0)
    {
        if (lockedEnding == EDeathCause::None)
            lockedEnding = (arrestCount > firedCount) ? EDeathCause::Arrest : EDeathCause::Fired;

        if (lockedEnding == EDeathCause::Arrest)
        {
            UE_LOG(LogTemp, Warning, TEXT("GAME OVER : ARRETE PAR LA POLICE"));
            // TODO: ecran / niveau "arrete"
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("GAME OVER : VIRE"));
            // TODO: ecran / niveau "vire"
        }
    }
}

void APlayerHealth::UpdateHearts()
{
    int totalLost = heartsFullArray.Num() - lives;
    for (int32 i = 0; i < heartsFullArray.Num(); i++)
    {
        bool lost = i < totalLost;
        heartsFullArray[i]->SetHiddenInGame(lost);
        if (heartsEmptyArray.IsValidIndex(i))
            heartsEmptyArray[i]->SetHiddenInGame(!lost);
    }
}