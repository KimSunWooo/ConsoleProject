#include "Game.h"
#include "MainMenu.h"
#include<iostream>
using namespace std;
Game::Game()
{
}

Game::~Game()
{
	
}

void Game::Start()
{
	cout << "게임이 시작되었습니다." << endl;
	MainMenu();
}
