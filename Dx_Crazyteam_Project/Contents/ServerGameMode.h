#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>
#include "CAGameMode.h"


// Ό³Έν :
class UEngineNetWindow;
class APlayer;
class AVillage;
class ATitleMenu;
class APlayLobby;
class AServerTestPlayer;
class ACamp;
class AMainGameMode;
class ALobbyMainMode;
class AServerGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)


public:
	static ENetType NetType;
	// constrcuter destructer
	AServerGameMode();
	~AServerGameMode();

	// delete Function
	AServerGameMode(const AServerGameMode& _Other) = delete;
	AServerGameMode(AServerGameMode&& _Other) noexcept = delete;
	AServerGameMode& operator=(const AServerGameMode& _Other) = delete;
	AServerGameMode& operator=(AServerGameMode&& _Other) noexcept = delete;

	void ServerPacketInit(UEngineDispatcher& Dis);
	void ClientPacketInit(UEngineDispatcher& Dis);

	std::shared_ptr<APlayLobby> GetPlayLobby();


	static void ServerOpen();
	static bool GetIsServerOpen()
	{
		return IsServerOpen;
	}
	

	std::shared_ptr<AMainGameMode> MainGame = nullptr;
	std::shared_ptr<ALobbyMainMode> MainLobby = nullptr;
	//std::shared_ptr<ULevel> NetWindow;

protected:
	static std::shared_ptr<UEngineNetWindow> NetWindow;
	//std::shared_ptr<ACamp> Camp = nullptr;
	//std::shared_ptr<ATitleMenu> TitleMenu = nullptr;
	//std::shared_ptr<APlayLobby> PlayLobby = nullptr;


private:
	static bool IsServerOpen;

private:

	static void SetIsServerOpen(bool _Value)
	{
		IsServerOpen = _Value;
	}
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void CollectWindowAppear();
};

