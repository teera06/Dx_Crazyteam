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
	UEngineSound::SoundPlay("ItemEat.wav");
	//플레이어 상태변경
	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;
	FVector ItemCurPos = GetActorLocation();

	if (Type == EPlayerRideType::None && false == GetGameMode()->GetPlayer()->GetIsPlayerTrap())
	{
		GetGameMode()->GetPlayer()->SetRideType(EPlayerRideType::Owl);
		GetGameMode()->GetPlayer()->SetActorLocation(ItemCurPos);
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
