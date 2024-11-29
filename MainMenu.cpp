#include "MainMenu.h"
#include "KeyEnum.h"
#include "KeyManager.h"
#include "InGameManager.h"
#include<iostream>

using namespace std;
KeyManager k;

MainMenu::MainMenu()
{
	srand(static_cast<unsigned>(time(nullptr)));
	system("mode con: cols=120 lines=60 | title Console_Project");
	DrawMainTitle();
	DrawMainMenu();

}

MainMenu::~MainMenu()
{
	
}

void MainMenu::DrawMainTitle()
{
	cout << "\n\n\n\n" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "############            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
	cout << "#          #            ##         ########################################################" << endl;
}

void MainMenu::DrawMainMenu()
{
	int x = 24;
	int y = 15;
	k.Gotoxy(x - 2, y);
	cout << ">   게임시작" << endl;
	k.Gotoxy(x, y+1);
	cout << "게임정보" << endl;
	k.Gotoxy(x, y+2);
	cout << "종료" << endl;

	while (1)
	{
		int n = k.HandleKey();
		
			switch (n)
			{
			case UP :
				
				if (y > 15) {
					k.Gotoxy(x - 2, y);
					cout << " " << endl;
					k.Gotoxy(x - 2, --y);
					cout << ">" << endl;
				}
				continue;
			case DOWN :
				
				if (y < 17) {
					k.Gotoxy(x - 2, y);
					cout << " " << endl;
					k.Gotoxy(x - 2, ++y);
					cout << ">" << endl;
				} 
				continue;
			case SPACE :
				
				return SelectMenu(y);
				break;
			}
		
	}
}

void MainMenu::SelectMenu(int y)
{
	switch (y)
	{
	case 15 : 
		system("cls");
		
		return PlayGame();
	case 16 : 
		break;
	case 17 : 

		Quit();
		break;
	}
}

void MainMenu::PlayGame()
{
	//게임 시작.
	InGameManager ig;
	ig.InGameDisplay();
}

int MainMenu::Quit()
{
	return -1;
}

