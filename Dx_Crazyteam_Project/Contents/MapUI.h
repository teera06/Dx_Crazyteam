#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class UImage;
class AMapUI : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMapUI();
	~AMapUI();

	// delete Function
	AMapUI(const AMapUI& _Other) = delete;
	AMapUI(AMapUI&& _Other) noexcept = delete;
	AMapUI& operator=(const AMapUI& _Other) = delete;
	AMapUI& operator=(AMapUI&& _Other) noexcept = delete;

	void SetPlayItemUI(int _ItemNumber);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* MapPlayUI = nullptr;
	UImage* PlayerItemUI = nullptr;
};

