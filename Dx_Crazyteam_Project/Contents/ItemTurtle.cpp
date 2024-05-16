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
