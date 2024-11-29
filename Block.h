#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Block
{
private :
	string color;
	int startX;
	int startY;
	vector<string> colors = { "red", "blue" };
	vector<string> AddColors = { "yellow", "green", "purple", "white" };
	string blockColor;
	vector<vector<int>> blockShape;
public :
	Block();
	~Block();
	// ��� ����
	void GenerateBlock(int mapX);
	// ��� ���λ���
	// �߰� �� ����
	vector<string> GetAddColor();
	// �� �߰�
	void SetColors(int level);
	vector<vector<string>> BlockShape();
	// ��� ����(�ı�)
	int DestroyBlock(int level, std::string color);
	// ��� �ϴ�����
	void BlockDown();
	
};

