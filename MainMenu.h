#pragma once
class MainMenu
{
public : 
	MainMenu();
	~MainMenu();

	void DrawMainTitle();
	void DrawMainMenu();

	// ���κ����� �޴� y ���� ���� �޴� ����.
	void SelectMenu(int mNum);

	void PlayGame();
	int Quit();
};

