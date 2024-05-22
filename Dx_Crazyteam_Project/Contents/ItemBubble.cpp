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

	Renderer->CreateAnimation("ItemBubble", "Bubble(1).png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemBubble");
	Renderer->SetAutoSize(1.f, true);

}

void AItemBubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemBubble::Action()
{
	UEngineSound::SoundPlay("ItemEat.wav");

	int iWBCount = GetGameMode()->GetPlayer()->GetPlayerInfo()->WBCount;
	int iMaxCount = GetGameMode()->GetPlayer()->GetPlayerInfo()->MaxWBCount;


	if (iWBCount < iMaxCount)
	{
		++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBCount;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
