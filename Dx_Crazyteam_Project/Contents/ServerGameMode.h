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
class AServerGameMode : public ACAGameMode
{
	GENERATED_BODY(AGameMode)

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


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _DeltaTime) override;
	void LevelEnd(ULevel* _DeltaTime) override;

	std::shared_ptr<UEngineNetWindow> NetWindow;
	std::shared_ptr<APlayer> MainPlayer = nullptr;
	std::shared_ptr<AVillage> Village = nullptr;
};

