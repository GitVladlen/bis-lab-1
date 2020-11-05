#include <conio.h>
#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

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


#include "App.h"

void main()
{
	App app = App();
	app.run();

	//setlocale( LC_ALL, "ru" );
	//string password = "";
	//string login = "";
	//bool error;
	//bool a = false;
	//ofstream account( "cppstudio.txt", ios_base::app );

	//cout << "Логин: ";
	//cin >> login;

	//do
	//{
	//	error = false;

	//	cout << "Пароль (Наявность букв, цифр и разделительных знаков): ";
	//	cin >> password;

	//	for( int i = 0; i < password.length(); i++ )
	//	{
	//		if( isdigit( password[i] ) && (password.find( "+" ) != -1 ||
	//			password.find( "-" ) != -1 ||
	//			password.find( "*" ) != -1 ||
	//			password.find( "/" ) != -1 ||
	//			password.find( "%" ) != -1) )
	//		{
	//			a = true;
	//		}
	//	}
	//	if( a == true )
	//	{
	//		system( "cls" );
	//		cout << "Логин: " << login << endl;
	//		cout << "Пароль: " << password << endl;
	//		cout << "Регистрация прошла успешно!" << endl;
	//		account << login << " " << password << endl;
	//		account.close();
	//	}
	//	else
	//	{
	//		system( "cls" );
	//		cout << "Пароль не удовлетворяет условия (Наявность букв, цифр и разделительных знаков)" << endl << endl;
	//		cout << "Логин: " << login << endl;
	//		error = true;

	//	}
	//} while( error == true );
	//_getch();
}