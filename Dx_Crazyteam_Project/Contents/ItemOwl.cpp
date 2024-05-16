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

	FrontRenderer->CreateAnimation("ItemOwl", "Owl.png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemOwl");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemOwl::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemOwl::Action()
{
	//플레이어 상태변경


	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
