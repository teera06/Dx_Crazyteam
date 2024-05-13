#include "PreCompile.h"
#include "UitestMonde.h"

AUitestMonde::AUitestMonde()
{
}

AUitestMonde::~AUitestMonde()
{
}

void AUitestMonde::BeginPlay()
{

	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));
}

void AUitestMonde::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AUitestMonde::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}



void AUitestMonde::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
