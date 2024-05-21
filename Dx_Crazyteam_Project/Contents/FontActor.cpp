#include "PreCompile.h"
#include "FontActor.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>


AFontActor::AFontActor()
{
}

AFontActor::~AFontActor()
{
}

void AFontActor::BeginPlay()
{
	Super::BeginPlay();

	{//Text
		ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
		ShowText->SetFont("¸¼Àº °íµñ");
		ShowText->SetScale(30.0f);
		ShowText->SetColor(Color8Bit::Black);
		ShowText->SetPosition({ -340.0f ,-200.0f });
		ShowText->SetFlag(FW1_LEFT);
		ShowText->AddToViewPort(11);
	}
#ifdef _DEBUG
	InputOn();
#endif

}

void AFontActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_RETURN))
	{
		if (true == UTextimeInput::GetOnOff())
		{
			UTextimeInput::Off();
		}
		else
		{
			UTextimeInput::On();
		}
	}

	if (true == UTextimeInput::GetOnOff())
	{
		std::string Text = UTextimeInput::GetReadText();
		if (Text.size() > 0)
		{
			ShowText->SetText(Text);
		}
		else
		{
			ShowText->SetText(" ");
		}
	}
	else
	{
		ShowText->SetText(" ");
	}
}
