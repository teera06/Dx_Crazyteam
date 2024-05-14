#include "PreCompile.h"
#include "Game_Core.h"
#include "ServerGameMode.h"
#include "testGameMode.h"
#include "UitestMonde.h"
#include "PlayertestMode.h"
#include "ServerGameMode.h"
#include "MainGameMode.h"
#include "SubServerLevel.h"

#include "ContentsDebugWindow.h"

#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineFont.h>


std::shared_ptr<UEngineNet> UGame_Core::Net = nullptr;

UGame_Core::UGame_Core()
{
}

UGame_Core::~UGame_Core()
{
}
void UGame_Core::Initialize()
{
	UEngineFont::Load("±Ã¼­");
	MainLoad();
	CuttingAni();
	SoundLoad();

	GEngine->CreateLevel<ATestGameMode>("testGameMode");
	GEngine->CreateLevel<APlayerTestMode>("PlayertestMode");
	GEngine->CreateLevel<AUitestMonde>("UitestMonde");
	GEngine->CreateLevel<AMainGameMode>("MainGameMode");
	GEngine->CreateLevel<AServerGameMode>("ServerGameMode");
	GEngine->CreateLevel<ASubServerLevel>("SubServerLevel");
	GEngine->ChangeLevel("MainGameMode");

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
}

void UGame_Core::ForderLoadAni()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("GameResource");
	Dir.Move("Image\\UI");
	{
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();

			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}
	}
}

void UGame_Core::CuttingAni()
{
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

	// ¹°ÁÙ±â
	{
		UEngineSprite::CreateCutting("Center11.png", 4, 1);
		UEngineSprite::CreateCutting("down12.png", 11, 1);
		UEngineSprite::CreateCutting("down22.png", 11, 1);
		UEngineSprite::CreateCutting("left12.png", 11, 1);
		UEngineSprite::CreateCutting("left22.png", 11, 1);
		UEngineSprite::CreateCutting("right12.png", 11, 1);
		UEngineSprite::CreateCutting("right22.png", 11, 1);
		UEngineSprite::CreateCutting("up12.png", 11, 1);
		UEngineSprite::CreateCutting("up22.png", 11, 1);
	}
	UEngineSprite::CreateCutting("bazzi_right.png", 4, 1);
	UEngineSprite::CreateCutting("bazzi_left.png", 4, 1);
	UEngineSprite::CreateCutting("bazzi_down.png", 4, 1);
	UEngineSprite::CreateCutting("bazzi_up.png", 4, 1);
	UEngineSprite::CreateCutting("bazzi_idle.png", 4, 1);

	UEngineSprite::CreateCutting("dao_right.png", 4, 1);
	UEngineSprite::CreateCutting("dao_left.png", 4, 1);
	UEngineSprite::CreateCutting("dao_down.png", 4, 1);
	UEngineSprite::CreateCutting("dao_up.png", 4, 1);
	UEngineSprite::CreateCutting("dao_idle.png", 4, 1);
}

void UGame_Core::SoundLoad()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("GameResource");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
	}
}
