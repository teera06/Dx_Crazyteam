#include "PreCompile.h"
#include "ItemRoller.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemRoller::AItemRoller()
{
	
}

AItemRoller::~AItemRoller()
{
}

void AItemRoller::BeginPlay()
{
	Super::BeginPlay();
	
	Renderer->CreateAnimation("ItemRoller", "Roller.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemRoller");
	Renderer->SetAutoSize(1.0f, true);

}

void AItemRoller::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemRoller::Action()
{
	int iSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed;
	int iMaxSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->MaxSpeed;

	switch (GetGameMode()->GetPlayer()->GetPlayerInfo()->MyType)
	{
	case ECharacterType::None:
		return;
	case ECharacterType::Bazzi:
		iMaxSpeed = ConstValue::BazziMaxSpeed;
		break;
	case ECharacterType::Dao:
		iMaxSpeed = ConstValue::DaoMaxSpeed;
		break;
	case ECharacterType::Marid:
		//iMaxSpeed = ConstValue::MaridWBCount;
		break;
	default:
		break;
	}


	GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed += 10;
	iSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed;

	if (iSpeed > iMaxSpeed)
	{
		GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed = iMaxSpeed;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
