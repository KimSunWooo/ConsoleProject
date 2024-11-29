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
                cout << "■";
            }
            else {
                cout << map[i][j];
            }
        }
        
    }

    ColorSelector selector;
    vector<Color> recentColors;
    // 한 줄의 블록 생성
    vector<Block> blocks; // 한 줄에 들어갈 블록들
    int mapX = 42;        // 맵의 가로 크기
    int blockWidth = (mapX - 2) / 3; // 블록 너비
    int gap = 1;                     // 블록 간 간격
    int startY = 7;                  // 블록 줄의 Y 좌표

    // 블록 생성 및 위치 설정
    // 이게원본
    for (int i = 0; i < 3; ++i) { // 한 줄에 블록 3개
        Block b;
        int startX = 35 + i * (blockWidth + gap); // X 위치 계산
        b.GenerateBlock(startX, startY);
        blocks.push_back(b);
    }

    //// 수정본 (테스트 중)
    //for (int i = 0; i < 3; ++i) { // 3개의 블록 생성
    //    Block b;

    //    int startX = 16 + i * (blockWidth + gap); // X 위치 계산

    //    // 조건 위반 방지 색상 선택
    //    Color color = selector.GetColor(1);
    //    recentColors.push_back(color); // 선택된 색상 추가

    //    // 최근 색상 목록 유지 (최대 2개)
    //    if (recentColors.size() > 2) {
    //        recentColors.erase(recentColors.begin());
    //    }

    //    b.GenerateBlock(startX, startY);
    //    b.SetColor(color); // 블록에 색상 설정
    //    blocks.push_back(b);
    //}
    
    // 블록 출력
    for (auto& block : blocks) {
        // 아래는 레벨 구현 후 코드
        //if (level < 5) {
        //    block.DrawBlock(5); // 레벨 1로 출력
        //}
        //else {
        //    block.DrawBlock(level); // 레벨 1로 출력
        //}
        block.DrawBlock(1); // 레벨 1로 출력
    }
}
