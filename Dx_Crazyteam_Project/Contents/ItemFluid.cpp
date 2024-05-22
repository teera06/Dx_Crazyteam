#include "PreCompile.h"
#include "ItemFluid.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AItemFluid::AItemFluid() 
{
}

AItemFluid::~AItemFluid() 
{
}

void AItemFluid::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemFluid", "Fluid.png", 0.3f, true, 0, 5);
	Renderer->ChangeAnimation("ItemFluid");
	Renderer->SetAutoSize(1.f, true);
}

void AItemFluid::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemFluid::Action()
{
	UEngineSound::SoundPlay("ItemEat.wav");

	int iWBPower = GetGameMode()->GetPlayer()->GetPlayerInfo()->WBPower;
	int iMaxPower = GetGameMode()->GetPlayer()->GetPlayerInfo()->MaxWBPower;


	if (iWBPower < iMaxPower)
	{
		++GetGameMode()->GetPlayer()->GetPlayerInfo()->WBPower;
	}

	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);

	/*if (GetIsPossessed())
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
	}*/
}
