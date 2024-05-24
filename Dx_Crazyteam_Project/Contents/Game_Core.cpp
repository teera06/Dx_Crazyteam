#include "PreCompile.h"
#include "Game_Core.h"
#include "ServerGameMode.h"
#include "testGameMode.h"
#include "UitestMonde.h"
#include "PlayertestMode.h"
#include "ServerGameMode.h"
#include "MainGameMode.h"
#include "SubServerLevel.h"
#include "IntroMainMode.h"
#include "LobbyMainMode.h"
#include "EndingGameMode.h"

#include "ContentsDebugWindow.h"
#include "ContentsMainDebugWin.h"

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
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsShader");
		UEngineShader::AutoCompile(Dir);
	}

	UEngineFont::Load("±Ã¼­");
	UEngineFont::Load("±¼¸²");
	UEngineFont::Load("¸¼Àº °íµñ");
	UEngineFont::Load("Bold");
	GEngine->EngineWindow.SetWindowTitle("Crazy Arcade");
	MainLoad();
	CuttingAni();
	SoundLoad();
	ForderLoadAni();

	// Material
	std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("FadeShader_Black");
	Mat->SetPixelShader("FadeShader_Black.fx");
	Mat->SetVertexShader("FadeShader_Black.fx");
	std::shared_ptr<UEngineMaterial> LongVer = UEngineMaterial::Create("FadeShader_LongVer");
	LongVer->SetPixelShader("FadeShader_LongVer.fx");
	LongVer->SetVertexShader("FadeShader_LongVer.fx");

	std::shared_ptr<AIntroMainMode> IntroMainMode = GEngine->CreateLevel<AIntroMainMode>("IntroMainMode",0);
	std::shared_ptr<ALobbyMainMode> LobbyMainMode = GEngine->CreateLevel<ALobbyMainMode>("LobbyMainMode",0);
	std::shared_ptr<AMainGameMode> MainGameMode = GEngine->CreateLevel<AMainGameMode>("MainGameMode",0);
	std::shared_ptr<AServerGameMode> ServerGameMode = GEngine->CreateLevel<AServerGameMode>("ServerGameMode",0);
	ServerGameMode->MainGame = MainGameMode;
	ServerGameMode->MainLobby = LobbyMainMode;

	////////////
	GEngine->CreateLevel<ATestGameMode>("testGameMode");
	GEngine->CreateLevel<APlayerTestMode>("PlayertestMode");
	GEngine->CreateLevel<ASubServerLevel>("SubServerLevel");
	GEngine->CreateLevel<AUitestMonde>("UitestMonde");
	GEngine->CreateLevel<AEndingGameMode>("EndingLevel");
	GEngine->ChangeLevel("SubServerLevel");

	UEngineEditorGUI::CreateEditorWindow<UContentsDebugWindow>("contentsHelpMe");
	UEngineEditorGUI::CreateEditorWindow<UContentsMainDebugWin>("MainStart");

}

