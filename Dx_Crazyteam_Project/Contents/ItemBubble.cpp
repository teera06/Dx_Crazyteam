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
	int iWBCount = GetGameMode()->GetPlayer()->GetPlayerInfo()->WBCount;
	int iMaxCount = 0;

	switch (GetGameMode()->GetPlayer()->GetPlayerInfo()->MyType)
	{
	case ECharacterType::None:
		return;
	case ECharacterType::Bazzi:
		iMaxCount = ConstValue::BazziMaxWBCount;
		break;
	case ECharacterType::Dao:
		iMaxCount = ConstValue::DaoMaxWBCount;
		break;
	case ECharacterType::Marid:
		//iMaxCount = ConstValue::MaridWBCount;
		break;
	default:
		break;
	}


	if (iWBCount < iMaxCount)
	{
		++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBCount;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
