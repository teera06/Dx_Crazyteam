#include "PreCompile.h"
#include "ItemNiddle.h"

AItemNiddle::AItemNiddle()
{
	SetItemType(EItemType::ItemNiddle);
}

AItemNiddle::~AItemNiddle()
{
}

void AItemNiddle::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemNiddle", "Niddle.png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemNiddle");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemNiddle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
