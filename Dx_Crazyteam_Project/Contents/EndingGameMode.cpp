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
}

void AEndingGameMode::Tick(float _DeltaTime)
{
	GameOffTime -= _DeltaTime;

	if (GameOffTime < 0.f)
	{
		GEngine->EngineWindow.Off();
	}
}

void AEndingGameMode::LevelStart(ULevel* _DeltaTime)
{
	BlackFade = GetWorld()->GetLastTarget()->AddEffect<FadeEffectLongVer>();
	BlackFade.get()->EffectON();

	GameOffTime = 5.f;
}

void AEndingGameMode::LevelEnd(ULevel* _DeltaTime)
{

}