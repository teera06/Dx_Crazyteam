#include "PreCompile.h"
#include "ItemRoller.h"

AItemRoller::AItemRoller()
{
	SetItemType(EItemType::ItemRoller);
}

AItemRoller::~AItemRoller()
{
}

void AItemRoller::BeginPlay()
{
	Super::BeginPlay();
	
	FrontRenderer->CreateAnimation("ItemRoller", "Roller.png", 0.2f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemRoller");
	FrontRenderer->SetAutoSize(1.0f, true);

}

void AItemRoller::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}