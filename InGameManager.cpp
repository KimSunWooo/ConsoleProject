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

// ���� ������ �Է� ���� ����
atomic<int> inputKey(-1);  // -1�� Ű �Է� ���� ���¸� ��Ÿ��
atomic<bool> stopInputThread(false); // ������ ���� �÷���

// �Է� ó�� �Լ�
void HandleInput(KeyManager& k) {
    while (!stopInputThread) { // ���� �÷��װ� ������ ������ �ݺ�
        int key = k.HandleKey(); // Ű �Է� ����
        inputKey.store(key, std::memory_order_relaxed); // �Է� ���� ����
        this_thread::sleep_for(chrono::milliseconds(50)); // �Է� ó�� �ӵ� ����
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
    

    vector<Block> blocks; // �����Ǵ� ��ϵ�
    vector<vector<Block>> columns(3); // ��� ������ (��ĥ ��� ���)
    int mapX = 42;             // ���� ���� ũ��
    int blockWidth = (mapX - 2) / 3; // ��� �ʺ�
    int gap = 1;                     // ��� �� ����
    int startY = 7;                  // �ʱ� Y ��ǥ
    int score = 0;

    // ù ��° �� ��� �ʱ�ȭ
    for (int i = 0; i < 3; ++i) {
        Block::GenerateBlockLine(blocks, columns[i], selector, blockWidth, gap, startY, i);
    }

    // Ÿ�̸� ����
    auto lastMoveTime = chrono::steady_clock::now();
    const int autoMoveInterval = 1000; // �ڵ� �̵� ���� (�и���)

    std::thread inputThread(HandleInput, std::ref(k));
    // ���� ����
    while (true) {
        auto currentTime = chrono::steady_clock::now();
        int elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastMoveTime).count();

        // ����� �Է� ó��
        int key = inputKey.exchange(-1, memory_order_relaxed);
        if (key == DOWN) {
            for (auto& block : blocks) {
                block.BlockDown(startY, selector);
            }
            UpdateColumns(columns, blocks);
        }

        // �ڵ� �̵� ó��
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

        // ���� ��� �� ��� ����
        score += CalculateScore(columns);
        Block::RemoveMatchingBlocks(columns, blocks);

        // ��� �ٽ� ���
        for (auto& block : blocks) {
            block.DrawBlock(1);
        }

        // ���� �ӵ� ����
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
                cout << "��";
            }
            else {
                cout << map[i][j];
            }
        }

    }
    std::cout.flush(); // ��� ���� ����
}

void InGameManager::UpdateColumns(vector<vector<Block>>& columns, const std::vector<Block>& blocks)
{
    // �� ������ �ʱ�ȭ
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
        if (column.size() >= 3) { // �����ٿ� ����� 3�� �̻��� ���
            // ���ϴ� 3���� ����� ���� �������� Ȯ��
            auto color1 = column[column.size() - 1].GetColor();
            auto color2 = column[column.size() - 2].GetColor();
            auto color3 = column[column.size() - 3].GetColor();

            if (color1 == color2 && color2 == color3) {
                score += 100; // ���� ���� ����� 3�� �̻��̸� ���� �߰�
            }
        }
        
    }

    return score;
}




