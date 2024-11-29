#pragma once
#include<vector>
#include<iostream>
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

private : 
	
};

