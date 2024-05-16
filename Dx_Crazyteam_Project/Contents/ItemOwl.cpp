#include "PreCompile.h"
#include "ItemOwl.h"

AItemOwl::AItemOwl()
{
	SetItemType(EItemType::ItemOwl);
}

AItemOwl::~AItemOwl()
{
}

void AItemOwl::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemOwl", "Owl.png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemOwl");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemOwl::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
