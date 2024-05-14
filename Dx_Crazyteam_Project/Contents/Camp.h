#pragma once
#include "BaseMap.h"

// Ό³Έν :
class ACamp : public ABaseMap
{
	GENERATED_BODY(ABaseMap);
public:
	// constructor destructor
	ACamp();
	~ACamp();

	// delete Function
	ACamp(const ACamp& _Other) = delete;
	ACamp(ACamp&& _Other) noexcept = delete;
	ACamp& operator=(const ACamp& _Other) = delete;
	ACamp& operator=(ACamp&& _Other) noexcept = delete;

	void AddObjectInit();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

