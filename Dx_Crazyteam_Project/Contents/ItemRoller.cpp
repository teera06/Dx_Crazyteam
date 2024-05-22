#include "PreCompile.h"
#include "ItemRoller.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Bush.h"

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
	UEngineSound::SoundPlay("ItemEat.wav");

	int iSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed;
	int iMaxSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->MaxSpeed;

	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;
	if (Type == EPlayerRideType::None)
	{
		GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed++;
		iSpeed = GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed;

		if (iSpeed > iMaxSpeed)
		{
			GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed = iMaxSpeed;
		}
	}
	else // 탈것에 타있는 경우
	{
		GetGameMode()->GetPlayer()->AddBeforeSpeedData();
	}



	if (GetIsPossessed())
	{
		std::shared_ptr<AMapObject> MapObj = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x);
		if (MapObj != nullptr)
		{
			ABush* Bush = dynamic_cast<ABush*>(GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x).get());

			Bush->SetPossessBlock(nullptr);
		}
		Destroy();
	}
	else
	{
		GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
	}
}
