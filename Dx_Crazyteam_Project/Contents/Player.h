#pragma once
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsEnum.h"
#include "CAObject.h"
#include "NetInterface.h"

class APlayer;
class PlayerInfo
{
	friend APlayer;

public:
	POINT CurIndex = POINT(0, 0);
	ECharacterType MyType = ECharacterType::Bazzi;
	ETeamType Team = ETeamType::None;
	float MoveSpeed = 100.f;
	int WBPower = 4;				// ¹°ÆøÅº ÆÄ¿ö(¹°ÁÙ±â ±æÀÌ)
	int WBCount = 4;				// ¹°ÆøÅº °³¼ö	
};

class APlayer_Shadow;

class APlayer : public ACAObject
{
	GENERATED_BODY(ACAObject)
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;
	
	void SetCharacterType(ECharacterType _Type);
	void SetTeamType(ETeamType _Team)
	{
		Info->Team = _Team;
	}

	PlayerInfo* GetPlayerInfo()
	{
		return Info.get();
	}

protected:
	std::shared_ptr<PlayerInfo> Info = nullptr;
	UStateManager State;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	void StateInit();

	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	void TrapStart();
	void Trap(float _DeltaTime);
	void RescueStart();
	void Rescue(float _DeltaTime);
	void DieStart();
	void Die(float _DeltaTime);

	std::string GetAnimationName(std::string_view _StateName);

	FVector Dir = FVector::Down;
	float AnimationInter = 0.1f;
	float TrapMoveSpeed = 0.4f;
	float TrapMoveTime = 1.f;
	float TrapAnimationTime = 3.f;
	float TrapToDieTime = 5.f;
	FVector TrapDir = FVector::Up;

	std::shared_ptr<APlayer_Shadow> Shadow = nullptr;


	static int WaterBomb_Token;

};


