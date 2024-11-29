#include "InGameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include<iostream>
#include<vector>
using namespace std;

InGameManager::InGameManager()
{
    map = {
            "######################",
            "#                                        #",
            "#         ªÔ¥‹¡§∏Æ πÃ¥œ∞‘¿” ∏            #",
            "#                                        #",
            "#   OOOOOO     XXXXXX       ZZZZZZ       #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "######################"
    };
}

InGameManager::~InGameManager()
{
}

const vector<string>& InGameManager::Getmap() const
{
    return map;
}


void InGameManager::InGameDisplay()
{
    vector<string> map = InGameManager::Getmap();
    KeyManager k;
    for (int i = 0; i < map.size(); i++) {
        k.Gotoxy(16,5 + i);
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                cout << "°·";
            }
            else {
                cout << map[i][j];
            }
        }
        
    }

    Block b;
    cout << map[1].size();
    b.GenerateBlock(map[1].size()/2);
    
}
