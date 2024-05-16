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
	
	FrontRenderer->CreateAnimation("ItemRoller", "Roller.png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemRoller");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemRoller::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemRoller::Action()
{
	GetGameMode()->GetPlayer()->GetPlayerInfo()->Speed += 100;

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
