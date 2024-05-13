#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class UImage;
class TitleMenu : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	TitleMenu();
	~TitleMenu();

	// delete Function
	TitleMenu(const TitleMenu& _Other) = delete;
	TitleMenu(TitleMenu&& _Other) noexcept = delete;
	TitleMenu& operator=(const TitleMenu& _Other) = delete;
	TitleMenu& operator=(TitleMenu&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

