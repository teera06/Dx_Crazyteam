#include "PreCompile.h"
#include "ContentsMainDebugWin.h"

#include <EngineCore/EngineCore.h>

bool UContentsMainDebugWin::IsLevel = false;

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

		if (true == IsLevel)
		{
			return;
		}


		GEngine->ChangeLevel("IntroMainMode");
	}
}
