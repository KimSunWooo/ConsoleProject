#include "InGameManager.h"
#include "KeyManager.h"
#include "Block.h"
#include "Color.h"
#include "ColorSelector.h"
#include<iostream>
#include<vector>
#include <thread>   
#include <chrono>   
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
            "#                                        #",
            "#                                        #",
            "#                                        #",
            "######################"
    };
}

InGameManager::~InGameManager()
{
}

// 공유 변수로 입력 값을 저장
atomic<int> inputKey(-1);  // -1은 키 입력 없음 상태를 나타냄
atomic<bool> stopInputThread(false); // 스레드 종료 플래그

// 입력 처리 함수
void HandleInput(KeyManager& k) {
    while (!stopInputThread) { // 종료 플래그가 설정될 때까지 반복
        int key = k.HandleKey(); // 키 입력 감지
        inputKey.store(key, std::memory_order_relaxed); // 입력 값을 저장
        this_thread::sleep_for(chrono::milliseconds(50)); // 입력 처리 속도 조절
    }
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
}

// 게임 루프
void InGameManager::RunningGame() {
    ColorSelector selector;
    KeyManager k;
    

    vector<Block> blocks; // 생성되는 블록들
    vector<vector<Block>> columns(3); // 블록 세로줄 (터칠 블록 계산)
    int mapX = 42;             // 맵의 가로 크기
    int blockWidth = (mapX - 2) / 3; // 블록 너비
    int gap = 1;                     // 블록 간 간격
    int startY = 7;                  // 초기 Y 좌표
    int score = 0;

    // 첫 번째 줄 블록 초기화
    for (int i = 0; i < 3; ++i) {
        Block::GenerateBlockLine(blocks, columns[i], selector, blockWidth, gap, startY, i);
    }

    // 타이머 설정
    auto lastMoveTime = chrono::steady_clock::now();
    const int autoMoveInterval = 1000; // 자동 이동 간격 (밀리초)

    std::thread inputThread(HandleInput, std::ref(k));
    // 게임 루프
    while (true) {
        auto currentTime = chrono::steady_clock::now();
        int elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastMoveTime).count();

        // 사용자 입력 처리
        int key = inputKey.exchange(-1, memory_order_relaxed);
        if (key == DOWN) {
            for (auto& block : blocks) {
                block.BlockDown(startY, selector);
            }
            UpdateColumns(columns, blocks);
        }

        // 자동 이동 처리
        if (elapsedTime >= autoMoveInterval) {
            for (auto& block : blocks) {
                block.BlockDown(startY, selector);
            }
            for (int i = 0; i < 3; ++i) {
                Block::GenerateBlockLine(blocks, columns[i], selector, blockWidth, gap, startY, i);
            }
            UpdateColumns(columns, blocks);
            lastMoveTime = currentTime;
        }

        // 점수 계산 및 블록 제거
        score += CalculateScore(columns);
        Block::RemoveMatchingBlocks(columns, blocks);

        // 블록 다시 출력
        for (auto& block : blocks) {
            block.DrawBlock(1);
        }

        // 루프 속도 조절
        this_thread::sleep_for(chrono::milliseconds(50));
    }
        stopInputThread = true;
        inputThread.join();

}



void InGameManager::DrawMap() {

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

void InGameManager::UpdateColumns(vector<vector<Block>>& columns, const std::vector<Block>& blocks)
{
    // 각 세로줄 초기화
    for (auto& column : columns) {
        column.clear();
        
    }

    for (auto& column : columns) {

       cout << "column " << column.size() << endl;

    }
}

int InGameManager::CalculateScore(const vector<vector<Block>>& columns) {
    int score = 0;

    for (const auto& column : columns) {
        if (column.size() >= 3) { // 세로줄에 블록이 3개 이상인 경우
            // 최하단 3개의 블록이 같은 색상인지 확인
            auto color1 = column[column.size() - 1].GetColor();
            auto color2 = column[column.size() - 2].GetColor();
            auto color3 = column[column.size() - 3].GetColor();

            if (color1 == color2 && color2 == color3) {
                score += 100; // 같은 색상 블록이 3개 이상이면 점수 추가
            }
        }
        
    }

    return score;
}




