#pragma once
#include <string>

class stringHelper
{
public:
	static std::string GetPlayerName()
	{
		return Name;
	}

	static void SetPlayerName(const std::string& _Name)
	{
		Name = _Name;
	}

	static void SetChat(const std::string& _Chat)
	{
		Chat = _Chat;
	}

	static std::string GetChat()
	{
		return Chat;
	}

protected:

private:

	static std::string Name;
	static std::string Chat;
};

