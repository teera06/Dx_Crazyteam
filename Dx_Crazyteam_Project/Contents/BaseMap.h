#pragma once
#include <EngineCore/Actor.h>

enum class EMapObjectType {
	Block,   //움직이지도 부서지지도 않는 블록
	BrakableBlock,   //부서지는 블록
	MoveBlock,     //움직이는 블록
	Bush,          //부시
	WaterBalloon,  //물풍선
};

// 설명 :
class UEngineTexture;
class UDefaultSceneComponent;
class AMapObject;
class ABaseMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ABaseMap();
	~ABaseMap();

	// delete Function
	ABaseMap(const ABaseMap& _Other) = delete;
	ABaseMap(ABaseMap&& _Other) noexcept = delete;
	ABaseMap& operator=(const ABaseMap& _Other) = delete;
	ABaseMap& operator=(ABaseMap&& _Other) noexcept = delete;

	static bool IsMove(FVector _PlayerPos);
	static const FVector TileSize;
	static const int TileY;
	static const int TileX;
	
	void AddMapObject(int _Y, int _X, EMapObjectType _MapObjectType);

	static std::pair<int,int> PlayerPosToPoint(FVector _PlayerPos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	USpriteRenderer* BackMap = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	std::vector<std::vector<std::shared_ptr<AMapObject>>> MapStatus;
private:

};

