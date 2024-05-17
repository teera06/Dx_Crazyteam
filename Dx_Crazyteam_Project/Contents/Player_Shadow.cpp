#include "PreCompile.h"
#include "Player_Shadow.h"

APlayer_Shadow::APlayer_Shadow()
{
}

APlayer_Shadow::~APlayer_Shadow()
{
}

void APlayer_Shadow::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Player_Shadow.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Shadow);
	Renderer->SetAlpha(0.6f);

}

void APlayer_Shadow::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//PlayerShadowPacket(_DeltaTime);
}