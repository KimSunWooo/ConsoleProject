#include "InGameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include "Color.h"
#include "ColorSelector.h"
#include<iostream>
#include<vector>
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds
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
    
    // 중복검사
    //for (auto& block : blocks) {
    //    ColorSelector c;
    //    vector<Color> usedColor;
    //    Color color = c.GetColor(1);
    //    int cnt = 0;
    //    for (int i = 0; i < usedColor.size(); i++) {
    //        if (find(usedColor.begin(), usedColor.end(), color) != usedColor.end()) {
    //            cnt++;
    //        }
    //        
    //    }
    //    
    //    block.DrawBlock(color);
    //}

    
}

void InGameManager::RunningGame() {
    ColorSelector selector;
    std::vector<Block> blocks; // 현재 블록들

    // 초기 블록 생성
    int mapX = 42;             // 맵의 가로 크기
    int blockWidth = (mapX - 2) / 3; // 블록 너비
    int gap = 1;                     // 블록 간 간격
    int startY = 7;                  // 블록 줄의 Y 좌표

    for (int i = 0; i < 3; ++i) { // 초기 3개의 블록 생성
        Block b;
        int startX = 35 + i * (blockWidth + gap); // X 위치 계산
        b.GenerateBlock(startX, startY);
        Color color = selector.GetColor(1); // 색상 선택
        b.SetColor(color); // 색상 설정
        blocks.push_back(b);
    }

    // 게임 루프
    while (true) {
        // 1. 기존 블록 이동
        for (auto& block : blocks) {
            block.BlockDown(); // 블록을 아래로 이동
            block.DrawBlock(1); // 이동된 위치에 블록 출력
        }

        // 2. 새로운 블록 생성
        blocks.clear(); // 이전 블록 제거
        for (int i = 0; i < 3; ++i) {
            Block b;
            int startX = 35 + i * (blockWidth + gap);
            b.GenerateBlock(startX, startY);
            Color color = selector.GetColor(1);
            b.SetColor(color);
            blocks.push_back(b);
        }

        // 3. 대기 시간 (3초)
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // 콘솔 초기화 (선택 사항)
        std::cout << "\033[H"; // 커서를 맨 위로 이동
        DrawMap(); // 맵 다시 그리기
    }
}

void InGameManager::DrawMap() {
    //for (int i = 0; i < map.size(); ++i) {
    //    std::cout << "\033[" << (5 + i) << ";16H"; // 맵의 시작 위치 (16, 5)
    //    for (char c : map[i]) {
    //        if (c == '#') {
    //            std::cout << "\033[37m■\033[0m"; // 흰색 블록으로 출력
    //        }
    //        else {
    //            std::cout << c;
    //        }
    //    }
    //}
    KeyManager k;
    for (int i = 0; i < map.size(); i++) {
        k.Gotoxy(16, 5 + i);
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '#') {
                cout << "■";
            }
            else {
                cout << map[i][j];
            }
        }

    }
    std::cout.flush(); // 출력 버퍼 비우기
}
