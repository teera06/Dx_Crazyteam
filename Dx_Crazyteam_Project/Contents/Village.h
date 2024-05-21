#pragma once
#include "BaseMap.h"

// Ό³Έν :
class AVillage : public ABaseMap
{
	GENERATED_BODY(ABaseMap)
public:
	// constructor destructor
	AVillage();
	~AVillage();

	// delete Function
	AVillage(const AVillage& _Other) = delete;
	AVillage(AVillage&& _Other) noexcept = delete;
	AVillage& operator=(const AVillage& _Other) = delete;
	AVillage& operator=(AVillage&& _Other) noexcept = delete;

	void AddObjectInit();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

