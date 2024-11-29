#include "KeyManager.h"
#include "Block.h"
#include "Color.h"
#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "ColorSelector.h"
using namespace std;
KeyManager m;
Block::Block() : color("Red"), startX(0), startY(0), blockShape()
{
}

Block::~Block()
{
}

vector<string> Block::DrawBlock(int level)
{
    ColorSelector cSelector;
    Color color = cSelector.GetColor(level);

    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                cout << "\033[" << (startY + i) << ";" << (startX + j * 2) << "H";

                switch (color) {
                case Color::Red:
                    std::cout << "\033[31m��\033[0m"; // ����
                    break;
                case Color::Blue:
                    std::cout << "\033[34m��\033[0m"; // �Ķ�
                    break;
                case Color::Green:
                    std::cout << "\033[32m��\033[0m"; // �ʷ�
                    break;
                case Color::Yellow:
                    std::cout << "\033[33m��\033[0m"; // ���
                    break;
                case Color::purple:
                    std::cout << "\033[35m��\033[0m"; // ����
                    break;
                case Color::Gal:
                    std::cout << "\033[0;33m��\033[0m"; // ���� (��� ���� ���� �����)
                    break;
                case Color::White:
                    std::cout << "\033[37m��\033[0m"; // ���
                    break;
                default:
                    throw std::invalid_argument("Unknown color");
                }
            }
        }
        cout << endl;
    }
    cout << "\033[0;0H";
    return vector<string>();
}

void Block::GenerateBlock(int startX, int startY) {
    int blockWidth = 6; // �� �ʺ� ���
    int height = 2;                 // �� ���� ����
    int gap = 1;                    // �� �� ����

    this->startX = startX;
    this->startY = startY;

    // �� ��� �ʱ�ȭ
    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1)); // 2D ���ͷ� �� ����
}

void Block::BlockDown()
{
}

int Block::DestroyBlock(int level, std::string color)
{
    // ����� ������ ����
    color = "none";
    int score = 1;

    return score;
}








