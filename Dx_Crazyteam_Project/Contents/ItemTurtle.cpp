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

	Renderer->CreateAnimation("Turtle", "Turtle.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("Turtle");
	Renderer->SetAutoSize(1.0f, true);
}

void AItemTurtle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemTurtle::Action()
{
	UEngineSound::SoundPlay("ItemEat.wav");

	EPlayerRideType Type = GetGameMode()->GetPlayer()->GetPlayerInfo()->RideType;
	FVector ItemCurPos = GetActorLocation();

	if (Type == EPlayerRideType::None && false == GetGameMode()->GetPlayer()->GetIsPlayerTrap())
	{
		GetGameMode()->GetPlayer()->SetRideType(EPlayerRideType::Turtle);
		GetGameMode()->GetPlayer()->SetActorLocation(ItemCurPos);
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}
