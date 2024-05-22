#include "PreCompile.h"
#include "ItemShoes.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Bush.h"

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
	UEngineSound::SoundPlay("ItemEat.wav");
	//action

	GetGameMode()->GetPlayer()->SetCanKick(true);

	if (GetIsPossessed())
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
	}
}
