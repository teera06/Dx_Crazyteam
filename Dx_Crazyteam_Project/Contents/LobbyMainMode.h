#pragma once
#include <EngineCore/GameMode.h>
class UEngineSoundPlayer;


class APlayLobby;
class UEngineDispatcher;
class ALobbyMainMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ALobbyMainMode(); // 디폴트 생성자
	~ALobbyMainMode(); // 디폴트 소멸자

	// delete Function
	ALobbyMainMode(const ALobbyMainMode& _Other) = delete; // 디폴트 복사 생성자
	ALobbyMainMode(ALobbyMainMode&& _Other) noexcept = delete; 
	ALobbyMainMode& operator=(const ALobbyMainMode& _Other) = delete; // 디폴트 대입 연산자
	ALobbyMainMode& operator=(ALobbyMainMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

	void ServerPacketInit(UEngineDispatcher& Dis);
	void ClientPacketInit(UEngineDispatcher& Dis);

private:
	UEngineSoundPlayer LobbyBGM;
	std::shared_ptr<APlayLobby> PlayLobby = nullptr;

};

