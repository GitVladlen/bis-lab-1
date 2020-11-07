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

	void notLoggedUserMainMenu();
	void loggedAdminUserMainMenu();
	void loggedNotAdminUserMainMenu();

	void login();
	void logout();

	void changePassword();

protected:
	void readUsers();
	void writeUsers();
	
	void resetUsers();
	void printUsers();

	bool hasUser( const std::string & _userLogin ) const;
	User & getUser( const std::string & _userLogin );
	User & getLoggedUser();

	bool checkPassword( const std::string & _pass ) const;

private:
	bool m_isRunned;

private:
	std::string m_loggedUserName;
	std::vector<User> m_users;
};
