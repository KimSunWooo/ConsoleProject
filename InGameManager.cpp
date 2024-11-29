#include "InGameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include "Color.h"
#include "ColorSelector.h"
#include<iostream>
#include<vector>
using namespace std;

InGameManager::InGameManager()
{
    map = {
            "######################",
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
                cout << "��";
            }
            else {
                cout << map[i][j];
            }
        }
        
    }

    ColorSelector selector;
    vector<Color> recentColors;
    // �� ���� ��� ����
    vector<Block> blocks; // �� �ٿ� �� ��ϵ�
    int mapX = 42;        // ���� ���� ũ��
    int blockWidth = (mapX - 2) / 3; // ��� �ʺ�
    int gap = 1;                     // ��� �� ����
    int startY = 7;                  // ��� ���� Y ��ǥ

    // ��� ���� �� ��ġ ����
    // �̰Կ���
    for (int i = 0; i < 3; ++i) { // �� �ٿ� ��� 3��
        Block b;
        int startX = 35 + i * (blockWidth + gap); // X ��ġ ���
        b.GenerateBlock(startX, startY);
        blocks.push_back(b);
    }

    //// ������ (�׽�Ʈ ��)
    //for (int i = 0; i < 3; ++i) { // 3���� ��� ����
    //    Block b;

    //    int startX = 16 + i * (blockWidth + gap); // X ��ġ ���

    //    // ���� ���� ���� ���� ����
    //    Color color = selector.GetColor(1);
    //    recentColors.push_back(color); // ���õ� ���� �߰�

    //    // �ֱ� ���� ��� ���� (�ִ� 2��)
    //    if (recentColors.size() > 2) {
    //        recentColors.erase(recentColors.begin());
    //    }

    //    b.GenerateBlock(startX, startY);
    //    b.SetColor(color); // ��Ͽ� ���� ����
    //    blocks.push_back(b);
    //}
    
    // ��� ���
    for (auto& block : blocks) {
        // �Ʒ��� ���� ���� �� �ڵ�
        //if (level < 5) {
        //    block.DrawBlock(5); // ���� 1�� ���
        //}
        //else {
        //    block.DrawBlock(level); // ���� 1�� ���
        //}
        block.DrawBlock(1); // ���� 1�� ���
    }
}
