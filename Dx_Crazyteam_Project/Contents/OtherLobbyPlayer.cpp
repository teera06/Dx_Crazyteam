#include "PreCompile.h"

#include "OtherLobbyPlayer.h"

AOtherLobbyPlayer::AOtherLobbyPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetOrder(5);
	SetActorScale3D(FVector(20, 20, 1));
}

AOtherLobbyPlayer::~AOtherLobbyPlayer()
{
}

void AOtherLobbyPlayer::SetRenderer(std::string_view _SpriteName, int _Index)
{
	Renderer->SetSprite(_SpriteName, _Index);
}

void AOtherLobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AOtherLobbyPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
