#pragma once

#include "User.h"
#include <vector>

/*
password limits:
	- contain latin letters, digits and punctuation marks ("",.;:!?)(\/")

user:
	- bool is_admin
	- bool is_blocked

	- string login (unique)
	- string password (empty on create)

app:
	- login (with retry)
	- change pass (all)
	- list all users (admin)
		- block/unblock user
		- enable/disable password limit (limit by variant 5)
		- add new unique user (with empty password)
	- exit
*/

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
	void listUsers();

    void blockUser();
    void unblockUser();
    void enableCheckUserPassword();
    void disableCheckUserPassword();
    void createNewUser();

protected: // debug
	void readUsers();
	void writeUsers();
	
	void resetUsers();
	void printUsers();

protected:
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
