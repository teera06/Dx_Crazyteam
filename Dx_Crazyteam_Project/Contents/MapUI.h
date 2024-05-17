#pragma once
#include "CAObject.h"

class UImage;
class AMapUI : public ACAObject
{
	GENERATED_BODY(ACAObject)

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
	UImage* GameStartUI = nullptr;
	UImage* ColonUI = nullptr;
	std::vector<UImage*> PlayerUI;
	std::vector<UImage*> GameTimeerUI;

	float GameTimeCheck = 1.0f;
	int MinUI = 2;
	int SecondUI = 5;
	int SecondUI2 = 9;
};