void UGame_Core::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	UEngineDirectory NewDir;
	NewDir.MoveToSearchChild("GameResource");

	//_OutWindowTitle = "TestMyTitle";

	std::string IconPath = NewDir.AppendPath("icon_gm.ico");
	_SmallIconPath = IconPath;

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
	// ¹°Ç³¼±
	{
		UEngineSprite::CreateCutting("bomb.png", 4, 1);
	}
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

	// Ä³¸¯ÅÍ
	{
		// Red Bazzi
		UEngineSprite::CreateCutting("bazzi_right.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_left.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_down.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_up.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_idle.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_trap.png", 4, 1);
		UEngineSprite::CreateCutting("bazzi_trap_long.png", 5, 7);
		UEngineSprite::CreateCutting("bazzi_rescue.png", 3, 1);
		UEngineSprite::CreateCutting("bazzi_die.png", 5, 2);
		UEngineSprite::CreateCutting("bazzi_1_red.png", 5, 18);
		UEngineSprite::CreateCutting("bazzi_3_red.png", 5, 4);
		UEngineSprite::CreateCutting("Bazzi_3_blue.png", 5, 4);

		// Blue Bazzi
		UEngineSprite::CreateCutting("Bazzi_1_blue.png", 5, 18);
		UEngineSprite::CreateCutting("Bazzi_2_blue.png", 5, 2);
		UEngineSprite::CreateCutting("Bazzi_3_blue.png", 5, 4);
		UEngineSprite::CreateCutting("Bazzi_4_blue.png", 5, 7);

		// Red Dao
		UEngineSprite::CreateCutting("Dao_1_red.png", 5, 12);
		UEngineSprite::CreateCutting("Dao_2_red.png", 5, 2);
		UEngineSprite::CreateCutting("Dao_3_red.png", 5, 4);
		UEngineSprite::CreateCutting("Dao_4_red.png", 5, 4);
		UEngineSprite::CreateCutting("Dao_5_red.png", 5, 6);
		UEngineSprite::CreateCutting("Dao_6_red.png", 2, 1);

		// Blue Dao 
		UEngineSprite::CreateCutting("dao_right.png", 4, 1);
		UEngineSprite::CreateCutting("dao_left.png", 4, 1);
		UEngineSprite::CreateCutting("dao_down.png", 4, 1);
		UEngineSprite::CreateCutting("dao_up.png", 4, 1);
		UEngineSprite::CreateCutting("dao_idle.png", 4, 1);
		UEngineSprite::CreateCutting("dao_trap.png", 4, 1);
		UEngineSprite::CreateCutting("dao_trap_long.png", 5, 6);
		UEngineSprite::CreateCutting("dao_rescue.png", 3, 1);
		UEngineSprite::CreateCutting("dao_die.png", 5, 2);
		UEngineSprite::CreateCutting("dao_1_blue.png", 5, 12);
		UEngineSprite::CreateCutting("dao_3_blue.png", 5, 4);
		UEngineSprite::CreateCutting("dao_4_blue.png", 5, 4);
		UEngineSprite::CreateCutting("dao_6_blue.png", 2, 1);

		// Red Marid
		UEngineSprite::CreateCutting("luxMarid_1.png", 5, 12);
		UEngineSprite::CreateCutting("luxMarid_2.png", 5, 2);
		UEngineSprite::CreateCutting("luxMarid_3.png", 5, 4);
		UEngineSprite::CreateCutting("luxMarid_4.png", 5, 4);
		UEngineSprite::CreateCutting("luxMarid_5.png", 5, 6);
		UEngineSprite::CreateCutting("luxMarid_6.png", 2, 1);

		// Blue Marid
		UEngineSprite::CreateCutting("luxMarid_1_blue.png", 5, 12);
		UEngineSprite::CreateCutting("luxMarid_2_blue.png", 5, 2);
		UEngineSprite::CreateCutting("luxMarid_3_blue.png", 5, 4);
		UEngineSprite::CreateCutting("luxMarid_4_blue.png", 5, 4);
		UEngineSprite::CreateCutting("luxMarid_5_blue.png", 5, 6);
		UEngineSprite::CreateCutting("luxMarid_6_blue.png", 2, 1);
	}

	// ¾ÆÀÌÅÛ
	{
		// Item
		UEngineSprite::CreateCutting("Bubble(1).png", 6, 1);
		UEngineSprite::CreateCutting("Roller.png", 6, 1);
		UEngineSprite::CreateCutting("Fluid.png", 6, 1);

		UEngineSprite::CreateCutting("Niddle.png", 6, 1);
		UEngineSprite::CreateCutting("Owl.png", 6, 1);
		UEngineSprite::CreateCutting("Shoes.png", 6, 1);
		UEngineSprite::CreateCutting("Turtle.png", 6, 1);

		// Item Shadow
		UEngineSprite::CreateCutting("ItemShadow.png", 2, 1);

	}

	// UI
	{
		UEngineSprite::CreateCutting("GameTimer.png", 10, 1);
		UEngineSprite::CreateCutting("START.png", 6, 1);
		UEngineSprite::CreateCutting("ui_coplayui_KCW.png", 1, 4);

		UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Normal_R.png", 1, 2);
		UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Lose.png", 1, 4);
		
	}
}

void UGame_Core::SoundLoad()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("GameResource");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav", ".mp3"}, true);
		for (UEngineFile& File : Files)
		{
			File.Open(EIOOpenMode::Read, EIODataType::Binary);

			char Arr[100];
			File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());

		}
	}
}

void UGame_Core::End()
{
	if (nullptr != Net)
	{
		Net->End();
		Net = nullptr;
	}
}