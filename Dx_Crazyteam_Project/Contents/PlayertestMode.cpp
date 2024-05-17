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

	Player1 = GetWorld()->SpawnActor<APlayer>("Player1");
	Player1->SetCurGameMode(this);
	SetMainPlayer(Player1);
	//Player1->SetCharacterType(ECharacterType::Marid);

	std::shared_ptr<AItemBubble> Bubble = GetWorld()->SpawnActor<AItemBubble>("ItemTest");
	Bubble->SetActorLocation(Player1->GetActorLocation());

	std::shared_ptr<AItemRoller> Roller = GetWorld()->SpawnActor<AItemRoller>("ItemTest");
	Roller->SetActorLocation(FVector(100.0f, 100.0f, 0.0f));

	std::shared_ptr<AItemNiddle> Niddle = GetWorld()->SpawnActor<AItemNiddle>("ItemTest");
	Niddle->SetActorLocation(FVector(50.0f, 50.0f, 0.0f));

	std::shared_ptr<AItemOwl> Owl = GetWorld()->SpawnActor<AItemOwl>("ItemTest");
	Owl->SetActorLocation(FVector(150.0f, 150.0f, 0.0f));

}

void APlayerTestMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
}

void APlayerTestMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void APlayerTestMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
