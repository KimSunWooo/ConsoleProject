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

// ���� ������ �Է� ���� ����
std::atomic<int> inputKey(-1);  // -1�� Ű �Է� ���� ���¸� ��Ÿ��
std::atomic<bool> stopInputThread(false); // ������ ���� �÷���


// �Է� ó�� �Լ�
void HandleInput(KeyManager& k) {
    while (!stopInputThread) { // ���� �÷��װ� ������ ������ �ݺ�
        int key = k.HandleKey(); // Ű �Է� ����
        inputKey.store(key, std::memory_order_relaxed); // �Է� ���� ����
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // �Է� ó�� �ӵ� ����
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
                cout << "��";
            }
            else {
                cout << map[i][j];
            }
        }
        
    }
}

// ���� ����
void InGameManager::RunningGame() {
    ColorSelector selector;
    KeyManager k;

    std::vector<Block> blocks; // ���� ��ϵ�
    int mapX = 42;             // ���� ���� ũ��
    int blockWidth = (mapX - 2) / 3; // ��� �ʺ�
    int gap = 1;                     // ��� �� ����
    int startY = 7;                  // �ʱ� Y ��ǥ

    // ù ��° �� ��� �ʱ�ȭ
    for (int i = 0; i < 3; ++i) {
        Block b;
        int startX = 35 + i * (blockWidth + gap); // X ��ġ ���
        b.GenerateBlock(startX, startY);
        Color color = selector.GetColor(1);      // ���� ��� ���� ����
        b.SetColor(color);
        blocks.push_back(b); // ��� �߰�
    }

    // Ÿ�̸� ����
    auto lastMoveTime = std::chrono::steady_clock::now();
    const int autoMoveInterval = 1000; // �ڵ� �̵� ���� (�и���)

    std::thread inputThread(HandleInput, std::ref(k));
    // ���� ����
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        int elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastMoveTime).count();

        // 1. ����� �Է� ó��
        int key = inputKey.exchange(-1, std::memory_order_relaxed); // �Է� ���� �а� �ʱ�ȭ
        if (key == DOWN) {
            std::cout << "DOWN key pressed" << std::endl;
            for (auto& block : blocks) {
                block.BlockDown(startY, selector); // ����� �Ʒ��� �̵�
            }
        }

        // 2. �ڵ� �̵� ó��
        if (elapsedTime >= autoMoveInterval) {
            
            for (auto& block : blocks) {
                block.BlockDown(startY, selector); // ���� ��� �̵�
            }

            // ���ο� ��� �߰�
            for (int i = 0; i < 3; ++i) {
                Block b;
                int startX = 35 + i * (blockWidth + gap); // X ��ġ ���
                b.GenerateBlock(startX, startY);         // ���ο� ����� �ʱ� ��ġ
                Color color = selector.GetColor(1);      // ���� ��� ���� ����
                b.SetColor(color);                       // ���� ����
                blocks.push_back(b); // ���ο� ��� �߰�
            }

            lastMoveTime = currentTime; // ������ �̵� �ð� ����
        }

        // 3. ��� ���
        for (auto& block : blocks) {
            block.DrawBlock(1); // ��� ���
        }

        // 4. ��� �ð� (���� �ӵ� ����)
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
                cout << "��";
            }
            else {
                cout << map[i][j];
            }
        }

    }
    std::cout.flush(); // ��� ���� ����
}
