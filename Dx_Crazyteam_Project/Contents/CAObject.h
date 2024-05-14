#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ACAGameMode;
class ACAObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ACAObject();
	~ACAObject();

	// delete Function
	ACAObject(const ACAObject& _Other) = delete;
	ACAObject(ACAObject&& _Other) noexcept = delete;
	ACAObject& operator=(const ACAObject& _Other) = delete;
	ACAObject& operator=(ACAObject&& _Other) noexcept = delete;

	void SetCurGameMode(ACAGameMode* _GameMode)
	{
		CurGameMode = _GameMode;
	}

	ACAGameMode* GetGameMode()
	{
		return CurGameMode;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ACAGameMode* CurGameMode = nullptr;
private:

};

