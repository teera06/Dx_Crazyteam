#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>


class UImage;
class ACAObject;
class ACAGameMode;
class APlayLobby : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayLobby();
	~APlayLobby();

	// delete Function
	APlayLobby(const APlayLobby& _Other) = delete;
	APlayLobby(APlayLobby&& _Other) noexcept = delete;
	APlayLobby& operator=(const APlayLobby& _Other) = delete;
	APlayLobby& operator=(APlayLobby&& _Other) noexcept = delete;

	void SetIsActive(bool _Active);

	void NewPlayer();

	std::vector<UImage*> LobbyPlayer;

	void SettingUIPlayerName(std::vector<std::string> _Names);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SwapSelectCharacter(UImage* _SelectCharacter);
	void SwapTeamSelectCharacter(UImage* _SelectCharacter);


	void TeamSelectBegin();
	void RoomBegin();
	void CharacterBegin();
	void StartBegin();
	void MapSelectBegin();
	void LobbyPlayerBegin();

	UImage* PlayLobbyUI = nullptr;
	UImage* GameStart = nullptr;
	UImage* SelectMap = nullptr;

	//캐릭터 선택창
	UImage* RandomBT = nullptr;
	UImage* DaoBT = nullptr;
	UImage* DizniBT = nullptr;
	UImage* MosBT = nullptr;
	UImage* EthiBT = nullptr;
	UImage* MaridBT = nullptr;
	UImage* BazziBT = nullptr;
	UImage* UniBT = nullptr;
	UImage* KephiBT = nullptr;
	UImage* SuBT = nullptr;
	UImage* HooUBT = nullptr;
	UImage* RayBT = nullptr;

	//캐릭터 설명
	UImage* LobbyCharacterBanner = nullptr;
	UImage* Randomex = nullptr;
	UImage* Daoex = nullptr;
	UImage* Maridex = nullptr;
	UImage* Kephiex = nullptr;
	UImage* Bazziex = nullptr;
	
	//팀 선택
	UImage* SelectTeam = nullptr;
	UImage* TeamA = nullptr;
	UImage* TeamB = nullptr;
	
	//선택한 캐릭터
	UImage* SelectCharacter = nullptr;
	UImage* checkUI = nullptr;

	//로비 플레이어 캐릭터
	//std::vector<UImage*> LobbyPlayer;
	std::vector<UImage*> Rank;
	
	//플레이어 Room
	UImage* Room1 = nullptr;
	UImage* Room2 = nullptr;
	UImage* Room3 = nullptr;
	UImage* Room4 = nullptr;
	UImage* Room5 = nullptr;
	UImage* Room6 = nullptr;
	UImage* Room7 = nullptr;
	
	ACAGameMode* Teamtyp = nullptr;


	bool SwitchON = false;
	bool TeamSwitchON = false;
	bool IsSelectSharacter = false;
	bool IsTeamSelectSharacter = false;

	bool RoomHoverChack = false;
	bool RoomO1 = true;
	bool RoomX1 = false;
	bool RoomO2 = true;
	bool RoomX2 = false;
	bool RoomO3 = true;
	bool RoomX3 = false;
	bool RoomO4 = true;
	bool RoomX4 = false;
	bool RoomO5 = true;
	bool RoomX5 = false;
	bool RoomO6 = true;
	bool RoomX6 = false;
	bool RoomO7 = true;
	bool RoomX7 = false;


	bool RoomSwitch= false;
	int  PlayerCount = 0;
	int TestCount = 0;

private:
	int MySessionToken = -1;
	bool IsGetSessionToken = false;
	static bool IsClient;
	static bool Create;
	static int Create_Count;
	int Cha_Count = 0;

public:
	int ChangeUIIndex = -1;

	inline void SetMySessionToken(int _Value)
	{
		MySessionToken = _Value;
		IsGetSessionToken = true;
	}

	// APlayLobby
	std::function<void(APlayLobby*, int, std::string_view)> ChracterChangeLogic = nullptr;
};

