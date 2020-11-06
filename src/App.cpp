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
    m_isRunned = true;

    while( m_isRunned == true )
    {
        this->mainMenu();
    }
}

void App::exit()
{
    m_isRunned = false;
}

void App::mainMenu()
{
    std::cout << "Main menu:" << std::endl;
    std::cout << "1. login" << std::endl;
    std::cout << "2. exit" << std::endl;

    std::cout << "3. read (debug)" << std::endl;
    std::cout << "4. write (debug)" << std::endl;

    int choice = 0;
    std::cin >> choice;

    switch( choice )
    {
    case 1:
        this->login();
        break;
    case 2:
        this->exit();
    case 3:
        this->readUsers();
    case 4:
        this->writeUsers();
    default:
        break;
    }
}

void App::login()
{
    std::cout << "Enter login: ";
    std::string login;
    std::cin >> login;

    std::cout << "Enter password: ";
    std::string password;
    std::cin >> password;
}

void App::readUsers()
{
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
    }

    inFile.close();
}

void App::writeUsers()
{
    std::ofstream outFile( DEFAULT_DATA_FILE_NAME, std::ios::app );

    outFile << "Carl pass232*_/" << std::endl;
    outFile << "John 34pass232*_/" << std::endl;

    outFile.close();
}
