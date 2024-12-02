#pragma once
#include<vector>
#include<iostream>
#include"Block.h"
using namespace std;
class InGameManager
{
public :
	vector<string> map;
public : 
	InGameManager();
	~InGameManager();

	const vector<string>& Getmap() const;

	void InGameDisplay();
	void RunningGame();
	void DrawMap();

	void UpdateColumns(vector<vector<Block>>& columns, const std::vector<Block>& blocks);
	int CalculateScore(vector<vector<Block>>& columns);
private : 
	
};

