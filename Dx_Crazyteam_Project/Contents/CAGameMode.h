#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

// 설명 :
class ABaseMap;
class APlayer;
class AMapUI;
class AOtherPlayer;
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

	std::vector<AOtherPlayer*>& GetOtherPlayers()
	{
		return OtherPlayers;
	}

	std::function<void(EGameResult)> GMToUICallBack = nullptr;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	std::vector<AOtherPlayer*> OtherPlayers;
private:
	void WinCheck(float _DeltaTime);

	std::shared_ptr<ABaseMap> CurMap = nullptr;
	std::shared_ptr<APlayer> MainPlayer = nullptr;
	std::shared_ptr<AMapUI> UI = nullptr;
	int ATeamCount = 0;
	int BTeamCount = 0;
	bool IsBattleEnd = false;
	EGameResult GameResult = EGameResult::None;
};

// UI에 팀의 승리 여부를 보내야함.(승리 조건에 따라 Win, Loss, Draw UI가 다르기 때문)
// UI에 해당 Player가 죽었는지 살았는지 보내야 함.(우측 UI 애니메이션[죽으면 울고 있음])
