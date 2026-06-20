#include "MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (Image_HowToPlay)
        Image_HowToPlay->SetVisibility(ESlateVisibility::Hidden);
    if (Button_Return)
        Button_Return->SetVisibility(ESlateVisibility::Hidden);

    if (Button_Play)
    {
        Button_Play->OnClicked.AddDynamic(this, &UMainMenu::OnPlayClicked);
    }
    if (Button_Quit)
    {
        Button_Quit->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);
    }
    if (Button_HowToPlay)
    {
        Button_HowToPlay->OnClicked.AddDynamic(this, &UMainMenu::OnHTPClicked);
    } 
    if (Button_Return)
    {
        Button_Return->OnClicked.AddDynamic(this, &UMainMenu::OnReturnClicked);
    }
}


void UMainMenu::OnPlayClicked()
{
    UGameplayStatics::OpenLevel(this, "MainGame");
}


void UMainMenu::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenu::OnHTPClicked()
{
    if (Image_HowToPlay)
        Image_HowToPlay->SetVisibility(ESlateVisibility::Visible);
    if (Button_Return)
        Button_Return->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenu::OnReturnClicked()
{
    if (Image_HowToPlay)
        Image_HowToPlay->SetVisibility(ESlateVisibility::Hidden);
    if (Button_Return)
        Button_Return->SetVisibility(ESlateVisibility::Hidden);
}