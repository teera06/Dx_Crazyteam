#pragma once
#include <Enginecore/Actor.h>

class UTextWidget;

class AFontActor : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AFontActor(); // 디폴트 생성자
	~AFontActor(); // 디폴트 소멸자

	// delete Function
	AFontActor(const AFontActor& _Other) = delete; // 디폴트 복사 생성자
	AFontActor(AFontActor&& _Other) noexcept = delete; 
	AFontActor& operator=(const AFontActor& _Other) = delete; // 디폴트 대입 연산자
	AFontActor& operator=(AFontActor&& _Other) noexcept = delete;

	UTextWidget* GetShowText()
	{
		return ShowText;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	UTextWidget* ShowText = nullptr;
};

