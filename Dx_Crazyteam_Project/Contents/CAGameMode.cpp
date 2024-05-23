#include "PreCompile.h"
#include "CAGameMode.h"
#include "OtherPlayer.h"

ACAGameMode::ACAGameMode() 
{
}

ACAGameMode::~ACAGameMode() 
{
}

void ACAGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->DepthOn();


#ifdef _DEBUG
	InputOn();
#endif
}

void ACAGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == IsBattleEnd)
	{
		WinCheck(_DeltaTime);
	}
	else if (true == IsBattleEnd)
	{
		if (nullptr != GMToUICallBack)
		{
			GMToUICallBack(GameResult);
		}
	}


}

void ACAGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ACAGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}


void ACAGameMode::WinCheck(float _DeltaTime)
{
	size_t PlayerCount = OtherPlayers.size();
	bool flag = false;
	
	ATeamCount = 0;
	BTeamCount = 0;

#ifdef _DEBUG
	std::string GetUIToTime = std::format("Time : {}\n", BTeamCount);
	UEngineDebugMsgWindow::PushMsg(GetUIToTime);
#endif
	
	if (0 != PlayerCount)
	{
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (true == OtherPlayers[i]->IsOtherPlayerDestroy())
			{
				continue;
			}

			ETeamType Team = OtherPlayers[i]->GetTeamType();
			if (ETeamType::ATeam == Team)
			{
				ATeamCount++;
			}
			else if (ETeamType::BTeam == Team)
			{
				BTeamCount++;
			}



#ifdef _DEBUG
			std::string TeamCount = std::format("A Team : {} | B Team : {}\n", ATeamCount, BTeamCount);
			std::string PlayerPos = std::format("Player_{} Position : {}\n", i, OtherPlayers[i]->GetActorLocation().ToString());
			UEngineDebugMsgWindow::PushMsg(TeamCount);
			UEngineDebugMsgWindow::PushMsg(PlayerPos);
#endif
		} // end for


		if (ATeamCount == 0 && BTeamCount == 0)
		{
			GameResult = EGameResult::Draw;
			IsBattleEnd = true;
		}
		else if (BTeamCount == 0)
		{
			GameResult = EGameResult::ATeamWin;
			IsBattleEnd = true;
		}
		else if (ATeamCount == 0)
		{
			GameResult = EGameResult::BTeamWin;
			IsBattleEnd = true;
		}
	}
}
