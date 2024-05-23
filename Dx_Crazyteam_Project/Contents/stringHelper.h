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

protected:

private:

	static std::string Name;
};

