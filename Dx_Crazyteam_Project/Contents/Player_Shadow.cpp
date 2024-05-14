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
	Renderer->SetSprite("Player_Shadow.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Shadow);
}

void APlayer_Shadow::Tick(float _DeltaTime)
{

}