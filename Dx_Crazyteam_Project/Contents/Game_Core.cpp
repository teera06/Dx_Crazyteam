#include "PreCompile.h"
#include "Game_Core.h"
#include "ServerGameMode.h"
#include "testGameMode.h"
#include "UitestMonde.h"
#include "PlayertestMode.h"



#include "ContentsDebugWindow.h"

#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineEditorGUI.h>

std::shared_ptr<UEngineNet> UGame_Core::Net = nullptr;

UGame_Core::UGame_Core()
{
}

UGame_Core::~UGame_Core()
{
}

void UGame_Core::Initialize()
{
	MainLoad();

	GEngine->CreateLevel<ATestGameMode>("testGameMode");
	GEngine->CreateLevel<APlayerTestMode>("PlayertestMode");
	GEngine->CreateLevel<AUitestMonde>("UitestMonde");
	GEngine->ChangeLevel("UitestMonde");

	UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("CupheadHelpMe");

}

void UGame_Core::MainLoad()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("OriginalResources");
		Dir.Move("Image");
		{
			std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png"}, true);
			for (UEngineFile& File : Files)
			{
				UEngineSprite::Load(File.GetFullPath());
			}
		}
	}


}
