#pragma once
class MainMenu
{
public : 
	MainMenu();
	~MainMenu();

	void DrawMainTitle();
	void DrawMainMenu();

	// 메인베뉴의 메뉴 y 값에 따라 메뉴 실행.
	void SelectMenu(int mNum);

	void PlayGame();
	int Quit();
};

