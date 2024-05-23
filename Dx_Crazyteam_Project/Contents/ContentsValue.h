#pragma once

// 서버만 사용하는 수치입니다
namespace ServerNum
{
	// 로비에 들어온 플레이어의 수
	int LobbyPlayerNum = 0;

	// 게임 스테이지에서 추합된 플레이어들의 아이디 모음 (세션토큰으로 분류)
	std::vector<int> PlayerIDs = std::vector<int>();
}