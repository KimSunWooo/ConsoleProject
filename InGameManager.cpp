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

        // 1. ����� �Է� ó��
        int key = inputKey.exchange(-1, memory_order_relaxed); // �Է� ���� �а� �ʱ�ȭ
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
                Block::GenerateBlockLine(blocks, columns[i], selector, blockWidth, gap, startY, i);
            }

            lastMoveTime = currentTime; // ������ �̵� �ð� ����
        }

        // 3. ������ ������Ʈ
        UpdateColumns(columns, blocks);

        // 4. ���� ��� �� ��� ����
        score += CalculateScore(columns);
        cout << score << endl;

        // 3. ��� ���
        for (auto& block : blocks) {
            block.DrawBlock(1); // ��� ���
        }

        // 4. ��� �ð� (���� �ӵ� ����)
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
    cout << "������ ������Ʈ" << endl;
    // �� ������ �ʱ�ȭ
    for (auto& column : columns) {
        column.clear();
    }

    // ����� �����ٿ� �з�
    for (const auto& block : blocks) {
        cout << block.GetX() << endl;
        int columnIndex = (block.GetX()) / 3; // X ��ǥ�� ���� ������ ����
        if (columnIndex >= 0 && columnIndex < columns.size()) {
            columns[columnIndex].push_back(block);
        }
    }
}

int InGameManager::CalculateScore(vector<vector<Block>>& columns)
{
    cout << "���� ������Ʈ" << endl;
    int score = 0;

    for (auto& column : columns) {
        // �����ٿ��� 3�� ���� ���� ���� ã��
        for (size_t i = 0; i < column.size(); ) {
            size_t count = 1;
            while (i + count < column.size() && column[i].GetColor() == column[i + count].GetColor()) {
                ++count;
            }

            if (count == 3) {
                // 3�� �̻��� ���ӵ� ��� ����
                cout << "�������" << endl;
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




