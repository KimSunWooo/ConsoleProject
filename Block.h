#pragma once
#include<iostream>
#include<vector>
#include"color.h"
using namespace std;
class Block
{
protected :
	string color;
	int startX = 19;
	int startY = 6;
	vector<vector<int>> blockShape = { {1,1,1,1}, {1,1,1,1} };
public :
	Block();
	~Block();
	// ��� ����
	void GenerateBlock(int x, int y);
	// ��� ���λ���
	// �߰� �� ����
	vector<string> GetAddColor();
	// �� �߰�
	void SetColor(Color newColor);
	vector<vector<string>> BlockShape();
	// ��� ����(�ı�)
	int DestroyBlock(int level, std::string color);
	// ��� �ϴ�����
	void BlockDown();
	vector<string> DrawBlock(int level);
	vector<string> DrawBlock(Color color);
	
};

