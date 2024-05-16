#include "PreCompile.h"
#include "ItemNiddle.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemNiddle::AItemNiddle()
{
	
}

AItemNiddle::~AItemNiddle()
{
}

void AItemNiddle::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemNiddle", "Niddle.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemNiddle");
	Renderer->SetAutoSize(1.0f, true);
}

void AItemNiddle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void AItemNiddle::Action()
{
	//++GetGameMode()->GetPlayer()->GetPlayerInfo()->NiddleCount;


	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
