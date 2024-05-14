#include "PreCompile.h"
#include "MapUI.h"
#include "EngineCore/Image.h"

AMapUI::AMapUI()
{
}

AMapUI::~AMapUI()
{
}

void AMapUI::BeginPlay()
{
	Super::BeginPlay();

	MapPlayUI = CreateWidget<UImage>(GetWorld(), "MapPlayUI");
	MapPlayUI->AddToViewPort(3);
	MapPlayUI->SetSprite("MapPlayUI.png");
	MapPlayUI->SetAutoSize(1.0f, true);

	MapPlayUI = CreateWidget<UImage>(GetWorld(), "PlayerItemUI");
	MapPlayUI->AddToViewPort(4);
	MapPlayUI->SetAutoSize(1.0f, true);
	MapPlayUI->SetPosition(FVector(315.0f, -190.0f, 100.0f));
	MapPlayUI->SetActive(true);
}

void AMapUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}


void AMapUI::SetPlayItemUI(int _ItemNumber)
{
	MapPlayUI->SetSprite("Item", _ItemNumber);
}