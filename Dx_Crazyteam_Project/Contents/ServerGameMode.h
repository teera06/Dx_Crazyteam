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
class AServerGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)

public:
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

protected:
	std::shared_ptr<UEngineNetWindow> NetWindow;
	//std::shared_ptr<APlayer> MainPlayer = nullptr;
	//std::shared_ptr<AVillage> Village = nullptr;
	std::shared_ptr<ATitleMenu> TitleMenu = nullptr;
	std::shared_ptr<APlayLobby> PlayLobby = nullptr;


private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
	void CollectWindowAppear();
};

