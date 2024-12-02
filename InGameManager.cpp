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

        // 1. 사용자 입력 처리
        int key = inputKey.exchange(-1, memory_order_relaxed); // 입력 값을 읽고 초기화
        if (key == DOWN) {
            std::cout << "DOWN key pressed" << std::endl;
            for (auto& block : blocks) {
                block.BlockDown(startY, selector); // 블록을 아래로 이동
            }
        }

        // 2. 자동 이동 처리
        if (elapsedTime >= autoMoveInterval) {
            
            for (auto& block : blocks) {
                block.BlockDown(startY, selector); // 기존 블록 이동
            }

            // 새로운 블록 추가
            for (int i = 0; i < 3; ++i) {
                Block::GenerateBlockLine(blocks, columns[i], selector, blockWidth, gap, startY, i);
            }

            lastMoveTime = currentTime; // 마지막 이동 시간 갱신
        }

        // 3. 세로줄 업데이트
        UpdateColumns(columns, blocks);

        // 4. 점수 계산 및 블록 제거
        score += CalculateScore(columns);
        cout << score << endl;

        // 3. 블록 출력
        for (auto& block : blocks) {
            block.DrawBlock(1); // 블록 출력
        }

        // 4. 대기 시간 (루프 속도 조절)
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
    cout << "세로줄 업데이트" << endl;
    // 각 세로줄 초기화
    for (auto& column : columns) {
        column.clear();
    }

    // 블록을 세로줄에 분류
    for (const auto& block : blocks) {
        cout << block.GetX() << endl;
        int columnIndex = (block.GetX()) / 3; // X 좌표에 따라 세로줄 결정
        if (columnIndex >= 0 && columnIndex < columns.size()) {
            columns[columnIndex].push_back(block);
        }
    }
}

int InGameManager::CalculateScore(vector<vector<Block>>& columns)
{
    cout << "점수 업데이트" << endl;
    int score = 0;

    for (auto& column : columns) {
        // 세로줄에서 3개 연속 같은 색상 찾기
        for (size_t i = 0; i < column.size(); ) {
            size_t count = 1;
            while (i + count < column.size() && column[i].GetColor() == column[i + count].GetColor()) {
                ++count;
            }

            if (count == 3) {
                // 3개 이상의 연속된 블록 제거
                cout << "점수계산" << endl;
                score += count;
                column.erase(column.begin() + i, column.begin() + i + count);
            }
            else {
                ++i;
            }
        }
    }

    return score;
}




