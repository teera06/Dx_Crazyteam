#include "PreCompile.h"
#include "ItemTurtle.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemTurtle::AItemTurtle() 
{
}

AItemTurtle::~AItemTurtle() 
{
}

void AItemTurtle::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemOwl", "Owl.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemOwl");
	Renderer->SetAutoSize(1.0f, true);
}

void AItemTurtle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemTurtle::Action()
{
	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;

	if (Type == EPlayerRideType::None)
	{
		GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType = EPlayerRideType::Turtle;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
