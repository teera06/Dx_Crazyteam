#include "PreCompile.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"

APlayLobby::APlayLobby()
{
}

APlayLobby::~APlayLobby()
{
}

void APlayLobby::BeginPlay()
{
	Super::BeginPlay();
	InputOn();

	PlayLobbyUI = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	PlayLobbyUI->AddToViewPort(1);
	PlayLobbyUI->SetSprite("map_pang_object5.png");
	PlayLobbyUI->SetScale({ 1280, 720 });
	PlayLobbyUI->SetActive(false);
}

void APlayLobby::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APlayLobby::SetIsActive(bool _Active)
{
	PlayLobbyUI->SetActive(_Active);
}