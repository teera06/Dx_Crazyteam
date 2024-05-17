#include "PreCompile.h"
#include "ContentsMainDebugWin.h"

#include <EngineCore/EngineCore.h>

UContentsMainDebugWin::UContentsMainDebugWin()
{
}

UContentsMainDebugWin::~UContentsMainDebugWin()
{
}

void UContentsMainDebugWin::Init()
{

}

void UContentsMainDebugWin::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("Start"))
	{
		GEngine->ChangeLevel("IntroMainMode");
	}
}
