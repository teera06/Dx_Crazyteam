#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class UTextWidget;
class UImage;
class AOtherPlayer : public AActor, public UNetObject
{
public:
	// constrcuter destructer
	AOtherPlayer();
	~AOtherPlayer();

	// delete Function
	AOtherPlayer(const AOtherPlayer& _Other) = delete;
	AOtherPlayer(AOtherPlayer&& _Other) noexcept = delete;
	AOtherPlayer& operator=(const AOtherPlayer& _Other) = delete;
	AOtherPlayer& operator=(AOtherPlayer&& _Other) noexcept = delete;

	inline bool IsOtherPlayerDestroy() const
	{
		return IsOPDestroy;
	}

	inline ETeamType GetTeamType() const 
	{
		return TeamType;
	}

	inline ECharacterType GetCharacterType() const
	{
		return CharacterType;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart();
	void Idle(float _DeltaTime);

	void MoveStart();
	void Move(float _DeltaTime);

private:
	UStateManager State;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UTextWidget* PlayerNameUI = nullptr;

	UTextWidget* NameListUI = nullptr;
	UImage* PlayerListUI = nullptr;

	bool IsOPDestroy = false;
	bool TempBool = false;
	ETeamType TeamType = ETeamType::None;
	ECharacterType CharacterType = ECharacterType::None;

	int SessionToken = -1;
};

