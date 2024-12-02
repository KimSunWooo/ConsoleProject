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
Block::Block() : color(Color::Red),x(16), y(6), startX(0),  blockShape()
{
}

Block::~Block()
{
}

void Block::GenerateBlockLine(std::vector<Block>& blocks, vector<Block> height, ColorSelector selector, int blockWidth, int gap, int startY, int i)
{
    Block b;
    int startX = 35 + i * (blockWidth + gap); // X ��ġ ���
    b.GenerateBlock(startX, startY);
    Color color = selector.GetColor(1);      // ���� ��� ���� ����
    b.SetColor(color);
    height.push_back(b);
    blocks.push_back(b); // ��� �߰�
}

bool Block::operator==(const Block& other) const {
    return x == other.x && y == other.y && color == other.color;
}

vector<string> Block::DrawBlock(int level) {
    for (int i = 0; i < blockShape.size(); i++) {
        for (int j = 0; j < blockShape[i].size(); j++) {
            if (blockShape[i][j] == 1) {
                cout << "\033[" << (y + i) << ";" << (startX + j * 2) << "H";

                // ������ color�� ���� ���
                switch (color) {
                case Color::Red:
                    cout << "\033[31m��\033[0m"; // ����
                    break;
                case Color::Blue:
                    cout << "\033[34m��\033[0m"; // �Ķ�
                    break;
                case Color::Green:
                    cout << "\033[32m��\033[0m"; // �ʷ�
                    break;
                case Color::Yellow:
                    cout << "\033[33m��\033[0m"; // ���
                    break;
                case Color::Purple:
                    cout << "\033[35m��\033[0m"; // ����
                    break;
                default:
                    cout << "��"; // �⺻��
                }
            }
        }
        cout << endl;
    }
    return vector<string>();
}

void Block::GenerateBlock(int startX, int y) {
    int blockWidth = 6; // �� �ʺ� ���
    int height = 2;     // �� ���� ����

    this->startX = startX;
    this->y = y; // ���յ� Y ��ǥ ����

    // �� ��� �ʱ�ȭ
    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1)); // 2D ���ͷ� �� ����
}

void Block::BlockDown(int startY, ColorSelector& selector) {
    y+=2;
    // �Ź� ȣ�� �� ���� ����
    Color newColor = selector.GetColor(1); // ���ο� ���� ����
     
}

std::atomic<bool> isBlockMoving(false);
void Block::MoveBlocks(std::vector<Block>& blocks, int startY, ColorSelector& selector)
{
    if (isBlockMoving.load(std::memory_order_relaxed)) {
        return; // �̵� ���̸� �ߺ� ó�� ����
    }

    isBlockMoving.store(true, std::memory_order_relaxed); // �̵� ����

    for (auto& block : blocks) {
        block.BlockDown(startY, selector); // ��� �̵�
    }

    isBlockMoving.store(false, std::memory_order_relaxed); // �̵� �Ϸ�
}

int Block::GetX() const {
    return x;
}

// Y ��ǥ ��ȯ
int Block::GetY() const {
    return y;
}

// ���� ��ȯ
Color Block::GetColor() const {
    return color;
}

void Block::SetColor(Color newColor)
{
    this->color = newColor;
}

int Block::DestroyBlock(int level, std::string color)
{
    // ����� ������ ����
    color = "none";
    int score = 1;

    return score;
}








