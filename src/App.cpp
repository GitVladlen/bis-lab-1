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

    std::cout << "[debug]" << std::endl;
    std::cout << " 11. read users" << std::endl;
    std::cout << " 12. write users" << std::endl;
    std::cout << " 13. print users" << std::endl;
    std::cout << " 14. reset users" << std::endl;

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

    case 11:
        this->readUsers();
        break;
    case 12:
        this->writeUsers();
        break;
    case 13:
        this->printUsers();
        break;
    case 14:
        this->resetUsers();
        break;

    default:
        break;
    }
}

void App::loggedAdminUserMainMenu()
{
    const User & loggedUser = this->getLoggedUser();

    if( loggedUser.getIsBlocked() == true )
    {
        std::cout << "[WARNING] User '" << loggedUser.getLogin() << "' is blocked" << std::endl;
        this->logout();
        return;
    }

    std::cout << "Main menu, user '" << loggedUser.getLogin() << "' (admin):" << std::endl;
    std::cout << " 1. logout" << std::endl;
    std::cout << " 2. change password" << std::endl;
    std::cout << " 3. list users" << std::endl;

    std::cout << " 4. block user" << std::endl;
    std::cout << " 5. unblock user" << std::endl;
    std::cout << " 6. enable user password check" << std::endl;
    std::cout << " 7. disable user password check" << std::endl;
    std::cout << " 8. enable admin user" << std::endl;
    std::cout << " 9. disable admin user" << std::endl;
    std::cout << " 10. create new user" << std::endl;

    std::cout << " 11. exit" << std::endl;

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
    case 3:
        this->listUsers();
        break;

    case 4:
        this->blockUser();
        break;
    case 5:
        this->unblockUser();
        break;
    case 6:
        this->enableCheckUserPassword();
        break;
    case 7:
        this->disableCheckUserPassword();
        break;
    case 8:
        this->enableAdminUser();
        break;
    case 9:
        this->disableAdminUser();
        break;
    case 10:
        this->createNewUser();
        break;

    case 11:
        this->exit();
        break;

    default:
        break;
    }
}

void App::loggedNotAdminUserMainMenu()
{
    const User & loggedUser = this->getLoggedUser();

    if( loggedUser.getIsBlocked() == true )
    {
        std::cout << "[WARNING] User '" << loggedUser.getLogin() << "' is blocked" << std::endl;
        this->logout();
        return;
    }

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

    if( user->getIsBlocked() == true )
    {
        std::cout << "[WARNING] User '" << login << "' is blocked";
        return;
    }

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
    std::cout << "Enter new password (letters, digits, punctuation marks): ";
    std::cin >> newPassword;

    if( currentUser.getIsPasswordCheck() == true &&  this->checkPassword( newPassword ) == false )
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

void App::listUsers()
{
    for( const User & user : m_users )
    {
        std::cout << user.getLogin() << std::endl;
    }
}

void App::blockUser()
{
    std::string userLogin;
    std::cout << "User login to block: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsBlocked( true );

    this->writeUsers();

    std::cout << "User with login '" << userLogin << "' is successfully blocked" << std::endl;
}

void App::unblockUser()
{
    std::string userLogin;
    std::cout << "User login to unblock: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsBlocked( false );

    this->writeUsers();
 
    std::cout << "User with login '" << userLogin << "' is successfully unblocked" << std::endl;
}

void App::enableCheckUserPassword()
{
    std::string userLogin;
    std::cout << "User login to enable password check: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsPasswordCheck( true );

    this->writeUsers();

    std::cout << "User with login '" << userLogin << "' is successfully enable password check" << std::endl;
}

void App::disableCheckUserPassword()
{
    std::string userLogin;
    std::cout << "User login to disable password check: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsPasswordCheck( false );

    this->writeUsers();

    std::cout << "User with login '" << userLogin << "' is successfully disable password check" << std::endl;
}

void App::enableAdminUser()
{
    std::string userLogin;
    std::cout << "User login to enable admin: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsAdmin( true);

    this->writeUsers();

    std::cout << "User with login '" << userLogin << "' is successfully enabled admin" << std::endl;
}

void App::disableAdminUser()
{
    std::string userLogin;
    std::cout << "User login to disable admin: ";
    std::cin >> userLogin;

    if( this->hasUser( userLogin ) == false )
    {
        std::cout << "[WARNING] Has no user with login'" << userLogin << "'" << std::endl;
        return;
    }

    User & user = this->getUser( userLogin );

    user.setIsAdmin( false );

    this->writeUsers();

    std::cout << "User with login '" << userLogin << "' is successfully disabled admin" << std::endl;
}

void App::createNewUser()
{
    // todo: implement this
    std::string login;
    std::cout << "Enter new user login: ";
    std::cin >> login;

    if( this->hasUser( login ) == true )
    {
        std::cout << "[WARNING] User with login '" << login << "' already exists" << std::endl;
        return;
    }

    User user = User();

    user.setLogin( login );
    user.setPassword( "user" ); // default password for user
    user.setIsAdmin( false );
    user.setIsBlocked( false );

    m_users.emplace_back( user );

    this->writeUsers();

    std::cout << "User with login '" << login << "' is successfully created" << std::endl;
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
        std::cout << user.toStringDebug() << std::endl;
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
    if( _pass.length() < 3 )
    {
        return false;
    }

    // must contain latin letters, digits and punctuation marks( "", .; :!? )(\ / ")

    bool hasLatinLetters = false;
    bool hasDigits = false;
    bool hasPunctuationMarks = false;

    for( int32_t i = 0; i < _pass.length(); ++i )
    {
        char ch = _pass[i];
        if( isalpha( ch ) != 0 )
        {
            hasLatinLetters = true;
        }
        else if( isdigit( ch ) != 0 )
        {
            hasDigits = true;
        }
        else if( ispunct( ch ) != 0 )
        {
            hasPunctuationMarks = true;
        }
    }

    if( hasLatinLetters == false )
    {
        return false;
    }

    if( hasDigits == false )
    {
        return false;
    }

    if( hasPunctuationMarks == false )
    {
        return false;
    }

    return true;
}
