#pragma once
#include "Bush.h"

// Ό³Έν :
class ATownBush : public ABush
{
	GENERATED_BODY(ABush)
public:
	// constructor destructor
	ATownBush();
	~ATownBush();

	// delete Function
	ATownBush(const ATownBush& _Other) = delete;
	ATownBush(ATownBush&& _Other) noexcept = delete;
	ATownBush& operator=(const ATownBush& _Other) = delete;
	ATownBush& operator=(ATownBush&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

