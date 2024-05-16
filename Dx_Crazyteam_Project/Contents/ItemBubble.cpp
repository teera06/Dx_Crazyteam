#include "PreCompile.h"
#include "ItemBubble.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemBubble::AItemBubble()
{
	
}

AItemBubble::~AItemBubble()
{
}

void AItemBubble::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemBubble", "Bubble(1).png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemBubble");
	FrontRenderer->SetAutoSize(1.f, true);

}

void AItemBubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemBubble::Action()
{
	++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBCount;


	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
