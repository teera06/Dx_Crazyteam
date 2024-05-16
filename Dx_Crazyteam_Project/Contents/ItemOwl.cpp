#include "PreCompile.h"
#include "ItemOwl.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemOwl::AItemOwl()
{
	
}

AItemOwl::~AItemOwl()
{
}

void AItemOwl::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemOwl", "Owl.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemOwl");
	Renderer->SetAutoSize(1.0f, true);

}

void AItemOwl::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemOwl::Action()
{
	//플레이어 상태변경
	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;

	if (Type == EPlayerRideType::None)
	{
		GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType = EPlayerRideType::Owl;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
