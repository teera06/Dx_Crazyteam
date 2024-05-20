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
	int GetCreateTime() { return MapTime_Second; }
	
	void ClientCreate() { Client_Create = true; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ClientSend();
	void ServerSend();

	int MapTime_MilliSecond = 0;
	int MapTime_Second = 0;
	int Sub_MilliSecond = 0;
	int Sub_Second = 0;
	bool Client_Create = false;
	bool Client_Send = false;
	bool SerVer_Send = false;


	float CreateTime();

private:
	UImage* MapPlayUI = nullptr;
	UImage* PlayerItemUI = nullptr;
	UImage* GameStartUI = nullptr;
	UImage* ColonUI = nullptr;
	std::vector<UImage*> PlayerUI;
	std::vector<UImage*> GameTimeerUI;

	static float GameTimeCheck;
	int MinUI = 2;
	int SecondUI = 5;
	int SecondUI2 = 9;
};

