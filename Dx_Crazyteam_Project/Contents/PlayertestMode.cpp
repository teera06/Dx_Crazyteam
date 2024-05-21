#include "PreCompile.h"
#include "PlayertestMode.h"
#include "ItemBubble.h"
#include "ItemRoller.h"
#include "ItemNiddle.h"
#include "ItemOwl.h"


APlayerTestMode::APlayerTestMode()
{
}

APlayerTestMode::~APlayerTestMode()
{
}

void APlayerTestMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

	Village = GetWorld()->SpawnActor<AVillage>("Village");
	SetCurMap(Village);
	Village->SetCurGameMode(this);

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1");
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);
	Player1->MainPlayerSetting();


	Village->AddMapObject(1, 1, EMapObject::Item, EItemType::ItemBubble);
	Village->AddMapObject(2, 2, EMapObject::Item, EItemType::ItemNiddle);
	Village->AddMapObject(3, 3, EMapObject::Item, EItemType::ItemFluid);
	Village->AddMapObject(4, 4, EMapObject::Item, EItemType::ItemRoller);
	Village->AddMapObject(5, 5, EMapObject::Item, EItemType::ItemOwl);
	Village->AddMapObject(6, 6, EMapObject::Item, EItemType::ItemTurtle);
}

void APlayerTestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
}

void APlayerTestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	Player1->MainPlayerInit();
}

void APlayerTestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
