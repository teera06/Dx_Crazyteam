#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class AUitestMonde;
class UImage;
class UTextWidget;
class ATitleMenu : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleMenu();
	~ATitleMenu();

	// delete Function
	ATitleMenu(const ATitleMenu& _Other) = delete;
	ATitleMenu(ATitleMenu&& _Other) noexcept = delete;
	ATitleMenu& operator=(const ATitleMenu& _Other) = delete;
	ATitleMenu& operator=(ATitleMenu&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AUitestMonde* UIGameMode = nullptr;
	UTextWidget* TestText = nullptr;

};

