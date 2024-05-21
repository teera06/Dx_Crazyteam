#include "PreCompile.h"
#include "Intro.h"
#include "EngineCore/Image.h"

AIntro::AIntro()
{

}

AIntro::~AIntro()
{
}

void AIntro::BeginPlay()
{
	Super::BeginPlay();

	IntroUI = CreateWidget<UImage>(GetWorld(), "IntroUser");
	IntroUI->CreateAnimation("IntroUser", "IntroUser", 0.1f, false ,0 , 19);
	IntroUI->CreateAnimation("IntroNexen", "IntroUser", 0.1f, false, 20, 92);
	IntroUI->SetAutoSize(1.0f, true);
	IntroUI->AddToViewPort(10);
	IntroUI->SetActive(true);

	
	IntroUI->ChangeAnimation("IntroUser");

	StartUI = CreateWidget<UImage>(GetWorld(), "StartUI");
	StartUI->SetSprite("first_bge.png");
	StartUI->SetAutoSize(1.0f, true);
	StartUI->AddToViewPort(10);
	StartUI->SetActive(false);


}

void AIntro::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IntroUI->IsCurAnimationEnd())
	{
		IntroUI->ChangeAnimation("IntroNexen");
		if (true == IntroUI->IsCurAnimationEnd())
		{
			IntroUI->SetActive(false);
		
			StartUI->SetActive(true);
		}
	}
	


}
