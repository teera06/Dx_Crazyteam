#pragma once

class ALobbyMainMode;
class AMainGameMode;
class UContentsValue
{
	friend ALobbyMainMode;
	friend AMainGameMode;
private:
	// 서버만 사용하는 수치입니다
	static int LobbyPlayerNum;
	static std::vector<int> PlayerIDs;
private:
	UContentsValue()
	{

	}

	~UContentsValue()
	{

	}
};