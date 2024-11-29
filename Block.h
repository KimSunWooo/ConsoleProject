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
	// 블록 생성
	void GenerateBlock(int x, int y);
	// 블록 라인생성
	// 추가 색 선택
	vector<string> GetAddColor();
	// 색 추가
	void SetColor(Color newColor);
	vector<vector<string>> BlockShape();
	// 블록 제거(파괴)
	int DestroyBlock(int level, std::string color);
	// 블록 하단진행
	void BlockDown();
	vector<string> DrawBlock(int level);
	vector<string> DrawBlock(Color color);
	
};

