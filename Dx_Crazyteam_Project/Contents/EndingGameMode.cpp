#include "PreCompile.h"
#include "EndingGameMode.h"
#include "FadeEffectLongVer.h"
#include <EngineCore/Image.h>

AEndingGameMode::AEndingGameMode()
{

}

AEndingGameMode::~AEndingGameMode()
{
}

void AEndingGameMode::BeginPlay()
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	Img = CreateWidget<UImage>(GetWorld(), "end");
	Img->SetSprite("Ending_Temp.png");
	Img->SetAutoSize(1.0f, true);
	Img->AddToViewPort(11);
	Img->SetPosition(FVector(0.0f, 0.0f, 0.0f));
	Img->SetActive(true);

	Credit = CreateWidget<UImage>(GetWorld(), "Credit");
	Credit->SetSprite("Ending.png");
	Credit->SetAutoSize(1.f, true);
	Credit->AddToViewPort(12);
	Credit->SetPosition(FVector(0.0f, 0.0f, 0.0f));
	Credit->SetActive(false);
}

void AEndingGameMode::Tick(float _DeltaTime)
{
	CreditOnTime -= _DeltaTime;
	GameOffTime -= _DeltaTime;
	if (EndingShader == true)
	{
		EffectOnTime -= _DeltaTime;
	}	

	if (0.0f >= CreditOnTime)
	{
		EndingShader = true;
		Img->SetActive(false);
		Credit->SetActive(true);
	}

	if (0.0f >= EffectOnTime)
	{
		BlackFade = GetWorld()->GetLastTarget()->AddEffect<FadeEffectLongVer>();
		BlackFade.get()->EffectON();
	}

	if (GameOffTime < 0.f)
	{
		GEngine->EngineWindow.Off();
	}
}

void AEndingGameMode::LevelStart(ULevel* _DeltaTime)
{

}

void AEndingGameMode::LevelEnd(ULevel* _DeltaTime)
{

}