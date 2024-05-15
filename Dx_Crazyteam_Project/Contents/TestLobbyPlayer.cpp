#include "PreCompile.h"

#include "TestLobbyPlayer.h"

ATestLobbyPlayer::ATestLobbyPlayer()
{
}

ATestLobbyPlayer::~ATestLobbyPlayer()
{
}

void ATestLobbyPlayer::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
}

void ATestLobbyPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATestLobbyPlayer::RendererInit()
{
	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->CreateAnimation("Bazzi_Idle_Down", "bazzi_idle.png", 0.1f, false, 1, 1);
	Renderer->ChangeAnimation("Bazzi_Idle_Down");
}