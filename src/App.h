#pragma once

#include "User.h"
#include <vector>

class App
{
public:
	App();
	~App();

public:
	void run();
	void exit();

protected:
	void mainMenu();
	void login();

protected:
	void readUsers();
	void writeUsers();

private:
	bool m_isRunned;

private:
	typedef std::vector<User> VectorUsers;

	VectorUsers m_users;
};
