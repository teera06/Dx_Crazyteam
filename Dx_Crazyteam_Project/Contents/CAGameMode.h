#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

// Ό³Έν :
class ABaseMap;
class APlayer;
class AMapUI;
class ACAGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	ACAGameMode();
	~ACAGameMode();

	// delete Function
	ACAGameMode(const ACAGameMode& _Other) = delete;
	ACAGameMode(ACAGameMode&& _Other) noexcept = delete;
	ACAGameMode& operator=(const ACAGameMode& _Other) = delete;
	ACAGameMode& operator=(ACAGameMode&& _Other) noexcept = delete;

	void SetCurMap(std::shared_ptr<ABaseMap> _CurMap)
	{
		CurMap = _CurMap;
	}

	std::shared_ptr<ABaseMap> GetCurMap()
	{
		return CurMap;
	}

	void SetMainPlayer(std::shared_ptr<APlayer> _Player)
	{
		MainPlayer = _Player;
	}

	std::shared_ptr<APlayer> GetPlayer()
	{
		return MainPlayer;
	}

	void SetUI(std::shared_ptr<AMapUI> _UI)
	{
		UI = _UI;
	}

	std::shared_ptr<AMapUI> GetUI()
	{
		return UI;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	std::shared_ptr<ABaseMap> CurMap = nullptr;
	std::shared_ptr<APlayer> MainPlayer = nullptr;
	std::shared_ptr<AMapUI> UI = nullptr;

	EMap CurMapType = EMap::Village;
};

