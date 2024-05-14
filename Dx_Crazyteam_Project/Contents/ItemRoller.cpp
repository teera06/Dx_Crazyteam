#include "PreCompile.h"
#include "ItemRoller.h"

AItemRoller::AItemRoller()
{
}

AItemRoller::~AItemRoller()
{
}

void AItemRoller::BeginPlay()
{
	Super::BeginPlay();
	
	FrontRenderer->CreateAnimation("ItemRoller", "Roller.png", true, 0.5f);



}

void AItemRoller::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}