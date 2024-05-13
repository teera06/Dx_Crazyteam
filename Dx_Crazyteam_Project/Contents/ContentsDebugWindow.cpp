#include "PreCompile.h"
#include "ContentsDebugWindow.h"

#include <EngineCore/EngineCore.h>

UContentsDebugWindow::UContentsDebugWindow()
{
}

UContentsDebugWindow::~UContentsDebugWindow()
{
}

void UContentsDebugWindow::Init()
{
}

void UContentsDebugWindow::OnGui(ULevel* Level, float _Delta)
{
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