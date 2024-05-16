#include "PreCompile.h"
#include "ItemFluid.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemFluid::AItemFluid() 
{
}

AItemFluid::~AItemFluid() 
{
}

void AItemFluid::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemBubble", "Bubble(1).png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemBubble");
	FrontRenderer->SetAutoSize(1.f, true);
}

void AItemFluid::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemFluid::Action()
{
	++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBPower;


	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
