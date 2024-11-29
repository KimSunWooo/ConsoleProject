#include "KeyManager.h"
#include "Block.h"
#include <iostream>
#include <vector>
using namespace std;

Block::Block() : color("Red"), startX(0), startY(0)
{
}

Block::~Block()
{
}

void Block::GenerateBlock(int mapX)
{
    
    
    int blockWidth = (mapX-2)/3;
    
    int height = 2;
    
    // �� ������ 16, "��"�� 2ĭ ��Ƹ���, 18���� �����ϴ°� ����
    // �� ũ��� �����̴ϱ� ����� �ھƳִ°� ����? �����..
    // ��� ���������� {18, 26, 34}
    int startPosition = rand() % 3;
    
    startX = startPosition * (blockWidth+1) + 18;
    startY = 6;

    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1));

    blockColor = colors[rand() % colors.size()];
}

int Block::DestroyBlock(int level, std::string color)
{   
    // ����� ������ ����
    color = "none";
    int score = 1;

    return score;
}

void Block::BlockDown()
{
}

vector<string> Block::GetAddColor()
{
    return AddColors;
}

void Block::SetColors(int level)
{
    Block::colors.push_back(Block::GetAddColor()[level - 3]);
}

vector<vector<string>> Block::BlockShape() {
    vector<vector<string>> visualBlock;

    for (const auto& row : blockShape) {
        vector<string> visualRow;
        for (const auto& cell : row) {
            if (cell == 1) {
                visualRow.push_back(blockColor); // ��� ���� �߰�
            }
            else {
                visualRow.push_back(" ");
            }
        }
        visualBlock.push_back(visualRow);
    }

    return visualBlock;
}
