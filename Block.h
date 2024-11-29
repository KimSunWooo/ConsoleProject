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
	// 블록 생성
	void GenerateBlock(int mapX);
	// 블록 라인생성
	// 추가 색 선택
	vector<string> GetAddColor();
	// 색 추가
	void SetColors(int level);
	vector<vector<string>> BlockShape();
	// 블록 제거(파괴)
	int DestroyBlock(int level, std::string color);
	// 블록 하단진행
	void BlockDown();
	
};

