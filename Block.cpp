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
                    std::cout << "\033[31m■\033[0m"; // 빨강
                    break;
                case Color::Blue:
                    std::cout << "\033[34m■\033[0m"; // 파랑
                    break;
                case Color::Green:
                    std::cout << "\033[32m■\033[0m"; // 초록
                    break;
                case Color::Yellow:
                    std::cout << "\033[33m■\033[0m"; // 노랑
                    break;
                case Color::purple:
                    std::cout << "\033[35m■\033[0m"; // 보라
                    break;
                case Color::Gal:
                    std::cout << "\033[0;33m■\033[0m"; // 갈색 (밝기 조정 없는 노란색)
                    break;
                case Color::White:
                    std::cout << "\033[37m■\033[0m"; // 흰색
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
    int blockWidth = 6; // 블럭 너비 계산
    int height = 2;                 // 블럭 높이 고정
    int gap = 1;                    // 블럭 간 간격

    this->startX = startX;
    this->startY = startY;

    // 블럭 모양 초기화
    blockShape = vector<vector<int>>(height, vector<int>(blockWidth, 1)); // 2D 벡터로 블럭 생성
}

void Block::BlockDown()
{
}

int Block::DestroyBlock(int level, std::string color)
{
    // 사라진 것으로 간주
    color = "none";
    int score = 1;

    return score;
}








