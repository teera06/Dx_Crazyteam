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
	int iWBPower = GetGameMode()->GetPlayer()->GetPlayerInfo()->MaxWBPower;
	int iMaxPower = 0;

	switch (GetGameMode()->GetPlayer()->GetPlayerInfo()->MyType)
	{
	case ECharacterType::None:
		return;
	case ECharacterType::Bazzi:
		iMaxPower = ConstValue::BazziDefaultWBPower;
		break;
	case ECharacterType::Dao:
		iMaxPower = ConstValue::DaoMaxWBPower;
		break;
	case ECharacterType::Marid:
		//iMaxPower = ConstValue::MaridWBPower;
		break;
	default:
		break;
	}


	if (iWBPower < iMaxPower)
	{
		++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBPower;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
