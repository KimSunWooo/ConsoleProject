#include "ColorSelector.h"
#include<iostream>
using namespace std;
int main1() {
	srand(std::time(nullptr));
	ColorSelector::GetColor(1);

	int ran;

	for (int i = 0; i < 10; i++) {
		ran = rand() % 3;
		cout << ran << endl;
	}
}