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
std::atomic<int> inputKey(-1);  // -1은 키 입력 없음 상태를 나타냄
std::atomic<bool> stopInputThread(false); // 스레드 종료 플래그


// 입력 처리 함수
void HandleInput(KeyManager& k) {
    while (!stopInputThread) { // 종료 플래그가 설정될 때까지 반복
        int key = k.HandleKey(); // 키 입력 감지
        inputKey.store(key, std::memory_order_relaxed); // 입력 값을 저장
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 입력 처리 속도 조절
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

    std::vector<Block> blocks; // 현재 블록들
    int mapX = 42;             // 맵의 가로 크기
    int blockWidth = (mapX - 2) / 3; // 블록 너비
    int gap = 1;                     // 블록 간 간격
    int startY = 7;                  // 초기 Y 좌표

    // 첫 번째 줄 블록 초기화
    for (int i = 0; i < 3; ++i) {
        Block b;
        int startX = 35 + i * (blockWidth + gap); // X 위치 계산
        b.GenerateBlock(startX, startY);
        Color color = selector.GetColor(1);      // 난수 기반 색상 선택
        b.SetColor(color);
        blocks.push_back(b); // 블록 추가
    }

    // 타이머 설정
    auto lastMoveTime = std::chrono::steady_clock::now();
    const int autoMoveInterval = 1000; // 자동 이동 간격 (밀리초)

    std::thread inputThread(HandleInput, std::ref(k));
    // 게임 루프
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();

        // 1. 사용자 입력 처리
        int key = inputKey.exchange(-1, std::memory_order_relaxed); // 입력 값을 읽고 초기화
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
                Block b;
                int startX = 35 + i * (blockWidth + gap); // X 위치 계산
                b.GenerateBlock(startX, startY);         // 새로운 블록의 초기 위치
                Color color = selector.GetColor(1);      // 난수 기반 색상 선택
                b.SetColor(color);                       // 색상 설정
                blocks.push_back(b); // 새로운 블록 추가
            }

            lastMoveTime = currentTime; // 마지막 이동 시간 갱신
        }

        // 3. 블록 출력
        for (auto& block : blocks) {
            block.DrawBlock(1); // 블록 출력
        }

        // 4. 대기 시간 (루프 속도 조절)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
