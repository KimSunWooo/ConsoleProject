#include"Game.h"
#include<Windows.h>
#include <locale>


int main() {
	
	
	Game* g = new Game();
	g->Start();
	delete g;
	return 0;
}