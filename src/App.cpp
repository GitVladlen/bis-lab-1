#include "App.h"

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

static const char * DEFAULT_DATA_FILE_NAME = "users.txt";

App::App()
    : m_isRunned( false )
{
}

App::~App()
{
}

void App::run()
{
    this->readUsers();

    m_isRunned = true;

    while( m_isRunned == true )
    {
        this->mainMenu();
    }
}

void App::exit()
{
    this->writeUsers();

    m_isRunned = false;
}

void App::mainMenu()
{
    if( m_loggedUserName.empty() == false && this->hasUser( m_loggedUserName ) == false )
    {
        m_loggedUserName = "";
    }

    if( m_loggedUserName.empty() == true )
    {
        this->notLoggedUserMainMenu();
        return;
    }

    const User & loggedUser = this->getLoggedUser();

    if( loggedUser.getIsAdmin() == true )
    {
        this->loggedAdminUserMainMenu();
    }
    else
    {
        this->loggedNotAdminUserMainMenu();
    }
}

void App::notLoggedUserMainMenu()
{
    std::cout << "Main menu:" << std::endl;
    std::cout << " 1. login" << std::endl;
    std::cout << " 2. exit" << std::endl;

    int choice = 0;
    std::cout << "> ";
    std::cin >> choice;

    switch( choice )
    {
    case 1:
        this->login();
        break;
    case 2:
        this->exit();
        break;
    default:
        break;
    }
}

void App::loggedAdminUserMainMenu()
{
    const User & loggedUser = this->getLoggedUser();

    std::cout << "Main menu, user '" << loggedUser.getLogin() << "' (admin):" << std::endl;
    std::cout << " 1. logout" << std::endl;
    std::cout << " 2. change password" << std::endl;

    std::cout << " 5. exit" << std::endl;

    std::cout << "[debug]" << std::endl;
    std::cout << " 6. read users" << std::endl;
    std::cout << " 7. write users" << std::endl;
    std::cout << " 8. print users" << std::endl;
    std::cout << " 9. reset users" << std::endl;

    int choice = 0;
    std::cout << "> ";
    std::cin >> choice;

    switch( choice )
    {
    case 1:
        this->logout();
        break;
    case 2:
        this->changePassword();
        break;

    case 5:
        this->exit();
        break;

    case 6:
        this->readUsers();
        break;
    case 7:
        this->writeUsers();
        break;
    case 8:
        this->printUsers();
        break;
    case 9:
        this->resetUsers();
        break;
    default:
        break;
    }
}

void App::loggedNotAdminUserMainMenu()
{
    const User & loggedUser = this->getLoggedUser();

    std::cout << "Main menu, user '" << loggedUser.getLogin() << "':" << std::endl;
    std::cout << " 1. logout" << std::endl;
    std::cout << " 2. change password" << std::endl;

    std::cout << " 5. exit" << std::endl;

    int choice = 0;
    std::cout << "> ";
    std::cin >> choice;

    switch( choice )
    {
    case 1:
        this->logout();
        break;
    case 2:
        this->changePassword();
        break;

    case 5:
        this->exit();
        break;
    default:
        break;
    }
}

void App::login()
{
    std::string login;
    std::cout << "Enter login: "; 
    std::cin >> login;

    std::vector<User>::iterator itUserFound = std::find_if( m_users.begin(), m_users.end(), [login]( const User & _user )
    {
        return _user.getLogin() == login;
    } );

    if( itUserFound == m_users.end() )
    {
        std::cout << "[WARNING] Have no user with login '" << login << "'" << std::endl;
        return;
    }

    User * user = &(*itUserFound);

    std::string password;
    std::cout << "Enter password: ";
    std::cin >> password;

    if( user->getPassword() != password )
    {
        std::cout << "[WARNING] Invalid password" << std::endl;
        return;
    }

    m_loggedUserName = login;
}

void App::logout()
{
    m_loggedUserName = "";
}

void App::changePassword()
{
    std::string currentPassword;
    std::cout << "Enter current password: ";
    std::cin >> currentPassword;

    User & currentUser = this->getLoggedUser();
    if( currentUser.getPassword() != currentPassword )
    {
        std::cout << "[WARNING] Invalid password" << std::endl;
        return;
    }

    std::string newPassword;
    std::cout << "Enter new password (HERE MUST BE PASSWORD LIMITS, pass len >= 4): ";
    std::cin >> newPassword;

    if( this->checkPassword( newPassword ) == false )
    {
        std::cout << "[WARNING] Invalid password, check password limits" << std::endl;
        return;
    }

    std::string newPasswordRepeat;
    std::cout << "Repeat new password: ";
    std::cin >> newPasswordRepeat;

    if( newPassword != newPasswordRepeat )
    {
        std::cout << "[WARNING] New passwords doesnt match" << std::endl;
        return;
    }

    currentUser.setPassword( newPassword );
}

void App::readUsers()
{
    m_users.clear();

    std::ifstream inFile( DEFAULT_DATA_FILE_NAME );

    std::string line;

    while( std::getline( inFile, line ) )
    {
        std::istringstream iss( line );

        std::string login;
        std::string password;
        bool isAdmin;
        bool isBlocked;

        if( !(iss >> login >> password >> isAdmin >> isBlocked) )
        {
            break;
        } // error

        User user = User();

        user.setLogin( login );
        user.setPassword( password );
        user.setIsAdmin( isAdmin );
        user.setIsBlocked( isBlocked );

        m_users.emplace_back( user );
    }

    inFile.close();
}

void App::writeUsers()
{
    std::ofstream outFile( DEFAULT_DATA_FILE_NAME );

    for( const User & user : m_users )
    {
        outFile << user.toString() << std::endl;
    }

    outFile.close();
}

void App::resetUsers()
{
    m_loggedUserName = "";
    m_users.clear();

    std::ofstream outFile( DEFAULT_DATA_FILE_NAME );

    User admin = User();

    admin.setLogin( "admin" );
    admin.setPassword( "admin" );
    admin.setIsAdmin( true );
    admin.setIsBlocked( false );

    outFile << admin.toString() << std::endl;

    outFile.close();

    this->readUsers();
}

void App::printUsers()
{
    for( const User & user : m_users )
    {
        std::cout << user.toString() << std::endl;
    }
}

bool App::hasUser( const std::string & _userLogin ) const
{
    std::vector<User>::const_iterator itUserFound = std::find_if( m_users.begin(), m_users.end(), [_userLogin]( const User & _user )
    {
        return _user.getLogin() == _userLogin;
    } );

    if( itUserFound == m_users.end() )
    {
        return false;
    }

    return true;
}

User & App::getUser( const std::string & _userLogin )
{
    std::vector<User>::iterator itUserFound = std::find_if( m_users.begin(), m_users.end(), [_userLogin]( const User & _user )
    {
        return _user.getLogin() == _userLogin;
    } );

    return *itUserFound;
}

User & App::getLoggedUser()
{
    return this->getUser( m_loggedUserName );
}

bool App::checkPassword( const std::string & _pass ) const
{
    // dummy check
    if( _pass.length() < 4 )
    {
        return false;
    }

    // todo: implement check according task

    return true;
}
