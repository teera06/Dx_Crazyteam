#include "PreCompile.h"
#include "CAGameMode.h"
#include "OtherPlayer.h"
#include "Player.h"
#include "FadeEffect.h"
#include "MapUI.h"

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

	ChangeLevelTime = 0.0f;
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
	else
	{
		ChangeLevelTime += _DeltaTime;
		if (7.0f <= ChangeLevelTime)
		{
			GEngine->ChangeLevel("EndingLevel");
		}
	}
}

void ACAGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	BlackFade = GetWorld()->GetLastTarget()->AddEffect<FadeEffect>();
	BlackFade.get()->EffectON();
}

void ACAGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	if (nullptr != BlackFade)
	{
		BlackFade.get()->EffectOff();
	}
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
	
	if (0 != PlayerCount && nullptr != MainPlayer)
	{
		for (size_t i = 0; i < PlayerCount; i++)
		{
			if (true == OtherPlayers[i]->IsOtherPlayerDestroy())
			{
				continue;
			}
			if (ETeamType::None == OtherPlayers[i]->GetTeamType())
			{
				continue;
			}

			ETeamType Team = OtherPlayers[i]->GetTeamType();
			if (ETeamType::ATeam == Team)
			{
				ATeamCount++;
				IsRefereeStart = true;
			}
			else if (ETeamType::BTeam == Team)
			{
				BTeamCount++;
				IsRefereeStart = true;
			}



#ifdef _DEBUG			
			std::string PlayerPos = std::format("Player_{} Position : {}\n", i, OtherPlayers[i]->GetActorLocation().ToString());			
			UEngineDebugMsgWindow::PushMsg(PlayerPos);
#endif
		} // end for

		// Main
		if (true == IsRefereeStart && nullptr != MainPlayer && false == ConstValue::MainPlayerIsDie)
		{
			if (ETeamType::ATeam == MainPlayer->GetTeamType())
			{
				ATeamCount++;
			}
			else if(ETeamType::BTeam == MainPlayer->GetTeamType())
			{
				BTeamCount++;
			}
		}

#ifdef _DEBUG
		std::string TeamCount = std::format("A Team : {} | B Team : {}\n", ATeamCount, BTeamCount);
		UEngineDebugMsgWindow::PushMsg(TeamCount);
#endif


		// °ÔÀÓ °á°ú
		if (true == BattleStart && 0 != PlayerCount && true == IsRefereeStart && false == IsTimeOut)
		{
			if (ATeamCount == 0 && BTeamCount == 0)
			{
				GMToUICallBack(EGameResult::Draw);
				GMToPlayerCallBack(EGameResult::Draw);
				IsBattleEnd = true;
			}
			else if (BTeamCount == 0) // A ½Â
			{
				if (ETeamType::ATeam == MainPlayer->GetTeamType())
				{
					GMToUICallBack(EGameResult::Win);
					GMToPlayerCallBack(EGameResult::Win);
				}
				else if (ETeamType::BTeam == MainPlayer->GetTeamType())
				{
					GMToUICallBack(EGameResult::Loss);
					GMToPlayerCallBack(EGameResult::Loss);
				}
				IsBattleEnd = true;
			}
			else if (ATeamCount == 0) // B ½Â
			{
				if (ETeamType::ATeam == MainPlayer->GetTeamType())
				{
					GMToUICallBack(EGameResult::Loss);
					GMToPlayerCallBack(EGameResult::Loss);
				}
				else if (ETeamType::BTeam == MainPlayer->GetTeamType())
				{
					GMToUICallBack(EGameResult::Win);
					GMToPlayerCallBack(EGameResult::Win);
				}
				IsBattleEnd = true;
			}
		}
	}

	// Time Out
	if (nullptr != GamePlayUI)
	{
		GamePlayUI->GameEndTimeLogic = [&](bool _TimeOut)
			{
				if (true == _TimeOut)
				{
					GMToUICallBack(EGameResult::Draw);
					GMToPlayerCallBack(EGameResult::Draw);
					IsTimeOut = true;
				}
				else
				{
					int a = 0;
				}
			};
	}
	else
	{
		int a = 0;
	}
}
