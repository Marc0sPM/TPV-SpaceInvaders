#pragma once
#include <string>
class MainMenuState
{
private:
	static const std::string s_menuID;

public:

	virtual void render() const;
	virtual void update();
};

