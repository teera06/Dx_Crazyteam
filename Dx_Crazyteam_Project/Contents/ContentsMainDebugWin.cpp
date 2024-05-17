#include "PreCompile.h"
#include "ContentsMainDebugWin.h"

#include <EngineCore/EngineCore.h>

ContentsMainDebugWin::ContentsMainDebugWin()
{
}

ContentsMainDebugWin::~ContentsMainDebugWin()
{
}

void ContentsMainDebugWin::Init()
{

}

void ContentsMainDebugWin::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("Start"))
	{
		GEngine->ChangeLevel("MainGameMode");
	}

	if (true == ImGui::Button("ServerGameMode"))
	{
		GEngine->ChangeLevel("ServerGameMode");
	}

	if (true == ImGui::Button("SubServerLevel"))
	{
		GEngine->ChangeLevel("SubServerLevel");
	}

	if (true == ImGui::Button("UitestMode"))
	{
		GEngine->ChangeLevel("UitestMonde");
	}

	if (true == ImGui::Button("PlaytestMode"))
	{
		GEngine->ChangeLevel("PlayertestMode");
	}

	if (true == ImGui::Button("MaptestMode"))
	{
		GEngine->ChangeLevel("testGameMode");
	}
}
