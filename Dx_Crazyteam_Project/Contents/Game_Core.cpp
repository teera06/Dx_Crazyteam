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

	UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("contentsHelpMe");

}

void UGame_Core::MainLoad()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("GameResource");
		Dir.Move("Image");
		{
			std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png",".bmp" }, true);
			for (UEngineFile& File : Files)
			{
				UEngineSprite::Load(File.GetFullPath());
			}
		}
	}
	
	UEngineSprite::CreateCutting("Bazzi_1.bmp", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_1a.bmp", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_2.bmp", 5, 2);
	UEngineSprite::CreateCutting("Bazzi_3.bmp", 5, 4);
	UEngineSprite::CreateCutting("Bazzi_4.bmp", 5, 7);
	UEngineSprite::CreateCutting("Dao_1.bmp", 5, 12);
	UEngineSprite::CreateCutting("Dao_2.bmp", 5, 2);
	UEngineSprite::CreateCutting("Dao_3.bmp", 5, 4);
	UEngineSprite::CreateCutting("Dao_4.bmp", 5, 4);
	UEngineSprite::CreateCutting("Dao_5.bmp", 5, 6);
	UEngineSprite::CreateCutting("Effect_Shield.bmp", 5, 2);
	UEngineSprite::CreateCutting("luxMarid_1.bmp", 5, 12);
	UEngineSprite::CreateCutting("luxMarid_2.bmp", 5, 2);
	UEngineSprite::CreateCutting("luxMarid_3.bmp", 5, 4);
	UEngineSprite::CreateCutting("luxMarid_4.bmp", 5, 4);
	UEngineSprite::CreateCutting("luxMarid_5.bmp", 5, 6);
	UEngineSprite::CreateCutting("Player_Devil.bmp", 5, 18);


	UEngineSprite::CreateCutting("Bazzi_1.png", 5, 18);

	UEngineSprite::CreateCutting("bazzi_right.png", 6, 1);
	UEngineSprite::CreateCutting("bazzi_left.png", 6, 1);
	UEngineSprite::CreateCutting("bazzi_down.png", 8, 1);
	UEngineSprite::CreateCutting("bazzi_up.png", 8, 1);

	// π∞¡Ÿ±‚
	{
		UEngineSprite::CreateCutting("Center11.png", 1, 4);
		UEngineSprite::CreateCutting("down12.png", 11, 1);
		UEngineSprite::CreateCutting("down22.png", 11, 1);
		UEngineSprite::CreateCutting("left12.png", 11, 1);
		UEngineSprite::CreateCutting("left22.png", 11, 1);
		UEngineSprite::CreateCutting("right12.png", 11, 1);
		UEngineSprite::CreateCutting("right22.png", 11, 1);
		UEngineSprite::CreateCutting("up12.png", 11, 1);
		UEngineSprite::CreateCutting("up22.png", 11, 1);
	}
}
