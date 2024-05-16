#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

class UImage;
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SwapSelectCharacter(UImage* _SelectCharacter);

	UImage* PlayLobbyUI = nullptr;
	UImage* GameStart = nullptr;
	//캐릭터 선택창
	UImage* RandomBT;
	UImage* DaoBT;
	UImage* DizniBT;
	UImage* MosBT;
	UImage* EthiBT;
	UImage* MaridBT;
	UImage* BazziBT;
	UImage* UniBT;
	UImage* KephiBT;
	UImage* SuBT;
	UImage* HooUBT;
	UImage* RayBT;
	//캐릭터 설명
	UImage* Randomex;
	UImage* Daoex;
	UImage* Maridex;
	UImage* Kephiex;
	UImage* Bazziex;

	//선택한 캐릭터
	UImage* SelectCharacter;
	
	std::vector<UImage*> RoomVector;
	std::vector<UImage*>::iterator RoomIter = RoomVector.begin();


	UCollision* Collision0 = nullptr;

	bool SwitchON = false;
	bool IsSelectSharacter = false;
};

