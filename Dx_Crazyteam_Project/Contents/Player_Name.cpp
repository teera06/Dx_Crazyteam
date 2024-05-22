#include "PreCompile.h"
#include "Player_Name.h"
#include "Player.h"
#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>


APlayer_Name::APlayer_Name()
{
}

APlayer_Name::~APlayer_Name()
{
}


void APlayer_Name::BeginPlay()
{
	Super::BeginPlay();

	InsertName("NONE");

}

void APlayer_Name::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//PlayerShadowPacket(_DeltaTime);
}

void APlayer_Name::InsertName(std::string_view _Name)
{
	

	NameText = CreateWidget<UTextWidget>(GetWorld(), _Name);
	NameText->SetFont("¸¼Àº °íµñ");
//	NameText->SetPosition(FVector(-70.0f, 80.0f));

	NameText->SetScale(10.0f);
	NameText->SetColor(Color8Bit::Black);
	NameText->SetOrder(1);
	NameText->AddToViewPort(11);


	int a = 0;

}
