#include <conio.h>
#include <iostream> 
#include <string>
#include <fstream>
using namespace std;

void main()
{

	setlocale( LC_ALL, "ru" );
	string password = "";
	string login = "";
	bool error;
	bool a = false;
	ofstream account( "cppstudio.txt", ios_base::app );

	cout << "Логин: ";
	cin >> login;

	do
	{
		error = false;

		cout << "Пароль (Наявность букв, цифр и разделительных знаков): ";
		cin >> password;

		for( int i = 0; i < password.length(); i++ )
		{
			if( isdigit( password[i] ) && (password.find( "+" ) != -1 ||
				password.find( "-" ) != -1 ||
				password.find( "*" ) != -1 ||
				password.find( "/" ) != -1 ||
				password.find( "%" ) != -1) )
			{
				a = true;
			}
		}
		if( a == true )
		{
			system( "cls" );
			cout << "Логин: " << login << endl;
			cout << "Пароль: " << password << endl;
			cout << "Регистрация прошла успешно!" << endl;
			account << login << " " << password << endl;
			account.close();
		}
		else
		{
			system( "cls" );
			cout << "Пароль не удовлетворяет условия (Наявность букв, цифр и разделительных знаков)" << endl << endl;
			cout << "Логин: " << login << endl;
			error = true;

		}
	} while( error == true );
	_getch();
}