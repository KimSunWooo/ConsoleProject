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
    
    // 맵 시작점 16, "■"가 2칸 잡아먹음, 18부터 시작하는게 맞음
    // 블럭 크기는 고정이니까 상수로 박아넣는게 좋나? 고민좀..
    // 블록 생성지점은 {18, 26, 34}
    int startPosition = rand() % 3;
    
    startX = startPosition * (blockWidth+1) + 18;
    startY = 6;

    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1));

    blockColor = colors[rand() % colors.size()];
}

int Block::DestroyBlock(int level, std::string color)
{   
    // 사라진 것으로 간주
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
                visualRow.push_back(blockColor); // 블록 색상 추가
            }
            else {
                visualRow.push_back(" ");
            }
        }
        visualBlock.push_back(visualRow);
    }

    return visualBlock;
}
