#include "PreCompile.h"
#include "ItemShoes.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemShoes::AItemShoes() 
{
}

AItemShoes::~AItemShoes() 
{
}

void AItemShoes::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemShoes", "Shoes.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemShoes");
	Renderer->SetAutoSize(1.0f, true);
}

void AItemShoes::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemShoes::Action()
{
	//action
	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);

	GetGameMode()->GetPlayer()->SetCanKick(true);
}
