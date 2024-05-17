#include "PreCompile.h"
#include "MainGameMode.h"

#include <EngineCore/TextWidget.h>
#include <EnginePlatform/TextimeInput.h>

#include "Village.h"
#include "Camp.h"
#include "Player.h"

#include "ItemBubble.h"
#include "ItemRoller.h"
#include "ItemNiddle.h"
#include "ItemOwl.h"

#include "WaterCourse.h"

AMainGameMode::AMainGameMode()
{
}

AMainGameMode::~AMainGameMode()
{
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->DepthOn();
	//깊이버퍼 실행시 DepthOn

	GameModeActorInit();

	
#ifdef _DEBUG
	InputOn();
#endif
}

void AMainGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//UTextimeInput::IMEInput();
	std::string Text = UTextimeInput::GetReadText();
	if (Text.size() > 0)
	{
		ShowText->SetText(Text);
	}
	else
	{
		ShowText->SetText(" ");
	}

}

void AMainGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AMainGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}


void AMainGameMode::GameModeActorInit()
{
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -400.0f));




	std::shared_ptr<ACamp> Camp = GetWorld()->SpawnActor<ACamp>("Camp");
	SetCurMap(Camp);
	Camp->SetCurGameMode(this);




	Player1 = GetWorld()->SpawnActor<APlayer>("Player1", 0);
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);
	



	{//Text
		ShowText = CreateWidget<UTextWidget>(GetWorld(), "ShowText");
		ShowText->SetFont("맑은 고딕");
		ShowText->SetScale(30.0f);
		ShowText->SetColor(Color8Bit::Black);
		ShowText->SetPosition({ 0.0f ,0.0f });
		ShowText->SetFlag(FW1_LEFT);
		ShowText->AddToViewPort(11);
	}

	{//Camp 내 Item 및 Object
	
		//Block
		Camp->AddMapObject(1, 1, EMapObject::CampBlock1);
		Camp->AddMapObject(3, 1, EMapObject::CampBlock1);
		Camp->AddMapObject(1, 3, EMapObject::CampBlock1);
		Camp->AddMapObject(3, 3, EMapObject::CampBlock1);

		Camp->AddMapObject(6, 6, EMapObject::CampMoveBlock1);
		Camp->AddMapObject(9, 6, EMapObject::CampMoveBlock1);
		Camp->AddMapObject(6, 9, EMapObject::CampMoveBlock1);
		Camp->AddMapObject(9, 9, EMapObject::CampMoveBlock1);

		//Item
		Camp->AddMapObject(5, 1,EMapObject::Item,EItemType::ItemBubble);
		Camp->AddMapObject(1, 2, EMapObject::Item, EItemType::ItemNiddle);
		Camp->AddMapObject(2, 1, EMapObject::Item, EItemType::ItemOwl);
		Camp->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemShoes);
		Camp->AddMapObject(8, 6, EMapObject::Item, EItemType::ItemRoller);
		Camp->AddMapObject(6, 8, EMapObject::Item, EItemType::ItemFluid);


		//Camp 내 Object 그대로하려면 아래코드로
		//Camp->AddObjectInit();

	}

}